// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackState.h"
#include "StateMachine.h"

void UAttackState::EnterState(UStateMachine* StateMachine)
{
	Super::EnterState(StateMachine);
}

void UAttackState::UpdateState(UStateMachine* StateMachine, float DeltaTime)
{

}

void UAttackState::ExitState(UStateMachine* StateMachine)
{

}

TArray<UAction*> UAttackState::GetPossibleActions()
{
	return TArray<UAction*>();
}
