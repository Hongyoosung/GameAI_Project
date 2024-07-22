// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "MoveForwardAction.generated.h"

/**
 * 
 */
UCLASS()
class GAMEAI_PROJECT_API UMoveForwardAction : public UAction
{
	GENERATED_BODY()
	
public:
	virtual void ExecuteAction(UStateMachine* StateMachine) override;

private:
	// 타이머 핸들러
	FTimerHandle MoveTimer;

	// 델리게이트 (람다 함수를 저장하기 위한 변수)
	FTimerDelegate MoveDelegate;

	// 이동 시간
	float ElapsedTime;
};
