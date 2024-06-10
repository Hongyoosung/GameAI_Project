// Fill out your copyright notice in the Description page of Project Settings.


#include "DeafultAttackAction.h"
#include "StateMachine.h"

void UDeafultAttackAction::ExecuteAction(UStateMachine* StateMachine)
{
	StateMachine->TriggerBlueprintEvent("Default Attack");
}
