// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "EnemyInfo.generated.h"

USTRUCT(BlueprintType)
struct FEnemyInfo : public FTableRowBase
{
    GENERATED_BODY();

public:
    UPROPERTY( BlueprintReadWrite, EditAnywhere, Category = "EnemyInfo" )
    FString EnemyName;

    UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "EnemyInfo" )
    int32 MHP;

    UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "EnemyInfo" )
    int32 ATK;

    UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "EnemyInfo" )
    int32 DEF;

    UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "EnemyInfo" )
    int32 Luck;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "EnemyInfo")
    int32 Gold;

    UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "EnemyInfo" )
    TArray<FString> Abilities;
};
