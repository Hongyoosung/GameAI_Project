// Fill out your copyright notice in the Description page of Project Settings.


#include "State.h"
#include "StateMachine.h"
#include "Action.h"
#include "MCTSNode.h"

void UState::EnterState(UStateMachine* StateMachine)
{
    // 상태가 시작될 때 수행할 작업
    PossibleActions = GetPossibleActions();
}

void UState::ExitState(UStateMachine* StateMachine)
{
    // 상태가 종료될 때 수행할 작업
}

void UState::UpdateState(UStateMachine* StateMachine, float DeltaTime)
{
    // 상태가 업데이트될 때 수행할 작업
    ExcuteMCTS(StateMachine);
}


void UState::ExcuteMCTS(UStateMachine* StateMachine)
{
    if (RootNode == nullptr)
    {
        RootNode = NewObject<UMCTSNode>();
    }

    // MCTS 트리 확장 및 시뮬레이션
    RootNode->Expand(PossibleActions);

    // 최적의 행동 선택
    UMCTSNode* BestChild = RootNode->SelectChildNode();
    if (BestChild && BestChild->Action)
    {
        BestChild->Action->ExecuteAction(StateMachine);
    }
}

TArray<UAction*> UState::GetPossibleActions()
{
    return TArray<UAction*>();
}


