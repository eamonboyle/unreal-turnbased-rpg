// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCharacter.h"

#include "TurnBasedRPG/Actions/TestCombatAction.h"
#include "TurnBasedRPG/DecisionMakers/TestDecisionMaker.h"

UGameCharacter* UGameCharacter::CreateGameCharacter(FCharacterInfo* CharacterInfo, UObject* Outer)
{
    UGameCharacter* Character = NewObject<UGameCharacter>(Outer);

    // locate character classes asset
    UDataTable* CharacterClasses = Cast<UDataTable>(
        StaticLoadObject(
            UDataTable::StaticClass(),
            nullptr,
            TEXT("DataTable'/Game/Data/DT_CharacterClasses.DT_CharacterClasses'")
        )
    );

    if (CharacterClasses == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Character Classes datatable not found!"));
        return nullptr;
    }

    Character->CharacterName = CharacterInfo->Character_Name;
    FCharacterClassInfo* Row = CharacterClasses->FindRow<FCharacterClassInfo>(
        *(CharacterInfo->Class_ID), TEXT("LookupCharacterClass"));

    if (Row != nullptr)
    {
        // setup the player character
        Character->ClassInfo = Row;
        Character->MHP = Character->ClassInfo->StartMHP;
        Character->MMP = Character->ClassInfo->StartMMP;
        Character->HP = Character->MHP;
        Character->MP = Character->MMP;

        Character->ATK = Character->ClassInfo->StartATK;
        Character->DEF = Character->ClassInfo->StartDEF;
        Character->LUCK = Character->ClassInfo->StartLuck;

        Character->DecisionMaker = new TestDecisionMaker();
    }

    Character->IsPlayer = true;

    return Character;
}

UGameCharacter* UGameCharacter::CreateGameCharacter(FEnemyInfo* EnemyInfo, UObject* Outer)
{
    UGameCharacter* Character = NewObject<UGameCharacter>(Outer);

    if (Character == nullptr)
    {
        return nullptr;
    }

    // set up the enemy character
    Character->CharacterName = EnemyInfo->EnemyName;
    Character->ClassInfo = nullptr;

    Character->MHP = EnemyInfo->MHP;
    Character->MMP = 0;
    Character->HP = EnemyInfo->MHP;
    Character->MP = 0;

    Character->ATK = EnemyInfo->ATK;
    Character->DEF = EnemyInfo->DEF;
    Character->LUCK = EnemyInfo->Luck;

    Character->DecisionMaker = new TestDecisionMaker();

    Character->IsPlayer = false;

    return Character;
}

void UGameCharacter::BeginDestroy()
{
    Super::BeginDestroy();

    delete(this->DecisionMaker);
}

UGameCharacter* UGameCharacter::SelectTarget()
{
    UGameCharacter* Target = nullptr;

    // initialise with enemies
    TArray<UGameCharacter*> TargetList = this->CombatInstance->EnemyParty;

    // if it is the enemy, set target to players team
    if (!this->IsPlayer)
    {
        TargetList = this->CombatInstance->PlayerParty;
    }

    // loop through the target list and pull out the first target that
    // is alive
    for (int i = 0; i < TargetList.Num(); i++)
    {
        if (TargetList[i]->HP > 0)
        {
            Target = TargetList[i];
            break;
        }
    }

    // if the target is dead return null
    if (Target->HP <= 0)
    {
        return nullptr;
    }

    return Target;
}

void UGameCharacter::BeginMakeDecision()
{
    this->DecisionMaker->BeginMakeDecision(this);
}

bool UGameCharacter::MakeDecision(float DeltaSeconds)
{
    return this->DecisionMaker->MakeDecision(DeltaSeconds);
}

void UGameCharacter::BeginExecuteAction()
{
    this->CombatAction->BeginExecuteAction(this);
}

bool UGameCharacter::ExecuteAction(float DeltaSeconds)
{
    bool FinishedAction = this->CombatAction->ExecuteAction(DeltaSeconds);

    if (FinishedAction)
    {
        delete(this->CombatAction);
        return true;
    }

    return false;
}
