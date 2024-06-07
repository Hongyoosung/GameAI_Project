// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveBackwardAction.h"
#include "StateMachine.h"
#include "GameFramework/Character.h"

void UMoveBackwardAction::ExecuteAction(UStateMachine* StateMachine)
{
    UE_LOG(LogTemp, Warning, TEXT("MoveBackwardAction::ExecuteAction"));

    // Move backward
    ACharacter* OwnerCharacter = Cast<ACharacter>(StateMachine->GetOwner());
    if (OwnerCharacter)
    {
        FVector ForwardVector = OwnerCharacter->GetActorForwardVector() * -1.0f;
        OwnerCharacter->AddMovementInput(ForwardVector);
    }
}
