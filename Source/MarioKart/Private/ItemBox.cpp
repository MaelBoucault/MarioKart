

#include "ItemBox.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "KartPawn.h"
#include "TimerManager.h"


AItemBox::AItemBox()
{
	
	Trigger = CreateDefaultSubobject<UBoxComponent>("Trigger");
	Trigger->SetBoxExtent(FVector(80.f));
	Trigger->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	RootComponent = Trigger;
	
	//lz cube du bonus est un skeletal mesh car il a une animation sequance 
	BoxMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	BoxMesh->SetupAttachment(Trigger);
	BoxMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	
	InterrogationMesh = CreateDefaultSubobject<UStaticMeshComponent>("InterrogationMesh");
	InterrogationMesh->SetupAttachment(Trigger);
	InterrogationMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	
	Trigger->OnComponentBeginOverlap.AddDynamic(this,&AItemBox::OnOverlap);
}

void AItemBox::BeginPlay()
{
	Super::BeginPlay();

	//Lance l'aimation si elle est assignée:
	if (Animation)
	{
		BoxMesh->SetAnimationMode(EAnimationMode::AnimationSingleNode);
		BoxMesh->SetAnimation(Animation);
		BoxMesh->Play(true);
	}
}

void AItemBox::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AKartPawn* Kart = Cast<AKartPawn>(OtherActor);
	
	//Verifie si c'est un Kart
	if (Kart == nullptr) return;
	
	
	//On ne peut plus recup de bonus pendant RespawnTimer s
	SetActive(false);
	GetWorld()->GetTimerManager().SetTimer(RespawnTimer,FTimerDelegate::CreateUObject(this, &AItemBox::SetActive,true), RespawnTime, false);
	
	
	//lance la function pour recup un item
	if (Kart->GiveRandomItem()) return;

}

//rend la box invisible ou visible selon bActive
void AItemBox::SetActive(bool bActive)
{
	BoxMesh->SetVisibility(bActive);
	InterrogationMesh->SetVisibility(bActive);
	Trigger->SetCollisionEnabled(bActive ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
}
