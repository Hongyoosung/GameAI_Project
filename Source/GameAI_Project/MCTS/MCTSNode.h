// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Action.h"
#include "ObservationElement.h"
#include "MCTSNode.generated.h"

UCLASS()
class GAMEAI_PROJECT_API UMCTSNode : public UObject
{
    GENERATED_BODY()

public:
    UMCTSNode();

    void InitializeNode(UMCTSNode* InParent, UAction* InAction);

    UPROPERTY()
    UMCTSNode* Parent;

    UPROPERTY()
    TArray<UMCTSNode*> Children;

    UPROPERTY()
    UAction* Action;

    UPROPERTY()
    int32 VisitCount;

    UPROPERTY()
    float TotalReward;

    UPROPERTY()
    float LastVisitTime;

    FObservationElement Observation;

    // 현재 노드의 상태를 표현하는 함수 (실제 구현은 프로젝트의 상태 표현 방식에 따라 달라질 수 있습니다)
    virtual FString GetState() const;
};
