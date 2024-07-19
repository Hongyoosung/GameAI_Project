// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackState.h"
#include "StateMachine.h"
#include "SkillAttackAction.h"
#include "DeafultAttackAction.h"

void UAttackState::EnterState(UStateMachine* StateMachine)
{
	UE_LOG(LogTemp, Warning, TEXT("Entered Attack State"));

	if (MCTS == nullptr)
	{
		MCTS = NewObject<UMCTS>();
		MCTS->InitializeMCTS();
		MCTS->InitializeCurrentNodeLocate();
		PossibleActions = GetPossibleActions();
	}
	else
	{
		MCTS->InitializeCurrentNodeLocate();
	}
}

void UAttackState::UpdateState(UStateMachine* StateMachine, float Reward, float DeltaTime)
{
	if (MCTS == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("MCTS or CurrentNode is nullptr"));
		return;
	}

	MCTS->RunMCTS(PossibleActions, StateMachine);
}

void UAttackState::ExitState(UStateMachine* StateMachine)
{
	if (MCTS)
	{
		MCTS->Backpropagate();
		UE_LOG(LogTemp, Warning, TEXT("Exited Attack State"));
	}
}


TArray<UAction*> UAttackState::GetPossibleActions()
{
	TArray<UAction*> Actions;

	Actions.Add(NewObject<USkillAttackAction>(this, USkillAttackAction::StaticClass()));
	Actions.Add(NewObject<UDeafultAttackAction>(this, UDeafultAttackAction::StaticClass()));


	return Actions;
}
