// Fill out your copyright notice in the Description page of Project Settings.

#include "MoveToState.h"
#include "StateMachine.h"
#include "MoveForwardAction.h"
#include "MoveBackwardAction.h"
#include "MoveLeftAction.h"
#include "MoveRightAction.h"

void UMoveToState::EnterState(UStateMachine* StateMachine)
{
    PossibleActions = GetPossibleActions();

    if (MCTS == nullptr)
    {
        MCTS = NewObject<UMCTS>();
    }

    UE_LOG(LogTemp, Warning, TEXT("Entered MoveToState"));

    MCTS->InitializeMCTS();
}

void UMoveToState::UpdateState(UStateMachine* StateMachine, float DeltaTime)
{
    if (!MCTS->CurrentNode)
    {
        return;
    }

    if (MCTS->CurrentNode->Children.Num() == 0)
    {
        MCTS->Expand(PossibleActions);
    }

    // 최적의 행동 선택
    UMCTSNode* BestChild = MCTS->SelectChildNode();

    if (BestChild)
    {
        UE_LOG(LogTemp, Warning, TEXT("BestChild is valid"));

        if (BestChild->Action)
        {
            UE_LOG(LogTemp, Warning, TEXT("BestChild->Action is valid"));
            BestChild->Action->ExecuteAction(StateMachine);

            // 현재 노드를 최적의 자식 노드로 설정
            MCTS->CurrentNode = BestChild;
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
        float Reward = MCTS->Simulate();
        MCTS->Backpropagate(MCTS->CurrentNode, Reward);
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
