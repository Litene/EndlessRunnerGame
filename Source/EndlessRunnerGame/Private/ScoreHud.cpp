// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreHud.h"
#include "Components/Image.h"
#include "Algo/ForEach.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UScoreHud::InitializeHud() { // call in begin play of GameManager


	Hearts.Add(HeartOne);
	Hearts.Add(HeartTwo);
	Hearts.Add(HeartThree);
	HealLife();
	
}

void UScoreHud::UpdateScore(int Score) { // call every tick with int conversion?
	FString scoreText = "";
	scoreText.Append(ScoreBase);
	scoreText.Append(FString::FromInt(Score));
	ScoreText->SetText(FText::FromString(scoreText));
	// if (Score % 60 == 0) { ScoreText->SetColorAndOpacity(FSlateColor(FColor(255, 0, 0))); }
	// else if (ScoreText->GetColorAndOpacity() != FSlateColor(FColor(255, 255, 255))) {
	// 	ScoreText->SetColorAndOpacity(FSlateColor(FColor(255, 255, 255)));
	// }
}

void UScoreHud::RemoveLife(int CurrentLife) { // invoke even from game Manager. 
	const int32 ClampedLife = FMath::Clamp(CurrentLife, 0, 2);
	Hearts[ClampedLife]->SetBrushFromTexture(HeartEmpty);
}

void UScoreHud::HealLife() {
	for (UImage* Heart : Hearts) {
		Heart->SetBrushFromTexture(HeartFull);
	}
}
