// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackState.h"
#include "StateMachine.h"
#include "MCTS.h"
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

	UE_LOG(LogTemp, Warning, TEXT("Entered Attack State"));
}

void UAttackState::UpdateState(UStateMachine* StateMachine, float Reward, float DeltaTime)
{
	if (!MCTS->CurrentNode)
	{
		return;
	}

	if (MCTS->CurrentNode->Children.Num() == 0)
	{
		MCTS->Expand(PossibleActions);
	}

	// ������ �ൿ ����
	UMCTSNode* BestChild = MCTS->SelectChildNode(Reward);

	if (BestChild)
	{
		UE_LOG(LogTemp, Warning, TEXT("BestChild is valid"));

		if (BestChild->Action)
		{
			UE_LOG(LogTemp, Warning, TEXT("BestChild->Action is valid"));
			BestChild->Action->ExecuteAction(StateMachine);

			// ���� ��带 ������ �ڽ� ���� ����
			MCTS->CurrentNode = BestChild;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("BestChild->Action is nullptr"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("BestChild is nullptr"));
		// BestChild�� nullptr�� ��� CurrentNode�� ��Ʈ ���� �缳���Ͽ� ���� ����
		MCTS->CurrentNode = MCTS->RootNode;
	}
	
	
}

void UAttackState::ExitState(UStateMachine* StateMachine)
{
	if (MCTS)
	{
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
