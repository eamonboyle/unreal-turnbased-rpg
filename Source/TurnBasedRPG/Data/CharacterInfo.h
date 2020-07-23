// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "CharacterInfo.generated.h"

USTRUCT(BlueprintType)
struct FCharacterInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterInfo")
	FString Character_Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterInfo")
	FString Class_ID;
};