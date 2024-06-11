// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MCTSNode.h"
#include "MCTS.generated.h"

class UAction;

UCLASS()
class GAMEAI_PROJECT_API UMCTS : public UObject
{
	GENERATED_BODY()
	
public:
    UMCTS();

    UMCTSNode* SelectChildNode(float Reward);
    float Simulate();
    void InitializeMCTS();
    float Backpropagate(UMCTSNode*, float);
    void Expand(TArray<UAction*>);

    UMCTSNode* RootNode;
    UMCTSNode* CurrentNode;

private:

};
