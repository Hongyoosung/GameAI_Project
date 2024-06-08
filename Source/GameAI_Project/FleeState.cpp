// Fill out your copyright notice in the Description page of Project Settings.


#include "FleeState.h"
#include "StateMachine.h"

void UFleeState::EnterState(UStateMachine* StateMachine)
{
	Super::EnterState(StateMachine);
}

void UFleeState::UpdateState(UStateMachine* StateMachine, float DeltaTime)
{

}

void UFleeState::ExitState(UStateMachine* StateMachine)
{

}

void UFleeState::ExcuteMCTS(UStateMachine* StateMachine)
{

}

TArray<UAction*> UFleeState::GetPossibleActions()
{
	return TArray<UAction*>();
}
