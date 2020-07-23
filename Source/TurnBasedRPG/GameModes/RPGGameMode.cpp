// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGGameMode.h"


#include "Kismet/GameplayStatics.h"
#include "TurnBasedRPG/Characters/RPGCharacter.h"
#include "TurnBasedRPG/Management/RPGGameInstance.h"
#include "TurnBasedRPG/Characters/GameCharacter.h"
#include "TurnBasedRPG/Combat/CombatEngine.h"

ARPGGameMode::ARPGGameMode(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    DefaultPawnClass = ARPGCharacter::StaticClass();
}

void ARPGGameMode::BeginPlay()
{
    Cast<URPGGameInstance>(GetGameInstance())->Init();
}

void ARPGGameMode::Tick(float DeltaSeconds)
{
    if (this->CurrentCombatInstance != nullptr)
    {
        bool CombatOver = this->CurrentCombatInstance->Tick(DeltaSeconds);

        if (CombatOver)
        {
            // if the combat is over
            if (this->CurrentCombatInstance->Phase == CombatPhase::CPHASE_GameOver)
            {
                UE_LOG(LogTemp, Warning, TEXT("Player loses combat, game over"));
            }
            else if (this->CurrentCombatInstance->Phase == CombatPhase::CPHASE_Victory)
            {
                UE_LOG(LogTemp, Warning, TEXT("Player wins combat"));
            }

            UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;

            // enable player actor
            UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetActorTickEnabled(true);

            // clear up
            for (int i = 0; i < this->CurrentCombatInstance->PlayerParty.Num(); i++)
            {
                this->CurrentCombatInstance->PlayerParty[i]->DecisionMaker = nullptr;
            }
            
            this->CombatUIInstance->RemoveFromViewport();
            this->CombatUIInstance = nullptr;
            
            delete(this->CurrentCombatInstance);
            this->CurrentCombatInstance = nullptr;
            this->EnemyParty.Empty();
        }
    }
}

void ARPGGameMode::TestCombat()
{
    // locate enemies asset
    UDataTable* EnemyTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, TEXT("DataTable'/Game/Data/DT_Enemies.DT_Enemies'")));

    if (EnemyTable == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Enemies data table not found on: RPGGameMode.cpp"));
        return;
    }

    // locate enemy
    FEnemyInfo* Row = EnemyTable->FindRow<FEnemyInfo>(TEXT("S1"), TEXT("LookupEnemyInfo"));

    if (Row == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Enemy ID 'S1' not found on: RPGGameMode.cpp"));
        return;
    }

    // disable player actor
    UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetActorTickEnabled(false);

    // add character to enemy party
    UGameCharacter* Enemy = UGameCharacter::CreateGameCharacter(Row, this);
    this->EnemyParty.Add(Enemy);

    URPGGameInstance* GameInstance = Cast<URPGGameInstance>(GetGameInstance());

    this->CurrentCombatInstance = new CombatEngine(GameInstance->PartyMembers, this->EnemyParty);

    UE_LOG(LogTemp, Warning, TEXT("Combat Test Started!"));

    this->CombatUIInstance = CreateWidget<UCombatUIWidget>(GetGameInstance(), this->CombatUIClass);
    this->CombatUIInstance->AddToViewport();

    UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;

    for(int i = 0; i < GameInstance->PartyMembers.Num(); i++)
    {
        this->CombatUIInstance->AddPlayerCharacterPanel(GameInstance->PartyMembers[i]);
        GameInstance->PartyMembers[i]->DecisionMaker = this->CombatUIInstance;
    }

    for (int i = 0; i < this->EnemyParty.Num(); i++)
    {
        this->CombatUIInstance->AddEnemyCharacterPanel(this->EnemyParty[i]);
    }
}
