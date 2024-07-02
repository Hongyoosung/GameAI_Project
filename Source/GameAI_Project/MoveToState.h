// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"
#include "MCTS.h"
#include "MoveToState.generated.h"

/**
 * 
 */
class UAction;

UCLASS(Blueprintable)
class GAMEAI_PROJECT_API UMoveToState : public UState
{
	GENERATED_BODY()
	
public:
	virtual void EnterState(UStateMachine* StateMachine) override;

	virtual void UpdateState(UStateMachine* StateMachine, float Reward, float DeltaTime) override;
	virtual void ExitState(UStateMachine* StateMachine) override;
	virtual TArray<UAction*> GetPossibleActions() override;
	virtual void ResetCurrentNode() override;

private:
	UMCTS* MCTS;
	UMCTSNode* BestChild;
	TArray<UAction*> PossibleActions;
};
