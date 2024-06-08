// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StateMachine.generated.h"


class UState;
class UMCTSNode;
class AAIController;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEAI_PROJECT_API UStateMachine : public UActorComponent
{
	GENERATED_BODY()


public:	
	UStateMachine();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable)
    void ChangeState(UState* NewState);

	void TriggerBlueprintEvent(const FName& EventName);

	APawn* OwnerPawn;
    //void ExecuteMCTS();

private:
	AAIController* AIController;
	FTimerHandle TimerHandle;

	UPROPERTY()
	UState* CurrentState;

	UPROPERTY(Transient)
	UState* MoveToState;

	UPROPERTY(Transient)
	UState* AttackState;

	UPROPERTY(Transient)
	UState* FleeState;

	UPROPERTY(Transient)
	UState* DeadState;

	float CurrentTime;

	float LastStateUpdateTime;

	//UMCTSNode* RootNode;

	void InitStateMachine();
};
