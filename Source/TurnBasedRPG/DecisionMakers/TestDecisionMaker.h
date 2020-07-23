// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DecisionMaker.h"

class TURNBASEDRPG_API TestDecisionMaker : public IDecisionMaker
{
public:
    virtual void BeginMakeDecision(UGameCharacter* Character) override;
    virtual bool MakeDecision(float DeltaSeconds) override;
};
