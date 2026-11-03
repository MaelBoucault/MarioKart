
#include "KartController.h"
#include "KartHUD.h"
#include "Blueprint/UserWidget.h"



void AKartController::BeginPlay()
{
	Super::BeginPlay();
	
	if (HUDClass != nullptr)
	{
		HUD = CreateWidget<UKartHUD>(this, HUDClass);
		if (HUD != nullptr)
		{
			HUD->AddToViewport();
		}
	}
}



void AKartController::UpdateHUD()
{
	if (HUD != nullptr)
	{
		HUD->UpdateKartHUD();
	}
	
}