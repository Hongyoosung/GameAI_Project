// Fill out your copyright notice in the Description page of Project Settings.


#include "MCTS.h"

UMCTS::UMCTS()
{
    RootNode = nullptr;
    CurrentNode = nullptr;
}

void UMCTS::InitializeMCTS()
{
    RootNode = NewObject<UMCTSNode>();
    CurrentNode = RootNode;

    if (CurrentNode != nullptr)
    {
        CurrentNode->InitializeNode(nullptr, nullptr);

        UE_LOG(LogTemp, Warning, TEXT("Initialized MCTS"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to Initialize MCTS"));
    }
}


UMCTSNode* UMCTS::SelectChildNode()
{
    UMCTSNode* BestChild = nullptr;
    float BestValue = -FLT_MAX;
    float ExplorationParameter = 1.41f;

    if(CurrentNode == nullptr)
	{
        UE_LOG(LogTemp, Warning, TEXT("No Children"));
		return nullptr;
	}

    for (UMCTSNode* Child : CurrentNode->Children)
    {
        float UCT = Child->UCTValue(ExplorationParameter);
        if (UCT > BestValue)
        {
            BestValue = UCT;
            BestChild = Child;
        }
    }

    if (BestChild)
    {
        BestChild->VisitCount++;
        UE_LOG(LogTemp, Warning, TEXT("Selected Child with UCT Value: %f"), BestValue);

        return BestChild;
    }

    return nullptr;
}

void UMCTS::Expand(TArray<UAction*> PossibleActions)
{
    for (UAction* PossibleAction : PossibleActions)
    {
        UMCTSNode* NewNode = NewObject<UMCTSNode>();
        if (NewNode != nullptr)
        {
            NewNode->InitializeNode(CurrentNode, PossibleAction);
            CurrentNode->Children.Add(NewNode);

            UE_LOG(LogTemp, Warning, TEXT("Expanded Node"));
        }
    }
}

float UMCTS::Simulate()
{
    return FMath::RandRange(-100.0f, 100.0f);
}



void UMCTS::Backpropagate(UMCTSNode* Node, float InReward)
{
    while (Node)
    {
        Node->VisitCount++;
        Node->Reward += InReward;
        UE_LOG(LogTemp, Warning, TEXT("VisitCount: %d, Reward: %f"), Node->VisitCount, Node->Reward);
        Node = Node->Parent;
    }

    CurrentNode = RootNode;
}

