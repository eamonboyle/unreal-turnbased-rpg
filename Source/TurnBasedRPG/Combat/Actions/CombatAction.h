// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class UGameCharacter;

class TURNBASEDRPG_API ICombatAction
{
public:
    virtual ~ICombatAction();
    
    virtual void BeginExecuteAction(UGameCharacter* Character) = 0;
    virtual bool ExecuteAction(float DeltaSeconds) = 0;
};
