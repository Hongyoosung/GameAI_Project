// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveLeftAction.h"
#include "StateMachine.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMoveLeftAction::ExecuteAction(UStateMachine* StateMachine)
{
    UE_LOG(LogTemp, Warning, TEXT("------------MoveLeftAction"));

    //StateMachine->TriggerBlueprintEvent("MoveL");
    
    ACharacter* OwnerCharacter = Cast<ACharacter>(StateMachine->GetOwner());
    if (OwnerCharacter)
    {
        // world x vector
        FVector ForwardVector = FVector(0.0f, -1.0f, 0.0f);

        // 총 이동 거리와 이동 속도를 설정
        float TotalDistance = 100.0f; // 100cm (1m)
        float MoveDuration = 1.0f; // 1초 동안 이동
        float MoveSpeed = TotalDistance / MoveDuration; // 초당 이동 거리

        // 초기 시간 설정
        ElapsedTime = 0.0f;

        MoveDelegate.BindLambda([OwnerCharacter, ForwardVector, MoveSpeed, this]()
            {
                // 델타 시간을 가져옵니다.
                float DeltaTime = OwnerCharacter->GetWorld()->GetDeltaSeconds();

                // 경과 시간 업데이트
                ElapsedTime += DeltaTime;

                if (ElapsedTime < 1.0f) // 1초 동안만 이동
                {
                    OwnerCharacter->AddMovementInput(ForwardVector, MoveSpeed * DeltaTime);
                }
                else
                {
                    // 타이머 멈추기
                    OwnerCharacter->GetWorld()->GetTimerManager().ClearTimer(MoveTimer);
                }
            });

        // 타이머 설정: 델타 시간 간격으로 MoveDelegate를 반복 호출
        if (OwnerCharacter->GetWorld())
        {
            OwnerCharacter->GetWorld()->GetTimerManager().SetTimer(MoveTimer, MoveDelegate, OwnerCharacter->GetWorld()->GetDeltaSeconds(), true);
        }
    }
}
