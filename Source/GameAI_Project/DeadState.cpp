// Fill out your copyright notice in the Description page of Project Settings.


#include "DeadState.h"
#include "StateMachine.h"

void UDeadState::EnterState(UStateMachine* StateMachine)
{
    Super::EnterState(StateMachine);
}

void UDeadState::UpdateState(UStateMachine* StateMachine, float DeltaTime)
{

}

void UDeadState::ExitState(UStateMachine* StateMachine)
{

}

void UDeadState::ExcuteMCTS(UStateMachine* StateMachine)
{

}

TArray<UAction*> UDeadState::GetPossibleActions()
{
    return TArray<UAction*>();
}
