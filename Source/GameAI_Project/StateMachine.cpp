// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine.h"
#include "State.h"
#include "MoveToState.h"
#include "AttackState.h"
#include "FleeState.h"
#include "DeadState.h"
#include "AIController.h"
#include "GameFramework/Character.h"


UStateMachine::UStateMachine()
{
    PrimaryComponentTick.bCanEverTick = true;
    Owner = GetOwner();
}

void UStateMachine::BeginPlay()
{
    Super::BeginPlay();

    // 2초 딜레이 후에 상태 초기화
    FTimerHandle DelayTimerHandle;
    //GetWorld()->GetTimerManager().SetTimer(DelayTimerHandle, this, &UStateMachine::InitStateMachine, 3.0f, false);

    InitStateMachine();
}

void UStateMachine::InitStateMachine()
{
    // 상태 객체 생성
    MoveToState = NewObject<UMoveToState>(this, UMoveToState::StaticClass());
    AttackState = NewObject<UAttackState>(this, UAttackState::StaticClass());
    FleeState = NewObject<UFleeState>(this, UFleeState::StaticClass());
    DeadState = NewObject<UDeadState>(this, UDeadState::StaticClass());

    // 초기 상태 설정
    CurrentState = MoveToState;

    OwnerPawn = Cast<APawn>(GetOwner());
    if (OwnerPawn)
    {
        AIController = Cast<AAIController>(OwnerPawn->GetController());
    }

    // 초기 상태 시작
    if (CurrentState)
    {
        CurrentState->EnterState(this);
    }
}

void UStateMachine::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    /*
    // 현재 상태 업데이트
    if (CurrentState)
    {
        
        // Status updates every 2 seconds
        CurrentTime = GetWorld()->GetTimeSeconds();
        if (CurrentTime - LastStateUpdateTime > 4.0f)
        {
            LastStateUpdateTime = CurrentTime;
            CurrentState->UpdateState(this, DeltaTime);
        }
    }
    */
}

void UStateMachine::ChangeState(UState* NewState)
{
    if (CurrentState != NewState && NewState)
    {
        if (CurrentState)
        {
            CurrentState->ExitState(this);
        }

        CurrentState = NewState;
        CurrentState->EnterState(this);
    }
}

void UStateMachine::TriggerBlueprintEvent(const FName& EventName)
{
    if (Owner)
    {
        UFunction* Function = Owner->FindFunction(EventName);
        if (Function)
        {
            Owner->ProcessEvent(Function, nullptr);
        }
    }
}

UState* UStateMachine::GetCurrentState()
{
    return CurrentState;
}

UState* UStateMachine::GetMoveToState()
{
    return MoveToState;
}

UState* UStateMachine::GetAttackState()
{
    return AttackState;
}

UState* UStateMachine::GetFleeState()
{
    return FleeState;
}

UState* UStateMachine::GetDeadState()
{
    return DeadState;
}


