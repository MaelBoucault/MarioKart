

#include "LapZone.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "KartPawn.h"


// Sets default values
ALapZone::ALapZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	Box = CreateDefaultSubobject<UBoxComponent>(FName("Box"));
	Box->SetBoxExtent(BoxExtent);
	Box->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	RootComponent = Box;
	
	
	Arrow = CreateDefaultSubobject<UArrowComponent>(FName("Arrow"));
	Arrow->SetupAttachment(Box);
	Arrow->ArrowSize = 3.f;
}

// Called when the game starts or when spawned
void ALapZone::BeginPlay()
{
	Super::BeginPlay();
	
	Box->OnComponentBeginOverlap.AddDynamic(this, &ALapZone::OnBoxBeginOverlap);
}

bool ALapZone::IsGoingRightWay(const FVector& MoveDirection) const
{
	return FVector::DotProduct(MoveDirection, Arrow->GetForwardVector()) > 0.f;
}

void ALapZone::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AKartPawn* Kart = Cast<AKartPawn>(OtherActor);
	
	if (Kart == nullptr)
	{
		return;
	}
	
	if (IsGoingRightWay(Kart->GetMoveDirection()))
	{
		Kart->EnterLapZone(ZoneIndex);
	}
}

