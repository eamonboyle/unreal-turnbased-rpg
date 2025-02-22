// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "MyNewActor.generated.h"

UCLASS()
class TURNBASEDRPG_API AMyNewActor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AMyNewActor();

    // Called every frame
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "My New Actor")
    UDataTable* DataTable;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
};
