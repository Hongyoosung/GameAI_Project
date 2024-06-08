// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "MoveLeftAction.generated.h"

/**
 * 
 */
UCLASS()
class GAMEAI_PROJECT_API UMoveLeftAction : public UAction
{
	GENERATED_BODY()
	
public:
	virtual void ExecuteAction(UStateMachine* StateMachine) override;

private:
	// Ÿ�̸� �ڵ鷯
	FTimerHandle MoveTimer;

	// ��������Ʈ (���� �Լ��� �����ϱ� ���� ����)
	FTimerDelegate MoveDelegate;

	// �̵� �ð�
	float ElapsedTime;
};
