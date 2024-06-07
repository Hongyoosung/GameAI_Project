// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveToState.h"
#include "StateMachine.h"
#include "MoveForwardAction.h"
#include "MoveBackwardAction.h"

void UMoveToState::EnterState(UStateMachine* StateMachine)
{
    Super::EnterState(StateMachine);
    UE_LOG(LogTemp, Warning, TEXT("Entered MoveToState"));
}

void UMoveToState::UpdateState(UStateMachine* StateMachine, float DeltaTime)
{
    
}

void UMoveToState::ExitState(UStateMachine* StateMachine)
{

}

TArray<UAction*> UMoveToState::GetPossibleActions()
{
    TArray<UAction*> Actions;

    Actions.Add(NewObject<UMoveForwardAction>(this, UMoveForwardAction::StaticClass()));
    Actions.Add(NewObject<UMoveBackwardAction>(this, UMoveBackwardAction::StaticClass()));

    return Actions;
}
