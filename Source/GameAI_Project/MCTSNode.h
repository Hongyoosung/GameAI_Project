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
    float UCTValue(float ExplorationParameter) const;

    UAction* Action;
    UMCTSNode* Parent;
    TArray<UMCTSNode*> Children;
    float Reward;
    int32 VisitCount;
};
