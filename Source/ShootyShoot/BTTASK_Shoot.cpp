// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTASK_Shoot.h"
#include "BotAIController.h"
#include "ShootyCharacter.h"

UBTTASK_Shoot::UBTTASK_Shoot()
{
    NodeName = "Shoot";
}

EBTNodeResult::Type UBTTASK_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if (OwnerComp.GetAIOwner() == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    AShootyCharacter* Character = Cast<AShootyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
    if (Character == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    Character->Shoot();

    return EBTNodeResult::Succeeded;
}
