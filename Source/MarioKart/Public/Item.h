#pragma once


#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Item.generated.h"

UENUM(BlueprintType)
enum class EKartItem : uint8
{
	None,
	Mushroom,
	Banana
};

USTRUCT(BlueprintType)
struct FKartItemData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EKartItem Type = EKartItem::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTexture2D> Icon;

	// Probabilité relative d'obtenir cet objet
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"))
	float DropWeight = 1.f;

	// Utilisé que par le champignon
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BoostDuration = 1.5f;
};