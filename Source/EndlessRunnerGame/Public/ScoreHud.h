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
	UImage* HeartOne;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* HeartTwo;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* HeartThree;

	TArray<UImage*> Hearts;
	
	UPROPERTY(EditAnywhere, Category="Ref")
	class UTexture2D* HeartEmpty;
	UPROPERTY(EditAnywhere, Category="Ref")
	class UTexture2D* HeartFull;
	
	void UpdateScore(int Score);
	void RemoveLife(int CurrentLife);
	void HealLife();
	
	const FString ScoreBase = "Score: ";
};
