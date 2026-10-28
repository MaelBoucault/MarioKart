#include "KartHUD.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"
#include "KartPawn.h"
#include "KartGameMode.h"

void UKartHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	//Verification :
	const AKartPawn* Kart = Cast<AKartPawn>(GetOwningPlayerPawn());
	const AKartGameMode* GameMode = GetWorld()->GetAuthGameMode<AKartGameMode>();
	if (Kart == nullptr || GameMode == nullptr)
	{
		return;
	}
	
	//met la vitesse en Km/h et l'affiche
	const int32 SpeedKmh = FMath::RoundToInt(FMath::Abs(Kart->GetCurrentSpeed()) * 0.036f);
	SpeedText->SetText(FText::FromString(FString::Printf(TEXT("%d km/h"), SpeedKmh)));

	
	
	LapText->SetText(FText::FromString(FString::Printf(TEXT("Tour %d/%d"), Kart->GetCurrentLap(), GameMode->GetLapCount())));
	const float Time = Kart->HasFinishedRace() ? Kart->GetFinishTime() : GameMode->GetRaceTime();
	TimeText->SetText(AKartGameMode::FormatRaceTime(Time));
	
	
	//Affiche le 3,2,1,0 et disparait
	const int32 Countdown = GameMode->GetCountdownNumber();
	CountdownText->SetVisibility(Countdown > 0 ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Collapsed);
	if (Countdown > 0)
	{
		CountdownText->SetText(FText::AsNumber(Countdown));
	}

	
	//Affiche l'icon du bonus si il y en a un
	UTexture2D* Icon = Kart->GetCurrentItemData().Icon;
	ItemImage->SetVisibility(Icon ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Collapsed);
	if (Icon)
	{
		ItemImage->SetBrushFromTexture(Icon);
	}
}