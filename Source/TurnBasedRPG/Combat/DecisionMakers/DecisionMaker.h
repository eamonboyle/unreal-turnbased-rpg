// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class UGameCharacter;

/**
 * 
 */
class TURNBASEDRPG_API IDecisionMaker
{
public:
    virtual ~IDecisionMaker();
    
    virtual void BeginMakeDecision(UGameCharacter* Character) = 0;
    virtual bool MakeDecision(float DeltaSeconds) = 0;
};
