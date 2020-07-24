// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RPGGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TURNBASEDRPG_API URPGGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    URPGGameInstance(const class FObjectInitializer& ObjectInitializer);

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Data")
    TArray<class UGameCharacter*> PartyMembers;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game Data");
    bool TalkShop;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Data")
    int32 GameGold;

protected:
    bool IsInitialized;

public:
    virtual void Init() override;

    void PrepareReset();
};
