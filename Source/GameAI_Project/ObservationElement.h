// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ObservationElement.generated.h"

USTRUCT(BlueprintType)
struct FObservationElement
{
    GENERATED_BODY()

    // ������������ �Ÿ�
    float DistanceToDestination;

    // ������Ʈ�� ü��
    float AgentHealth;

    // ������Ʈ �ֺ� ���� ��
    int32 EnemiesNum;
};
