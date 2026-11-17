// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/KartPawn.h"
#include "Data/ItemBase.h"
#include "ItemData_SpawnActor.generated.h"

/*

Objet qui fait apparaître un acteur près du kart : un piège posé derrière, un projectile lancé devant...
La même classe sert pour tous ces objets : seuls l'acteur à créer et sa position changent d'un asset à l'autre

 */
UCLASS()
class MARIOKART_API UItemData_SpawnActor : public UItemBase
{
	GENERATED_BODY()
	
public:
	
	// L'acteur à faire apparaître (BP_ItemTrap, BP_ItemProjectile...)
	// TSubclassOf<AActor> = "une classe qui hérite de AActor" : on choisit un Blueprint dans une liste
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Spawn")
	TSubclassOf<AActor> ActorClass;
	
	
	// Position d'apparition par rapport au kart, en cm : X > 0 = devant, X < 0 = derrière, Z = hauteur
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Spawn")
	FVector SpawnOffset = FVector(-150.f, 0.f, 0.f);
	
	
	virtual bool Activate(AKartPawn* Kart) const override;
	
};
