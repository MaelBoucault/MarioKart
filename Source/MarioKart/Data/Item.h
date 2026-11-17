#pragma once


#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Item.generated.h"

UENUM(BlueprintType)
enum class EItem : uint8
{
	None,
	Consumable,
	Throwable,
};
