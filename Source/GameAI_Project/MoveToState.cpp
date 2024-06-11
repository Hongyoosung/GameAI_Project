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
}

void UMoveToState::UpdateState(UStateMachine* StateMachine, float Reward, float DeltaTime)
{

	if (!MCTS->CurrentNode)
	{
		return;
	}

	if (MCTS->CurrentNode->Children.IsEmpty() && TreeDepth <= 10)
	{
		MCTS->Expand(PossibleActions);
		TreeDepth++;

	}

	BestChild = MCTS->SelectChildNode(Reward);

	if (BestChild)
	{
		UE_LOG(LogTemp, Warning, TEXT("BestChild is valid"));

		if (BestChild->Action)
		{
			UE_LOG(LogTemp, Warning, TEXT("BestChild->Action is valid"));
			BestChild->Action->ExecuteAction(StateMachine);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("BestChild->Action is nullptr"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("BestChild is nullptr"));
		// BestChild가 nullptr인 경우 CurrentNode를 루트 노드로 재설정하여 문제 방지
		MCTS->CurrentNode = MCTS->RootNode;
	}
}

void UMoveToState::ExitState(UStateMachine* StateMachine)
{
    if (MCTS)
    {
        UE_LOG(LogTemp, Warning, TEXT("Exited MoveToState"));
        //float Reward = MCTS->Simulate();
        //MCTS->Backpropagate(MCTS->CurrentNode, Reward);
        MCTS->CurrentNode = MCTS->RootNode;
        TreeDepth = 0;
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
