// Fill out your copyright notice in the Description page of Project Settings.


#include "KillAllGameMode.h"
#include "ShootyPlayerController.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "BotAIController.h"

void AKillAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

    AShootyPlayerController* PlayerController = Cast<AShootyPlayerController>(PawnKilled->GetController());
    if (PlayerController != nullptr)
    {
        EndGame(false);
    }

    for (ABotAIController* Controller : TActorRange<ABotAIController>(GetWorld()))
    {
        if (!Controller->IsDead())
        {
            return;
        }
    }

    EndGame(true);


}

void AKillAllGameMode::EndGame(bool bIsPlayerWinner)
{
    for (AController* Controller : TActorRange<AController>(GetWorld()))
    {
        bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
    }
}
