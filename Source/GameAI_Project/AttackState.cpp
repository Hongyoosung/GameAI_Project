// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackState.h"
#include "StateMachine.h"
#include "MCTS.h"
#include "SkillAttackAction.h"
#include "DeafultAttackAction.h"

void UAttackState::EnterState(UStateMachine* StateMachine)
{
	PossibleActions = GetPossibleActions();

	if (MCTS == nullptr)
	{
		MCTS = NewObject<UMCTS>();
	}

	UE_LOG(LogTemp, Warning, TEXT("Entered Attack State"));

	MCTS->InitializeMCTS();
	
}

void UAttackState::UpdateState(UStateMachine* StateMachine, float DeltaTime)
{
	if (!MCTS->CurrentNode)
	{
		return;
	}

	if (MCTS->CurrentNode->Children.Num() == 0)
	{
		MCTS->Expand(PossibleActions);
	}

	// 최적의 행동 선택
	UMCTSNode* BestChild = MCTS->SelectChildNode();

	if (BestChild)
	{
		UE_LOG(LogTemp, Warning, TEXT("BestChild is valid"));

		if (BestChild->Action)
		{
			UE_LOG(LogTemp, Warning, TEXT("BestChild->Action is valid"));
			BestChild->Action->ExecuteAction(StateMachine);

			// 현재 노드를 최적의 자식 노드로 설정
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
		// BestChild가 nullptr인 경우 CurrentNode를 루트 노드로 재설정하여 문제 방지
		MCTS->CurrentNode = MCTS->RootNode;
	}
	
	
}

void UAttackState::ExitState(UStateMachine* StateMachine)
{
	if (MCTS)
	{
		float Reward = MCTS->Simulate();
		MCTS->Backpropagate(MCTS->CurrentNode, Reward);
	}
}


TArray<UAction*> UAttackState::GetPossibleActions()
{
	TArray<UAction*> Actions;

	Actions.Add(NewObject<USkillAttackAction>(this, USkillAttackAction::StaticClass()));
	Actions.Add(NewObject<UDeafultAttackAction>(this, UDeafultAttackAction::StaticClass()));


	return Actions;
}
