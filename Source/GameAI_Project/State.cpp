// Fill out your copyright notice in the Description page of Project Settings.


#include "State.h"
#include "StateMachine.h"
#include "Action.h"
#include "MCTSNode.h"

void UState::EnterState(UStateMachine* StateMachine)
{
    // ���°� ���۵� �� ������ �۾�
    PossibleActions = GetPossibleActions();
}

void UState::ExitState(UStateMachine* StateMachine)
{
    // ���°� ����� �� ������ �۾�
}

void UState::UpdateState(UStateMachine* StateMachine, float DeltaTime)
{
    // ���°� ������Ʈ�� �� ������ �۾�
    ExcuteMCTS(StateMachine);
}


void UState::ExcuteMCTS(UStateMachine* StateMachine)
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

TArray<UAction*> UState::GetPossibleActions()
{
    return TArray<UAction*>();
}


