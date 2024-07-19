// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StateMachine.h"
#include "ObservationElement.h"
#include "MCTSNode.h"
#include "MCTS.generated.h"

class UAction;

UCLASS()
class GAMEAI_PROJECT_API UMCTS : public UObject
{
	GENERATED_BODY()
	
public:
    UMCTS();

    void InitializeMCTS();
    void InitializeCurrentNodeLocate();
    void RunMCTS(TArray<UAction*>, UStateMachine*);
    void Backpropagate();

private:
    UMCTSNode* RootNode;
    UMCTSNode* CurrentNode;
    FObservationElement CurrentObservation;
    int32 TreeDepth;
    float ExplorationParameter;
    UWorld* World;

private:
    UMCTSNode* SelectChildNode();
    void Expand(TArray<UAction*> PossibleActions);
    float CalculateImmediateReward(UMCTSNode* Node) const;
    bool ShouldTerminate() const;
    float CalculateNodeScore(UMCTSNode* Node) const;
    float CalculateObservationSimilarity(const FObservationElement&, const FObservationElement&) const;
    float CalculateDynamicExplorationParameter() const;
    FObservationElement GetCurrentObservation(UStateMachine*);
};
