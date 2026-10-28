// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Boost.generated.h"

UCLASS()
class MARIOKART_API ABoost : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ABoost();
	
	//Creation de la function construct pour des update direct dans la scene
	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Boost|Components|Mesh")
	TObjectPtr<UStaticMeshComponent> BoostMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Boost|Components|TriggerBox")
	TObjectPtr<UBoxComponent> TriggerBox;
	
	UPROPERTY(EditAnywhere, Category = "Boost|Components|TriggerBox", meta = (ClampMin = "0"))
	float MinBoxExtentZ = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Kart|Boost")
	float BoostMultiplier = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Kart|Boost")
	float BoostTime = 2.f;
	
public:	
	
	//Function pour que la box fasse la taille du mesh
	void UpdateTriggerBox();
	
	UFUNCTION(BlueprintCallable, Category = "Boost")
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
