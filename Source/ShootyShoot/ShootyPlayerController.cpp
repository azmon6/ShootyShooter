// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootyPlayerController.h"

#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShootyPlayerController::BeginPlay()
{
    Super::BeginPlay();

    HUD = CreateWidget(this, HUDClass);
    if (HUD != nullptr)
    {
        HUD->AddToViewport();
    }
}


void AShootyPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    //REMOVE HUD AFTER GAME END
    HUD->RemoveFromViewport();
    //WE ADD WIDGET FOR LOSESCREEN FOR PLAYER
    if (bIsWinner)
    {
        UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
        if (WinScreen != nullptr)
        {
            WinScreen->AddToViewport();
        }

    }
    else
    {
        UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
        if (LoseScreen != nullptr)
        {
            LoseScreen->AddToViewport();
        }
    }

    //RESTART GAME FOR PLAYER
    GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}
