// Fill out your copyright notice in the Description page of Project Settings.


#include "MCTSNode.h"


UMCTSNode::UMCTSNode()
    : Parent(nullptr), Action(nullptr), Reward(0.0f), VisitCount(0)
{
}

void UMCTSNode::InitializeNode(UMCTSNode* InParent, UAction* InAction)
{
    Parent = InParent;
    Action = InAction;
    Reward = 0.0f;
    VisitCount = 0;
}

UMCTSNode* UMCTSNode::SelectChildNode()
{
    UMCTSNode* BestChild = nullptr;
    float BestValue = -FLT_MAX;

    for (UMCTSNode* Child : Children)
    {
        float UCT = Child->UCTValue();
        if (UCT > BestValue)
        {
            BestValue = UCT;
            BestChild = Child;
        }
    }

    return BestChild;
}

UMCTSNode* UMCTSNode::Expand(TArray<UAction*> PossibleActions)
{
    for (UAction* PossibleAction : PossibleActions)
    {
        UMCTSNode* NewNode = NewObject<UMCTSNode>();
        NewNode->InitializeNode(this, PossibleAction);
        Children.Add(NewNode);
    }

    // For simplicity, we'll return the first new node
    return Children.Num() > 0 ? Children[0] : nullptr;
    
}

float UMCTSNode::Simulate()
{
    // Simulate the game from this state and return a reward
    // For simplicity, we'll use a random value as the reward
    return FMath::FRand();
}

void UMCTSNode::Backpropagate(float InReward)
{
    UMCTSNode* CurrentNode = this;
    while (CurrentNode)
    {
        CurrentNode->VisitCount++;
        CurrentNode->Reward += InReward;
        CurrentNode = CurrentNode->Parent;
    }
}

float UMCTSNode::UCTValue(float ExplorationParameter) const
{
    /*
    if (VisitCount == 0)
    {
        return FLT_MAX;
    }

    float Exploitation = Reward / VisitCount;
    float Exploration = ExplorationParameter * FMath::Sqrt(FMath::Log(Parent->VisitCount) / VisitCount);
    return Exploitation + Exploration;
    */
    return 0.0f;
}