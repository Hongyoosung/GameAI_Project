// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveForwardAction.h"
#include "StateMachine.h"
#include "GameFramework/Character.h"

void UMoveForwardAction::ExecuteAction(UStateMachine* StateMachine)
{
    UE_LOG(LogTemp, Warning, TEXT("MoveForwardAction"));

    // Move forward ·ÎÁ÷
    ACharacter* OwnerCharacter = Cast<ACharacter>(StateMachine->GetOwner());
    if (OwnerCharacter)
    {
        FVector ForwardVector = OwnerCharacter->GetActorForwardVector();
        OwnerCharacter->AddMovementInput(ForwardVector);
    }
}
