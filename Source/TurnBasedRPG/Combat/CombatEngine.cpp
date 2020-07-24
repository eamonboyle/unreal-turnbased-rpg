// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatEngine.h"

#include "TurnBasedRPG/Characters/GameCharacter.h"

CombatEngine::CombatEngine(TArray<UGameCharacter*> NewPlayerParty, TArray<UGameCharacter*> NewEnemyParty)
{
    this->PlayerParty = NewPlayerParty;
    this->EnemyParty = NewEnemyParty;

    // first add all of the players to combat order
    for (int i = 0; i < PlayerParty.Num(); i++)
    {
        this->CombatantOrder.Add(PlayerParty[i]);
    }

    // next add all enemies to combat order
    for (int i = 0; i < EnemyParty.Num(); i++)
    {
        this->CombatantOrder.Add(EnemyParty[i]);
    }

    this->TickTargetIndex = 0;
    this->SetPhase(CombatPhase::CPHASE_Decision);

    // set the combat instance on each character
    for (int i = 0; i < this->CombatantOrder.Num(); i++)
    {
        this->CombatantOrder[i]->CombatInstance = this;
    }
}

CombatEngine::~CombatEngine()
{
    // free enemies
    for (int i = 0; i < this->EnemyParty.Num(); i++)
    {
        this->EnemyParty[i] = nullptr;
    }

    // free combat instances
    for (int i = 0; i < this->CombatantOrder.Num(); i++)
    {
        this->CombatantOrder[i]->CombatInstance = nullptr;
    }
}

bool CombatEngine::Tick(float DeltaSeconds)
{
    switch (Phase)
    {
    case CombatPhase::CPHASE_Decision:
        {
            if (!this->WaitingForCharacter)
            {
                this->CurrentTickTarget->BeginMakeDecision();
                this->WaitingForCharacter = true;
            }

            bool DecisionMade = this->CurrentTickTarget->MakeDecision(DeltaSeconds);

            if (DecisionMade)
            {
                SelectNextCharacter();

                // no next character, switch to action phase
                if (this->TickTargetIndex == -1)
                {
                    this->SetPhase(CombatPhase::CPHASE_Action);
                }
            }
        }
        break;
    case CombatPhase::CPHASE_Action:
        {
            if (!this->WaitingForCharacter)
            {
                this->CurrentTickTarget->BeginExecuteAction();
                this->WaitingForCharacter = true;
            }

            bool ActionFinished = this->CurrentTickTarget->ExecuteAction(DeltaSeconds);

            if (ActionFinished)
            {
                SelectNextCharacter();

                // no next character, switch to decision phase
                if (this->TickTargetIndex == -1)
                {
                    this->SetPhase(CombatPhase::CPHASE_Decision);
                }
            }
        }
        break;
    case CombatPhase::CPHASE_GameOver:
    case CombatPhase::CPHASE_Victory:
        return true;
        break;
    }

    // check for game over
    int DeadCount = 0;
    for (int i = 0; i < this->PlayerParty.Num(); i++)
    {
        if (this->PlayerParty[i]->HP <= 0)
        {
            DeadCount++;
        }
    }

    // all players have died, switch to game over phase
    if (DeadCount == this->PlayerParty.Num())
    {
        this->SetPhase(CombatPhase::CPHASE_GameOver);
        return false;
    }

    // check for victory
    DeadCount = 0;
    int32 Gold = 0;
    int32 XP = 0;
    for (int i = 0; i < this->EnemyParty.Num(); i++)
    {
        if (this->EnemyParty[i]->HP <= 0)
        {
            DeadCount++;
        }

        Gold += this->EnemyParty[i]->Gold;
        XP += this->EnemyParty[i]->XP;
    }

    // all enemies have died, switch to victory phase
    if (DeadCount == this->EnemyParty.Num())
    {
        this->SetPhase(CombatPhase::CPHASE_Victory);
        GoldTotal = Gold;
        XPTotal = XP;
        return false;
    }

    // if execution reaches here, combat has not finished, return false
    return false;
}

void CombatEngine::SetPhase(CombatPhase NewPhase)
{
    this->Phase = NewPhase;

    switch (Phase)
    {
    case CombatPhase::CPHASE_Action:
    case CombatPhase::CPHASE_Decision:
        // set the active target to the first character in the combat order
        UE_LOG(LogTemp, Warning, TEXT("DECISION PHASE"));
        this->TickTargetIndex = 0;
        this->SelectNextCharacter();
        break;
    case CombatPhase::CPHASE_Victory:
        // TODO: handle victory
        UE_LOG(LogTemp, Warning, TEXT("VICTORY"));
        break;
    case CombatPhase::CPHASE_GameOver:
        // TODO: handle game over
        UE_LOG(LogTemp, Warning, TEXT("GAMEOVER"));
        break;
    }
}

void CombatEngine::SelectNextCharacter()
{
    this->WaitingForCharacter = false;
    
    for (int i = this->TickTargetIndex; i < this->CombatantOrder.Num(); i++)
    {
        UGameCharacter* Character = this->CombatantOrder[i];

        if (Character != nullptr)
        {
            if (Character->HP > 0)
            {
                this->TickTargetIndex = i + 1;
                this->CurrentTickTarget = Character;
                return;
            }
        }
    }

    this->TickTargetIndex = -1;
    this->CurrentTickTarget = nullptr;
}
