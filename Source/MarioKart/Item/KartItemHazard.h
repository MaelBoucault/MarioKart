#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KartItemHazard.generated.h"
class USphereComponent;
class UStaticMeshComponent;
class UPrimitiveComponent;
class AKartPawn;
struct FHitResult;
// Un danger sur la piste, créé par un objet bonus : le kart qui le touche part en tête-à-queue, puis le danger disparaît
// Tel quel, c'est un PIÈGE : il se pose au sol et attend (BP_ItemTrap hérite de cette classe)
// AKartItemProjectile hérite de cette classe et ajoute seulement le déplacement : toucher un kart marche pareil
UCLASS()
class MARIOKART_API AKartItemHazard : public AActor
{
    GENERATED_BODY()
public:
    AKartItemHazard();
protected:
    virtual void BeginPlay() override;
    // ---------- Composants ----------
    // Sphère de collision : bloquée par les murs, mais les karts passent à travers (overlap) pour être touchés
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Kart|Components")
    TObjectPtr<USphereComponent> CollisionSphere;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Kart|Components")
    TObjectPtr<UStaticMeshComponent> Mesh;
    // ---------- Réglages ----------
    // Durée du tête-à-queue du kart touché
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Kart|Hazard", meta = (ClampMin = "0.1"))
    float SpinOutDuration = 1.5f;
    // Hauteur (en cm) du centre de la sphère au-dessus du sol
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Kart|Hazard", meta = (ClampMin = "0"))
    float HoverHeight = 45.f;
    // Pendant ce temps après l'apparition, le kart qui a lancé l'objet ne peut pas se toucher lui-même
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Kart|Hazard", meta = (ClampMin = "0"))
    float OwnerSafeTime = 0.5f;
    // Appelé juste avant que le danger disparaisse en touchant un kart : pour un son ou une explosion dans le BP
    UFUNCTION(BlueprintImplementableEvent, Category = "Kart|Hazard")
    void OnHitKart(AKartPawn* Kart);
    // Cherche le sol sous le danger, jusqu'à MaxDistance cm plus bas. Renvoie true s'il y en a un (infos dans OutHit)
    // "protected" et pas "private" : le projectile (classe enfant) s'en sert aussi
    bool FindGround(float MaxDistance, FHitResult& OutHit) const;
private:
    UFUNCTION()
    void HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
