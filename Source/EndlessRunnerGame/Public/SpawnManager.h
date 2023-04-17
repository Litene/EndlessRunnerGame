// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ALevelPiece.h"
#include "EndlessRunnerGame/FDifficultySetting.h"
#include "Containers/List.h"
#include "GameFramework/Actor.h"
#include "SpawnManager.generated.h"

UCLASS()
class ENDLESSRUNNERGAME_API ASpawnManager : public AActor {
	GENERATED_BODY()

public:
	ASpawnManager();

	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditInstanceOnly, Category="Available Pieces")
	TArray<TSubclassOf<AALevelPiece>> AvailablePieces;

	TArray<TObjectPtr<AALevelPiece>> PiecesInPlay; // Pieces should be self checking and have a callback, move should be called on all pieces from this tick? instead
	TArray<TObjectPtr<AALevelPiece>> PiecesToRemove;
	
	TArray<TArray<TObjectPtr<AALevelPiece>>> Lanes;
	
	TArray<TObjectPtr<AALevelPiece>> LaneOne;
	TArray<TObjectPtr<AALevelPiece>> LaneTwo;
	TArray<TObjectPtr<AALevelPiece>> LaneThree;
	
protected:

	virtual void BeginPlay() override;

private:
	FDifficultySetting CurrentSetting;
	TArray<FDifficultySetting> Settings;

	void SpawnSet();
	void RemoveSet();
	static bool CheckPlacement(TArray<TObjectPtr<AALevelPiece>> lane, TSubclassOf<AALevelPiece> piece);
	TSubclassOf<AALevelPiece> GetRandomPiece(TArray<TObjectPtr<AALevelPiece>> lane, TArray<TSubclassOf<AALevelPiece>> remainingPieces);
	FVector GetOriginVector(int laneNumber, TArray<TObjectPtr<AALevelPiece>> lane);
	void RemoveAndSpawnPiece();
	void IncreaseDifficulty();
	FTimerHandle RespawnTimerHandle;
	FTimerHandle DifficultyTimerHandle;
};



