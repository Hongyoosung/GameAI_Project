// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"
#include "MoveToState.generated.h"

/**
 * 
 */
class UAction;

UCLASS()
class GAMEAI_PROJECT_API UMoveToState : public UState
{
	GENERATED_BODY()
	
public:
	virtual void EnterState(UStateMachine* StateMachine) override;
	virtual void UpdateState(UStateMachine* StateMachine, float DeltaTime) override;
	virtual void ExitState(UStateMachine* StateMachine) override;

	// Override to return possible actions
	virtual TArray<UAction*> GetPossibleActions() override;
};
