// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameAI_ProjectGameMode.h"
#include "GameAI_ProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGameAI_ProjectGameMode::AGameAI_ProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
