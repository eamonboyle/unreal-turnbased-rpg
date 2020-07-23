// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CombatAction.h"

class TURNBASEDRPG_API TestCombatAction : public ICombatAction
{
protected:
    float DelayTimer;
    UGameCharacter* Character;
    UGameCharacter* Target;

public:
    TestCombatAction(UGameCharacter* Target);
    
    virtual void BeginExecuteAction(UGameCharacter* Character) override;
    virtual bool ExecuteAction(float DeltaSeconds) override;
};
