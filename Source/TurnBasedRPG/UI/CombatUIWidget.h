// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CombatUIWidget.generated.h"

class UGameCharacter;

UCLASS()
class TURNBASEDRPG_API UCombatUIWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintImplementableEvent, Category = "Combat UI")
    void AddPlayerCharacterPanel(UGameCharacter* Target);

    UFUNCTION(BlueprintImplementableEvent, Category = "Combat UI")
    void AddEnemyCharacterPanel(UGameCharacter* Target);
};
