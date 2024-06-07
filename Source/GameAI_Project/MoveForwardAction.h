// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "MoveForwardAction.generated.h"

/**
 * 
 */
UCLASS()
class GAMEAI_PROJECT_API UMoveForwardAction : public UAction
{
	GENERATED_BODY()
	
public:
	virtual void ExecuteAction(UStateMachine* StateMachine) override;
};
