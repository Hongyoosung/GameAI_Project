// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackState.h"
#include "StateMachine.h"
#include "SkillAttackAction.h"
#include "DeafultAttackAction.h"

void UAttackState::EnterState(UStateMachine* StateMachine)
{
	if (MCTS == nullptr)
	{
		MCTS = NewObject<UMCTS>();
		MCTS->InitializeMCTS();
		PossibleActions = GetPossibleActions();
	}
	else
	{
		MCTS->CurrentNode = MCTS->RootNode;
	}

	UE_LOG(LogTemp, Warning, TEXT("Entered Attack State"));
}

void UAttackState::UpdateState(UStateMachine* StateMachine, float Reward, float DeltaTime)
{
	if (MCTS == nullptr || MCTS->CurrentNode == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("MCTS or CurrentNode is nullptr"));
		return;
	}

	MCTS->RunMCTS(PossibleActions, Reward, StateMachine);
}

void UAttackState::ExitState(UStateMachine* StateMachine)
{
	if (MCTS)
	{
		UE_LOG(LogTemp, Warning, TEXT("Exited Attack State"));
		//float Reward = MCTS->Simulate();
		//MCTS->Backpropagate(MCTS->CurrentNode, Reward);
		MCTS->CurrentNode = MCTS->RootNode;
	}
}


TArray<UAction*> UAttackState::GetPossibleActions()
{
	TArray<UAction*> Actions;

	Actions.Add(NewObject<USkillAttackAction>(this, USkillAttackAction::StaticClass()));
	Actions.Add(NewObject<UDeafultAttackAction>(this, UDeafultAttackAction::StaticClass()));


	return Actions;
}

void UAttackState::ResetCurrentNode()
{
	MCTS->CurrentNode = MCTS->RootNode;
}
