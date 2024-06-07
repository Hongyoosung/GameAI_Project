// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Action.h"
#include "MCTSNode.generated.h"

class UAction;

UCLASS()
class GAMEAI_PROJECT_API UMCTSNode : public UObject
{
	GENERATED_BODY()

public:
    UMCTSNode();

    void InitializeNode(UMCTSNode* InParent, UAction* InAction);

    UMCTSNode* SelectChildNode();
    UMCTSNode* Expand(TArray<UAction*> PossibleActions);
    float Simulate();
    void Backpropagate(float InReward);

    float UCTValue(float ExplorationParameter = 1.414f) const;

    UPROPERTY()
    UMCTSNode* Parent;

    UPROPERTY()
    TArray<UMCTSNode*> Children;

    UPROPERTY()
    UAction* Action;

    UPROPERTY()
    float Reward;

    UPROPERTY()
    int32 VisitCount;
};
