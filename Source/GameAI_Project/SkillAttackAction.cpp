// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillAttackAction.h"
#include "StateMachine.h"

void USkillAttackAction::ExecuteAction(UStateMachine* StateMachine)
{
	UE_LOG(LogTemp, Warning, TEXT("------------Skill Attack"));
	//StateMachine->TriggerBlueprintEvent("Skill Attack");
}
