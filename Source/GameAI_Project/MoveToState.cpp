// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveToState.h"
#include "StateMachine.h"
#include "MoveForwardAction.h"
#include "MoveBackwardAction.h"
#include "MCTSNode.h"

void UMoveToState::EnterState(UStateMachine* StateMachine)
{
    PossibleActions = GetPossibleActions();
    UE_LOG(LogTemp, Warning, TEXT("Entered MoveToState"));
}

void UMoveToState::UpdateState(UStateMachine* StateMachine, float DeltaTime)
{
    ExitState(StateMachine);
}

void UMoveToState::ExitState(UStateMachine* StateMachine)
{
    if (RootNode == nullptr)
    {
        RootNode = NewObject<UMCTSNode>();
    }

    // MCTS Ʈ�� Ȯ�� �� �ùķ��̼�
    RootNode->Expand(PossibleActions);

    // ������ �ൿ ����
    UMCTSNode* BestChild = RootNode->SelectChildNode();
    if (BestChild && BestChild->Action)
    {
        BestChild->Action->ExecuteAction(StateMachine);
    }
}

TArray<UAction*> UMoveToState::GetPossibleActions()
{
    TArray<UAction*> Actions;

    Actions.Add(NewObject<UMoveForwardAction>(this, UMoveForwardAction::StaticClass()));
    Actions.Add(NewObject<UMoveBackwardAction>(this, UMoveBackwardAction::StaticClass()));

    return Actions;
}
