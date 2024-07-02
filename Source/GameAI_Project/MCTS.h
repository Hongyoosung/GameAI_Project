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
    void RunMCTS(TArray<UAction*>, float, UStateMachine*);

    UMCTSNode* RootNode;
    UMCTSNode* CurrentNode;

private:
    int32 TreeDepth;
    float ExplorationParameter;
    bool ShouldTerminate() const; // 조기 중단 조건 함수 추가
};
