// Fill out your copyright notice in the Description page of Project Settings.

#include "MoveToState.h"
#include "StateMachine.h"
#include "MoveForwardAction.h"
#include "MoveBackwardAction.h"
#include "MoveLeftAction.h"
#include "MoveRightAction.h"

void UMoveToState::EnterState(UStateMachine* StateMachine)
{
    UE_LOG(LogTemp, Warning, TEXT("Entered MoveToState"));

    if (MCTS == nullptr)
    {
        MCTS = NewObject<UMCTS>();
        MCTS->InitializeMCTS();
        PossibleActions = GetPossibleActions();
    }
    else
    {
		MCTS->CurrentNode = MCTS->RootNode;
	}
}

void UMoveToState::UpdateState(UStateMachine* StateMachine, float Reward, float DeltaTime)
{

	if (!MCTS->CurrentNode)
	{
		return;
	}

    MCTS->RunMCTS(PossibleActions, Reward, StateMachine);
}


void UMoveToState::ExitState(UStateMachine* StateMachine)
{
    if (MCTS)
    {
        UE_LOG(LogTemp, Warning, TEXT("Exited MoveToState"));
        //float Reward = MCTS->Simulate();
        //MCTS->Backpropagate(MCTS->CurrentNode, Reward);
        MCTS->CurrentNode = MCTS->RootNode;
    }
}

TArray<UAction*> UMoveToState::GetPossibleActions()
{
    TArray<UAction*> Actions;

    Actions.Add(NewObject<UMoveForwardAction>(this, UMoveForwardAction::StaticClass()));
    Actions.Add(NewObject<UMoveBackwardAction>(this, UMoveBackwardAction::StaticClass()));
    Actions.Add(NewObject<UMoveLeftAction>(this, UMoveLeftAction::StaticClass()));
    Actions.Add(NewObject<UMoveRightAction>(this, UMoveRightAction::StaticClass()));

    return Actions;
}

void UMoveToState::ResetCurrentNode()
{
    MCTS->CurrentNode = MCTS->RootNode;
}
