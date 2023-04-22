// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScoreHud.h"
#include "GameFramework/Actor.h"
#include "UIManager.generated.h"

UCLASS()
class ENDLESSRUNNERGAME_API AUIManager : public AActor {
	GENERATED_BODY()

public:
	TObjectPtr<UScoreHud> Hud;
	
	UPROPERTY(EditAnywhere, Category="Hud")
	TSubclassOf<UScoreHud> HudInterface;
	// Sets default values for this actor's properties
	AUIManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	float currentScore;
	virtual void Tick(float DeltaTime) override;
};
