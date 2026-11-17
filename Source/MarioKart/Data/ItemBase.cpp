// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ItemBase.h"
#include "Core/KartPawn.h"

bool UItemBase::Activate(AKartPawn* Kart) const
{
	// Le parent n'a pas d'effet : ce sont les classes enfants qui remplacent cette fonction
	// On renvoie false pour que l'objet ne soit pas consommé si un enfant oublie de la redéfinir
	return false;
}

