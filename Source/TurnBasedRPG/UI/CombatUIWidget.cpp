// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatUIWidget.h"
#include "../Combat/CombatEngine.h"
#include "../Combat/Actions/TestCombatAction.h"
#include "../Characters/GameCharacter.h"

void UCombatUIWidget::BeginMakeDecision(UGameCharacter* Target)
{    
    this->CurrentTarget = Target;
    this->FinishedDecision = false;

    ShowActionsPanel(Target);
}

bool UCombatUIWidget::MakeDecision(float DeltaSeconds)
{
    return this->FinishedDecision;
}

void UCombatUIWidget::AttackTarget(UGameCharacter* Target)
{
    TestCombatAction* Action = new TestCombatAction(Target);
    this->CurrentTarget->CombatAction = Action;

    this->FinishedDecision = true;
}

TArray<UGameCharacter*> UCombatUIWidget::GetCharacterTargets()
{
    if (this->CurrentTarget->IsPlayer)
    {
        return this->CurrentTarget->CombatInstance->EnemyParty;
    }
    else
    {
        return this->CurrentTarget->CombatInstance->PlayerParty;
    }
}
