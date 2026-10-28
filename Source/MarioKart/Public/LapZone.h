
#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "LapZone.generated.h"

UCLASS()
class MARIOKART_API ALapZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALapZone();
	
	UFUNCTION(BlueprintPure, Category = "Kart|Lap")
	int32 GetZoneIndex() const { return ZoneIndex; }
	
	UFUNCTION(BlueprintPure, Category = "Kart|Lap")
	bool IsGoingRightWay(const FVector& MoveDirection) const;
	
	UPROPERTY(EditAnywhere, Category = "Kart|Lap")
	FVector BoxExtent = FVector(50.f,500.f,200.f);
	

protected:
	
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Kart|Components")
	TObjectPtr<UBoxComponent> Box;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Kart|Components")
	TObjectPtr<UArrowComponent> Arrow;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Kart|Lap", meta = (ClampMin = "0"))
	int32 ZoneIndex = 0;

public:	
	
	UFUNCTION(BlueprintCallable, Category = "Kart|Lap")
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	

};
