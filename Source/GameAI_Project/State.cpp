// Fill out your copyright notice in the Description page of Project Settings.


#include "State.h"
#include "StateMachine.h"
#include "Action.h"

void UState::EnterState(UStateMachine* StateMachine)
{
    // 상태가 시작될 때 수행할 작업
    
}

void UState::ExitState(UStateMachine* StateMachine)
{
    // 상태가 종료될 때 수행할 작업
}

void UState::UpdateState(UStateMachine* StateMachine, float DeltaTime)
{

}


TArray<UAction*> UState::GetPossibleActions()
{
    return TArray<UAction*>();
}


