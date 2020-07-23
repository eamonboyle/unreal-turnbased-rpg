// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGGameInstance.h"

#include "TurnBasedRPG/Characters/GameCharacter.h"

URPGGameInstance::URPGGameInstance(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    IsInitialized = false;
}

void URPGGameInstance::Init()
{
    if (this->IsInitialized) return;

    // locate the characters asset
    UDataTable* Characters = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, TEXT("DataTable'/Game/Data/DT_Characters.DT_Characters'")));

    if (Characters == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Characters Data Table not found on RPGGameInstance"));
        return;
    }

    // locate character
    FCharacterInfo* Row = Characters->FindRow<FCharacterInfo>(TEXT("S1"), TEXT("LookupCharacterClass"));

    if (Row == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Character ID 'S1' not found on RPGGameInstance"));
        return;
    }

    // add character to party
    this->PartyMembers.Add(UGameCharacter::CreateGameCharacter(Row, this));

    this->IsInitialized = true;
}

void URPGGameInstance::PrepareReset()
{
    this->IsInitialized = false;
    this->PartyMembers.Empty();
}
