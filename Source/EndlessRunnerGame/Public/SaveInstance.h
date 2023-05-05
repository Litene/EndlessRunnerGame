// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSaveItem.h"
#include "GameFramework/SaveGame.h"
#include "SaveInstance.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNERGAME_API USaveInstance : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TArray<FSaveItem> LeaderBoard;

	
};
