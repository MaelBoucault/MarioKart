// Fill out your copyright notice in the Description page of Project Settings.


#include "Boost.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "KartPawn.h"


ABoost::ABoost()
{
	PrimaryActorTick.bCanEverTick = false;
	
	BoostMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoostMesh"));
	BoostMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = BoostMesh;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	TriggerBox->SetupAttachment(BoostMesh);
	TriggerBox->SetBoxExtent(FVector(100.f, 100.f, 50.f));
	TriggerBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	TriggerBox->SetGenerateOverlapEvents(true);

}


void ABoost::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	UpdateTriggerBox();
}


void ABoost::BeginPlay()
{
	Super::BeginPlay();
	
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ABoost::OnBoxBeginOverlap);
	
}



void ABoost::UpdateTriggerBox()
{
	if (BoostMesh == nullptr || BoostMesh->GetStaticMesh() == nullptr)
	{
		return;
	}
	
	const FBoxSphereBounds MeshBounds = BoostMesh->GetStaticMesh()->GetBounds();
	
	FVector Extent = MeshBounds.BoxExtent;
	Extent.Z = FMath::Max(Extent.Z, MinBoxExtentZ);
	
	TriggerBox->SetBoxExtent(Extent);
	TriggerBox->SetRelativeLocation(MeshBounds.Origin);
}



void ABoost::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AKartPawn* Kart = Cast<AKartPawn>(OtherActor);

	if (Kart == nullptr)
	{
		return;
	}
	Kart->SetSpeedBoost(BoostMultiplier, BoostTime);
	
}


