// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Item.h"
#include "ItemBase.generated.h"



UCLASS()
class MARIOKART_API UItemBase : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
	
public:
	
	UPROPERTY(EditDefaultsOnly)
	FString ItemName;
	
	UPROPERTY(EditDefaultsOnly)
	float Duration;
	
	UPROPERTY(EditDefaultsOnly)	
	int32 AmountUse;
	
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* ItemIcon;
	
	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "0"))
	float DropWeight = 1.f;
	
	UPROPERTY(EditDefaultsOnly)
	float BoostForce;
	
	UPROPERTY(EditDefaultsOnly)
	EItem Type = EItem::None;
	
	UPROPERTY(EditDefaultsOnly)
	float BoostDuration = 1.5f;
	
	
	
	
};
