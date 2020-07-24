// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum class CombatPhase : uint8
{
    CPHASE_Decision,
    CPHASE_Action,
    CPHASE_Victory,
    CPHASE_GameOver
};

class UGameCharacter;

class TURNBASEDRPG_API CombatEngine
{
public:
    TArray<UGameCharacter*> CombatantOrder;
    TArray<UGameCharacter*> PlayerParty;
    TArray<UGameCharacter*> EnemyParty;

    CombatPhase Phase;

    int32 GoldTotal;

protected:
    UGameCharacter* CurrentTickTarget;
    int TickTargetIndex;

public:
    CombatEngine(TArray<UGameCharacter*> NewPlayerParty, TArray<UGameCharacter*> NewEnemyParty);
    ~CombatEngine();

    bool Tick(float DeltaSeconds);

protected:
    void SetPhase(CombatPhase NewPhase);
    void SelectNextCharacter();

    bool WaitingForCharacter;
};
