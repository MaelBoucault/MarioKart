

#include "KartItemHazard.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "Core/KartPawn.h"


AKartItemHazard::AKartItemHazard()
{
    // Un piège ne fait rien à chaque frame (le projectile, lui, rallumera le Tick)
    PrimaryActorTick.bCanEverTick = false;
    CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
    CollisionSphere->SetSphereRadius(40.f);
    RootComponent = CollisionSphere;
    
    // On règle la collision canal par canal au lieu de prendre un profil tout fait :
    // - QueryOnly = détecte et bloque les déplacements, mais pas de physique simulée
    // - WorldDynamic = c'est un objet du décor qui bouge
    // - Block sur tout = les murs arrêtent le projectile (il rebondira dessus)
    // - Overlap sur Pawn = les karts passent au travers, mais déclenchent l'event OnComponentBeginOverlap
    // - Ignore sur Visibility = les rayons des roues du kart ne le prennent pas pour du sol
    
    
    CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionSphere->SetCollisionObjectType(ECC_WorldDynamic);
    CollisionSphere->SetCollisionResponseToAllChannels(ECR_Block);
    CollisionSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    CollisionSphere->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
    CollisionSphere->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
    CollisionSphere->SetGenerateOverlapEvents(true);
    
    // Le mesh est juste visuel
    
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Mesh->SetupAttachment(CollisionSphere);
    Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AKartItemHazard::BeginPlay()
{
    Super::BeginPlay();
    CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AKartItemHazard::HandleBeginOverlap);
    // L'objet est créé à côté du kart, peut-être en l'air (en haut d'une bosse, pendant un saut...) : on le pose au sol
    FHitResult GroundHit;
    if (FindGround(1000.f, GroundHit))
    {
        SetActorLocation(GroundHit.ImpactPoint + FVector::UpVector * HoverHeight);
    }
}

bool AKartItemHazard::FindGround(float MaxDistance, FHitResult& OutHit) const
{
    // On part un peu au-dessus du centre pour ne pas commencer sous le sol dans une montée
    const FVector Start = GetActorLocation() + FVector::UpVector * 50.f;
    const FVector End = GetActorLocation() - FVector::UpVector * MaxDistance;
    // On ignore le danger lui-même et le kart qui l'a lancé
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);
    Params.AddIgnoredActor(GetOwner());
    return GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, Params);
}

void AKartItemHazard::HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    AKartPawn* Kart = Cast<AKartPawn>(OtherActor);
    if (Kart == nullptr)
    {
        return;
    }
    // Juste après le lancer, le lanceur est protégé : sinon un projectile lancé en marche avant
    // pourrait le toucher tout de suite (GetGameTimeSinceCreation = âge de l'acteur en secondes)
    if (Kart == GetOwner() && GetGameTimeSinceCreation() < OwnerSafeTime)
    {
        return;
    }
    Kart->SpinOut(SpinOutDuration);
    OnHitKart(Kart);
    // Le danger a servi : il disparaît
    Destroy();
}