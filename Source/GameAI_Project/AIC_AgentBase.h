// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIC_AgentBase.generated.h"

/**
 * 
 */
UCLASS()
class GAMEAI_PROJECT_API AAIC_AgentBase : public AAIController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "AI")
	float SightRadius = 1000.0f;
	
public:
	// event on possessing a pawn
	virtual void OnPossess(APawn* InPawn) override;

	void SetStateAsPatrol();
	void SetStateAsChase();
	void SetStateAsAttack();
	void SetStateAsFlee();
	void SetStateAsMoveTo();
	void SetStateAsDead();

private:
	// Array to store all the nearby enemies
	TArray<AActor*> NearbyEnemies;


};
