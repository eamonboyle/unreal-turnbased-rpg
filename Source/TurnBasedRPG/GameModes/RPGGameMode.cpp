// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGGameMode.h"

#include "TurnBasedRPG/Characters/RPGCharacter.h"

ARPGGameMode::ARPGGameMode(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    DefaultPawnClass = ARPGCharacter::StaticClass();
}
