// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTASK_Shoot.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTYSHOOT_API UBTTASK_Shoot : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTASK_Shoot();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
