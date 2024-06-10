// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillAttackAction.h"
#include "StateMachine.h"

void USkillAttackAction::ExecuteAction(UStateMachine* StateMachine)
{
	StateMachine->TriggerBlueprintEvent("Skill Attack");
}
