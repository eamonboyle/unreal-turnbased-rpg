// Fill out your copyright notice in the Description page of Project Settings.


#include "TestCombatAction.h"

#include "TurnBasedRPG/Characters/GameCharacter.h"

TestCombatAction::TestCombatAction(UGameCharacter* Target)
    : DelayTimer(0), Character(nullptr)
{
    this->Target = Target;
}

void TestCombatAction::BeginExecuteAction(UGameCharacter* NewCharacter)
{
    this->Character = NewCharacter;

    // target is dead, select another target
    if (this->Target->HP <= 0)
    {
        this->Target = this->Character->SelectTarget();
    }

    // no target, just return
    if (this->Target == nullptr)
    {
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("%s attacks %s"), *Character->CharacterName, *Target->CharacterName);

    Target->HP -= 10;

    this->DelayTimer = 1.f;
}

bool TestCombatAction::ExecuteAction(float DeltaSeconds)
{
    this->DelayTimer -= DeltaSeconds;
    return this->DelayTimer <= 0.f;
}
