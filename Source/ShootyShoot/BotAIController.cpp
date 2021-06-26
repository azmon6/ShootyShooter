// Fill out your copyright notice in the Description page of Project Settings.


#include "BotAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShootyCharacter.h"

void ABotAIController::BeginPlay()
{
	Super::BeginPlay();

	//Running Behavior trees for better AI and less hardcoding 
	if (AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);

		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}

}

void ABotAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

bool ABotAIController::IsDead() const
{
	AShootyCharacter* ControlledCharacter = Cast<AShootyCharacter>(GetPawn());
	if (ControlledCharacter != nullptr)
	{
		return ControlledCharacter->IsDead();
	}

	return true;
}
