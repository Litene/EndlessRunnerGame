// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SaveInstance.h"
#include "GameFramework/SaveGame.h"
#include "SaveManager.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNERGAME_API ASaveManager : public AActor {
	GENERATED_BODY()
public:
	void SaveGame(int32 Score, FString Name);
	TArray<FSaveItem> LoadGame();
	//USaveInstance* UpdateCurrentSave(int32 Score, FString Name);
	USaveInstance* SaveInstance;
};
