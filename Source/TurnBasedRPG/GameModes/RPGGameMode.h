// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "RPGGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TURNBASEDRPG_API ARPGGameMode : public AGameMode
{
    GENERATED_BODY()

public:
    ARPGGameMode(const class FObjectInitializer& ObjectInitializer);

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    class CombatEngine* CurrentCombatInstance;
    TArray<class UGameCharacter*> EnemyParty;

    UFUNCTION(Exec)
    void TestCombat();
};
