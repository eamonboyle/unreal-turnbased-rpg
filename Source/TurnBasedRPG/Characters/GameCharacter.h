// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurnBasedRPG/Actions/CombatAction.h"
#include "TurnBasedRPG/Data/CharacterInfo.h"
#include "TurnBasedRPG/Data/CharacterClassInfo.h"
#include "TurnBasedRPG/Combat/CombatEngine.h"
#include "TurnBasedRPG/Data/EnemyInfo.h"
#include "TurnBasedRPG/DecisionMakers/DecisionMaker.h"



#include "GameCharacter.generated.h"

class CombatEngine;

UCLASS(BlueprintType)
class TURNBASEDRPG_API UGameCharacter : public UObject
{
    GENERATED_BODY()

public:
    FCharacterClassInfo* ClassInfo;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterInfo)
    FString CharacterName;

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = CharacterInfo )
    int32 MHP;

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = CharacterInfo )
    int32 MMP;

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = CharacterInfo )
    int32 HP;

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = CharacterInfo )
    int32 MP;

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = CharacterInfo )
    int32 ATK;

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = CharacterInfo )
    int32 DEF;

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = CharacterInfo )
    int32 LUCK;

    CombatEngine* CombatInstance;

    static UGameCharacter* CreateGameCharacter(FCharacterInfo* CharacterInfo, UObject* Outer);
    static UGameCharacter* CreateGameCharacter(FEnemyInfo* EnemyInfo, UObject* Outer);

    virtual void BeginDestroy() override;

public:
    ICombatAction* CombatAction;
    IDecisionMaker* DecisionMaker;

public:
    void BeginMakeDecision();
    bool MakeDecision(float DeltaSeconds);

    void BeginExecuteAction();
    bool ExecuteAction(float DeltaSeconds);
};
