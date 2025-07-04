// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyItem.h"

AKeyItem::AKeyItem()
	: KeyOrder(0), bIsUsable(false), bIsCollected(false)
{
	PrimaryActorTick.bCanEverTick = false;
}

void AKeyItem::Interact()
{

}
