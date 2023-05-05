// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EndlessRunnerGameCharacter.h"
#include "GameFramework/GameModeBase.h"
#include "EndlessRunnerGameGameMode.generated.h"

UCLASS(minimalapi)
class AEndlessRunnerGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AEndlessRunnerGameGameMode();

	virtual void BeginPlay() override;

	AEndlessRunnerGameCharacter* TwoPlayer;
};



