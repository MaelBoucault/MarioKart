#pragma once

#include "CoreMinimal.h"
#include "Boost.h"
#include "PadJumpBoost.generated.h"

UCLASS()
class MARIOKART_API APadJumpBoost : public ABoost
{
	GENERATED_BODY()

	
public:
	APadJumpBoost();


protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Boost")
	float JumpBoost = 2000.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Boost")
	TObjectPtr<UBoxComponent> TriggerJumpBox;

	UFUNCTION()
	void OnBoxJumpBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};