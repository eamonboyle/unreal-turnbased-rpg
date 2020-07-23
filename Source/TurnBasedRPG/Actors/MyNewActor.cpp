// Fill out your copyright notice in the Description page of Project Settings.


#include "MyNewActor.h"
#include "TestCustomData.h"

// Sets default values
AMyNewActor::AMyNewActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyNewActor::BeginPlay()
{
    Super::BeginPlay();

    GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("Hello, world!"));

    if (DataTable != nullptr)
    {
        FTestCustomData* Row = DataTable->FindRow<FTestCustomData>(TEXT("2"), TEXT("LookupTestCustomData"));
        FString SomeString = Row->SomeString;
        int32 SomeNumber = Row->SomeNumber;

        UE_LOG(LogTemp, Warning, TEXT("%s"), *SomeString);
    }
}

// Called every frame
void AMyNewActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
