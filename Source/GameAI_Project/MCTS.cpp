// Fill out your copyright notice in the Description page of Project Settings.


#include "MCTS.h"

UMCTS::UMCTS()
{

}

void UMCTS::InitializeMCTS()
{
    CurrentNode = NewObject<UMCTSNode>();

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
            BestChild->VisitCount++;
        }
    }

    // print uct value
    UE_LOG(LogTemp, Warning, TEXT("UCT Value: %f"), BestValue);

    CurrentNode = BestChild;

    return BestChild;
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



void UMCTS::Backpropagate(float InReward)
{
    // Check if CurrentNode is not null (safety check)
    if (CurrentNode == nullptr)
    {
        return;
    }
    else if(CurrentNode->Parent == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("CurrentNode is Root Node"));
    }

    UMCTSNode* LastNode = CurrentNode;
    int32 Count = 0;
    // Loop until reaching the root node (parent is null)
    while (CurrentNode->Parent != nullptr)
    {
        CurrentNode->Reward += InReward;

        UE_LOG(LogTemp, Warning, TEXT("VisitCount: %d, Reward: %f"), CurrentNode->VisitCount, CurrentNode->Reward);
        CurrentNode = CurrentNode->Parent;

        Count++;
        UE_LOG(LogTemp, Warning, TEXT("Count: %d"), Count);
    }
}


