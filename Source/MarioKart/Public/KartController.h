// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "KartController.generated.h"

/**
 * 
 */

class UKartHUD;


UCLASS()
class MARIOKART_API AKartController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,Category = "Kart|UI")
	TSubclassOf<UKartHUD> HUDClass;
	
	UFUNCTION(Category = "Kart|UI")
	void UpdateHUD();
	
public:
	
	UPROPERTY()
	TObjectPtr<UKartHUD> HUD;
	
	
	
};
