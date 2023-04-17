// Copyright Epic Games, Inc. All Rights Reserved.

#include "EndlessRunnerGameGameMode.h"
#include "EndlessRunnerGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

AEndlessRunnerGameGameMode::AEndlessRunnerGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
