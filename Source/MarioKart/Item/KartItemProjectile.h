#pragma once
#include "CoreMinimal.h"
#include "Item/KartItemHazard.h"
#include "KartItemProjectile.generated.h"
// Projectile lancé devant le kart : il file en ligne droite au ras du sol et rebondit sur les murs
// Il HÉRITE de AKartItemHazard : la collision, le tête-à-queue du kart touché et la disparition sont déjà faits par le parent
// Cette classe n'ajoute que le mouvement
UCLASS()
class MARIOKART_API AKartItemProjectile : public AKartItemHazard
{
	GENERATED_BODY()
public:
	
	AKartItemProjectile();
	virtual void Tick(float DeltaTime) override;
	
	
protected:
	virtual void BeginPlay() override;
	// ---------- Réglages ----------
	// Vitesse en cm/s (plus rapide que le kart, pour qu'il puisse rattraper ceux de devant)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Kart|Projectile")
	float Speed = 4000.f;
	// Nombre de rebonds sur les murs avant de disparaître
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Kart|Projectile", meta = (ClampMin = "0"))
	int32 MaxBounces = 3;
	// Gravité quand le projectile n'est plus au sol (au bord d'un saut, par exemple)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Kart|Projectile")
	float GravityStrength = 2500.f;
	// Distance sous le projectile en dessous de laquelle on considère qu'il est encore au sol
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Kart|Projectile")
	float GroundStickDistance = 30.f;
private:
	// Direction horizontale du projectile (elle change à chaque rebond)
	FVector MoveDirection = FVector::ForwardVector;
	float VerticalSpeed = 0.f;
	int32 BouncesLeft = 0;
};