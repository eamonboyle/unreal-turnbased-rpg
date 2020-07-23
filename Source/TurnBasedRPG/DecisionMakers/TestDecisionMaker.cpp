// Fill out your copyright notice in the Description page of Project Settings.


#include "TestDecisionMaker.h"

#include "../Characters/GameCharacter.h"
#include "../Actions/TestCombatAction.h"

void TestDecisionMaker::BeginMakeDecision(UGameCharacter* Character)
{
    Character->CombatAction = new TestCombatAction();
}

bool TestDecisionMaker::MakeDecision(float DeltaSeconds)
{
    return true;
}
