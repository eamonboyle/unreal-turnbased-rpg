// Fill out your copyright notice in the Description page of Project Settings.


#include "TestDecisionMaker.h"

#include "../Characters/GameCharacter.h"
#include "../Actions/TestCombatAction.h"

void TestDecisionMaker::BeginMakeDecision(UGameCharacter* Character)
{
    // pick a target
    UGameCharacter* Target = Character->SelectTarget();
    Character->CombatAction = new TestCombatAction(Target);
}

bool TestDecisionMaker::MakeDecision(float DeltaSeconds)
{
    return true;
}
