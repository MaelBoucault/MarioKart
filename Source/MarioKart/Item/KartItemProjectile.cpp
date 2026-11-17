#include "Item/KartItemProjectile.h"
// Même règle que pour le kart : une surface dont la normale a un Z plus grand que ça est un sol, sinon c'est un mur
static constexpr float ProjectileFloorZ = 0.7f;


AKartItemProjectile::AKartItemProjectile()
{
    // Le parent a coupé le Tick (un piège ne bouge pas) : le projectile, lui, avance à chaque frame
    PrimaryActorTick.bCanEverTick = true;
    // InitialLifeSpan est une variable de AActor : l'acteur se détruit tout seul au bout de ce temps
    // (un projectile qui ne touche personne ne doit pas rester dans le niveau pour toujours)
    InitialLifeSpan = 10.f;
}
void AKartItemProjectile::BeginPlay()
{
    // Le BeginPlay du parent pose le projectile au sol et branche la détection des karts
    Super::BeginPlay();
    // L'acteur est créé tourné dans la direction du kart (voir UKartItemData_SpawnActor) : on part tout droit
    MoveDirection = GetActorForwardVector().GetSafeNormal2D();
    BouncesLeft = MaxBounces;
}
void AKartItemProjectile::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    // ---------- 1. Le sol : on y reste collé, ou on tombe ----------
    FHitResult GroundHit;
    FVector Direction = MoveDirection;
    if (FindGround(HoverHeight + GroundStickDistance, GroundHit))
    {
        VerticalSpeed = 0.f;
        SetActorLocation(GroundHit.ImpactPoint + FVector::UpVector * HoverHeight);
        // Dans une pente, on avance le long du sol (comme le kart dans MoveKart)
        Direction = FVector::VectorPlaneProject(MoveDirection, GroundHit.ImpactNormal).GetSafeNormal();
    }
    else
    {
        VerticalSpeed -= GravityStrength * DeltaTime;
    }
    // ---------- 2. Le déplacement, avec "sweep" pour s'arrêter contre les murs ----------
    const FVector Delta = Direction * Speed * DeltaTime + FVector::UpVector * VerticalSpeed * DeltaTime;
    FHitResult Hit;
    AddActorWorldOffset(Delta, true, &Hit);
    if (!Hit.bBlockingHit)
    {
        return;
    }
    // On a touché une surface plate (le sol, une bosse) : on finit le mouvement sans collision
    if (Hit.Normal.Z >= ProjectileFloorZ)
    {
        AddActorWorldOffset(Delta * (1.f - Hit.Time), false);
        return;
    }
    // ---------- 3. Un mur : rebond ----------
    if (BouncesLeft <= 0)
    {
        Destroy();
        return;
    }
    --BouncesLeft;
    // MirrorByVector renvoie la direction "en miroir" par rapport au mur, comme une balle de billard :
    // la partie qui rentre dans le mur est inversée, la partie qui longe le mur est gardée
    // GetSafeNormal2D enlève la hauteur (Z) et remet la longueur à 1 : on reste à l'horizontale
    MoveDirection = MoveDirection.MirrorByVector(Hit.Normal).GetSafeNormal2D();
    SetActorRotation(MoveDirection.Rotation());
}