// Fill out your copyright notice in the Description page of Project Settings.


#include "TestCombatAction.h"

#include "TurnBasedRPG/Characters/GameCharacter.h"

void TestCombatAction::BeginExecuteAction(UGameCharacter* Character)
{
    UE_LOG(LogTemp, Warning, TEXT("%s does nothing"), *Character->CharacterName);
    this->DelayTimer = 1.f;
}

bool TestCombatAction::ExecuteAction(float DeltaSeconds)
{
    this->DelayTimer -= DeltaSeconds;
    return this->DelayTimer <= 0.f;
}
