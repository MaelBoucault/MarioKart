#include "PadJumpBoost.h"
#include "Components/BoxComponent.h"
#include "KartPawn.h"

APadJumpBoost::APadJumpBoost()
{
	//definie les details du TriggerBox
	TriggerJumpBox = CreateDefaultSubobject<UBoxComponent>(TEXT("JumpBox"));
	TriggerJumpBox->SetupAttachment(BoostMesh);
	TriggerJumpBox->SetBoxExtent(FVector(100.f, 100.f, 50.f));
	TriggerJumpBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	TriggerJumpBox->SetGenerateOverlapEvents(true);
	
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


void APadJumpBoost::BeginPlay()
{
	Super::BeginPlay();
	
	//Assigne l'event overlap de la box a la function créer dans script
	TriggerJumpBox->OnComponentBeginOverlap.AddDynamic(this, &APadJumpBoost::OnBoxJumpBeginOverlap);
}


void APadJumpBoost::OnBoxJumpBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//fais sauté le Kart
	AKartPawn* Kart = Cast<AKartPawn>(OtherActor);
	if (Kart == nullptr)
	{
		return;
	}
	Kart->Jump(JumpBoost);
}