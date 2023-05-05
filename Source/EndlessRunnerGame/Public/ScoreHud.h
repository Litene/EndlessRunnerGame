// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "ScoreHud.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNERGAME_API UScoreHud : public UUserWidget {
	GENERATED_BODY()

	
public:
	
	void InitializeHud();
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* ScoreText; 

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* HeartOneP1;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* HeartOneP2;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* HeartTwoP1;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* HeartTwoP2;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* HeartThreeP1;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* HeartThreeP2;

	TArray<UImage*> HeartsP1;
	TArray<UImage*> HeartsP2;
	
	UPROPERTY(EditAnywhere, Category="Ref")
	class UTexture2D* HeartEmpty;
	UPROPERTY(EditAnywhere, Category="Ref")
	class UTexture2D* HeartFull;
	
	void UpdateScore(int Score);
	void RemoveLife(int CurrentLife, int PlayerID);
	void HealLife();
	
	const FString ScoreBase = "Score: ";
};
