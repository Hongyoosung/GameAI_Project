// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"
#include "AttackState.generated.h"

/**
 * 
 */
UCLASS()
class GAMEAI_PROJECT_API UAttackState : public UState
{
	GENERATED_BODY()
	
public:
	virtual void EnterState(UStateMachine* StateMachine) override;
	virtual void UpdateState(UStateMachine* StateMachine, float DeltaTime) override;
	virtual void ExitState(UStateMachine* StateMachine) override;
	virtual void ExcuteMCTS(UStateMachine* StateMachine) override;
	virtual TArray<UAction*> GetPossibleActions() override;

private:
	UMCTS* MCTS;

	TArray<UAction*> PossibleActions;
};
