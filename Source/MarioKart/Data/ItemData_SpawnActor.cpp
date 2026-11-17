

#include "Data/ItemData_SpawnActor.h"
#include "Engine/World.h"
#include "Core/KartPawn.h"


bool UItemData_SpawnActor::Activate(AKartPawn* Kart) const
{
	if (Kart == nullptr || ActorClass == nullptr)
	{
		return false;
	}
	
	// TransformPosition passe du repère du kart au repère du monde :
	// (-150, 0, 0) "derrière le kart" devient la vraie position dans le niveau, quelle que soit la direction du kart
	const FVector SpawnLocation = Kart->GetActorTransform().TransformPosition(SpawnOffset);
	
	// On garde seulement le Yaw du kart (sa direction) : l'acteur part à l'horizontale même si le kart est dans une pente
	const FRotator SpawnRotation(0.f, Kart->GetActorRotation().Yaw, 0.f);
	
	
	// Owner = le kart qui a utilisé l'objet : l'acteur créé saura qui l'a lancé (un projectile peut ignorer son lanceur)
	// AlwaysSpawn = on le crée même s'il touche déjà quelque chose (sinon Unreal peut refuser de le faire apparaître)
	FActorSpawnParameters SpawnParams;
	
	SpawnParams.Owner = Kart;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	const AActor* SpawnedActor = Kart->GetWorld()->SpawnActor<AActor>(ActorClass, SpawnLocation, SpawnRotation, SpawnParams);
	
	return SpawnedActor != nullptr;
}
