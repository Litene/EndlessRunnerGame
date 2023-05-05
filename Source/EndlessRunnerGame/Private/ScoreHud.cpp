// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreHud.h"
#include "Components/Image.h"
#include "Algo/ForEach.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UScoreHud::InitializeHud() {
	// call in begin play of GameManager


	HeartsP1.Add(HeartOneP1);
	HeartsP1.Add(HeartTwoP1);
	HeartsP1.Add(HeartThreeP1);

	HeartsP2.Add(HeartOneP2);
	HeartsP2.Add(HeartTwoP2);
	HeartsP2.Add(HeartThreeP2);
	HealLife();
}

void UScoreHud::UpdateScore(int Score) {
	// call every tick with int conversion?
	FString scoreText = "";
	scoreText.Append(ScoreBase);
	scoreText.Append(FString::FromInt(Score));
	ScoreText->SetText(FText::FromString(scoreText));
	// if (Score % 60 == 0) { ScoreText->SetColorAndOpacity(FSlateColor(FColor(255, 0, 0))); }
	// else if (ScoreText->GetColorAndOpacity() != FSlateColor(FColor(255, 255, 255))) {
	// 	ScoreText->SetColorAndOpacity(FSlateColor(FColor(255, 255, 255)));
	// }
}

void UScoreHud::RemoveLife(int CurrentLife, int PlayerID) {
	// invoke even from game Manager. 
	const int32 ClampedLife = FMath::Clamp(CurrentLife, 0, 2);
	if (PlayerID == 0) {
		HeartsP1[ClampedLife]->SetBrushFromTexture(HeartEmpty);
	}
	else if (PlayerID == 1) {
		HeartsP2[ClampedLife]->SetBrushFromTexture(HeartEmpty);
	}
}

void UScoreHud::HealLife() {
	for (UImage* Heart : HeartsP1) {
		Heart->SetBrushFromTexture(HeartFull);
	}
	for (UImage* Heart : HeartsP2) {
		Heart->SetBrushFromTexture(HeartFull);
	}
}
