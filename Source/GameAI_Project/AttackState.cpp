// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackState.h"
#include "StateMachine.h"
#include "MCTS.h"

void UAttackState::EnterState(UStateMachine* StateMachine)
{
	UE_LOG(LogTemp, Warning, TEXT("Attack State Attack State Attack State Attack State"));

	
}

void UAttackState::UpdateState(UStateMachine* StateMachine, float DeltaTime)
{
	UE_LOG(LogTemp, Warning, TEXT("Default Attacking"));
	StateMachine->TriggerBlueprintEvent("Default Attack");
}

void UAttackState::ExitState(UStateMachine* StateMachine)
{

}


TArray<UAction*> UAttackState::GetPossibleActions()
{
	return TArray<UAction*>();
}
