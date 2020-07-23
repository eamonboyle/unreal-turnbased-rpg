// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCharacter.h"

UGameCharacter* UGameCharacter::CreateGameCharacter(FCharacterInfo* CharacterInfo, UObject* Outer)
{
    UGameCharacter* Character = NewObject<UGameCharacter>(Outer);

    // locate character classes asset
    UDataTable* CharacterClasses = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, TEXT("DataTable'/Game/Data/DT_CharacterClasses.DT_CharacterClasses'")));

    if (CharacterClasses == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Character Classes datatable not found!"));
        return nullptr;
    }

    Character->CharacterName = CharacterInfo->Character_Name;
    FCharacterClassInfo* Row = CharacterClasses->FindRow<FCharacterClassInfo>(*(CharacterInfo->Class_ID), TEXT("LookupCharacterClass"));

    if (Row != nullptr)
    {
        Character->ClassInfo = Row;
        Character->MHP = Character->ClassInfo->StartMHP;
        Character->MMP = Character->ClassInfo->StartMMP;
        Character->HP = Character->MHP;
        Character->MP = Character->MMP;

        Character->ATK = Character->ClassInfo->StartATK;
        Character->DEF = Character->ClassInfo->StartDEF;
        Character->LUCK = Character->ClassInfo->StartLuck;
    }

    return Character;
}

void UGameCharacter::BeginDestroy()
{
    Super::BeginDestroy();
}
