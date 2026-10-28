// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KartHUD.generated.h"

/**
 * 
 */

class UTextBlock;
class UImage;
class UTexture2D;


UCLASS()
class MARIOKART_API UKartHUD : public UUserWidget
{
	GENERATED_BODY()
	
	
protected:
	
	//tick
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	// BindWidget pour que ça compile pas si il y a pas (nom exacte)
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> SpeedText;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> LapText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TimeText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CountdownText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> ItemImage;
	
};
