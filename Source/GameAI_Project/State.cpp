// Fill out your copyright notice in the Description page of Project Settings.


#include "State.h"
#include "StateMachine.h"
#include "Action.h"

void UState::EnterState(UStateMachine* StateMachine)
{
    // ���°� ���۵� �� ������ �۾�
    
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
    
}

TArray<UAction*> UState::GetPossibleActions()
{
    return TArray<UAction*>();
}


