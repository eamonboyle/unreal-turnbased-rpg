// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TurnBasedRPG/Combat/DecisionMakers/DecisionMaker.h"

#include "CombatUIWidget.generated.h"

class UGameCharacter;

UCLASS()
class TURNBASEDRPG_API UCombatUIWidget : public UUserWidget, public IDecisionMaker
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintImplementableEvent, Category = "Combat UI")
    void AddPlayerCharacterPanel(UGameCharacter* Target);

    UFUNCTION(BlueprintImplementableEvent, Category = "Combat UI")
    void AddEnemyCharacterPanel(UGameCharacter* Target);

    void BeginMakeDecision(UGameCharacter* Target);
    bool MakeDecision(float DeltaSeconds);

    UFUNCTION(BlueprintCallable, Category = "Combat UI")
    TArray<UGameCharacter*> GetCharacterTargets();

    UFUNCTION(BlueprintCallable, Category = "Combat UI")
    void AttackTarget(UGameCharacter* Target);

    UFUNCTION(BlueprintImplementableEvent, Category = "Combat UI")
    void ShowActionsPanel(UGameCharacter* Target);

protected:
    UGameCharacter* CurrentTarget;

    bool FinishedDecision;
};
