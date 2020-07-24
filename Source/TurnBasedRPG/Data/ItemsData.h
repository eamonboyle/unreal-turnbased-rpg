// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "ItemsData.generated.h"

USTRUCT(BlueprintType)
struct FItemsData : public FTableRowBase
{
    GENERATED_BODY();

public:
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ItemData")
    FString DisplayName;
    
    UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "ItemData" )
    int32 HP;

    UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "ItemData" )
    int32 MP;

    UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "ItemData" )
    int32 ATK;

    UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "ItemData" )
    int32 DEF;

    UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "ItemData" )
    int32 Luck;

    UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "ItemData" )
    int32 Gold;
};
