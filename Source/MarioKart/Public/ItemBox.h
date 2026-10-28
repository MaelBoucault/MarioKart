// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBox.generated.h"

class USkeletalMeshComponent;
class UAnimationAsset;
class UBoxComponent;

UCLASS()
class MARIOKART_API AItemBox : public AActor
{
	GENERATED_BODY()
	
public:	
	AItemBox();

protected:
	
	UPROPERTY(VisibleAnywhere, Category = "Item|Components")
	TObjectPtr<UBoxComponent> Trigger;
	
	UPROPERTY(VisibleAnywhere, Category = "Item|Components")
	TObjectPtr<USkeletalMeshComponent> BoxMesh;
	
	UPROPERTY(VisibleAnywhere, Category = "Item|Components")
	TObjectPtr<UStaticMeshComponent> InterrogationMesh;
	
	UPROPERTY(EditAnywhere, Category = "Item|Components")
	TObjectPtr<UAnimationAsset> Animation;
	
	UPROPERTY(VisibleAnywhere, Category = "Item|Variable")
	float RespawnTime = 3.f;
	
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
				   int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	
	virtual void BeginPlay() override;

	
private:
	
	void SetActive(bool bActive);
	FTimerHandle RespawnTimer;
	
};
