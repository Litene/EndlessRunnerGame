// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EndlessCharacterController.h"
#include "GameOverScreen.h"
#include "ScoreHud.h"
#include "GameFramework/Actor.h"
#include "UIManager.generated.h"

UCLASS()
class ENDLESSRUNNERGAME_API AUIManager : public AActor {
	GENERATED_BODY()

public:
	TObjectPtr<UScoreHud> Hud;
	TObjectPtr<UGameOverScreen> GameOverHud;
	TArray<bool> PlayerDead;

	UPROPERTY(EditAnywhere, Category="Hud")
	TSubclassOf<UScoreHud> HudInterface;


	UPROPERTY(EditAnywhere, Category="Hud")
	TSubclassOf<UGameOverScreen> GameOverInterface;
	// Sets default values for this actor's properties
	AUIManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	float currentScore;
	bool GameOverBool;
	virtual void Tick(float DeltaTime) override;
	void RemoveLife(int CurrentLife, int PlayerID);
	void PlayerDie(int32 PlayerNumber);
	void GameOver();
	
};
