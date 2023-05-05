// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSaveItem.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "GameOverScreen.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNERGAME_API UGameOverScreen : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* YourScore;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* SubmitButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* RestartButton;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UEditableText* YourNameInput;
public:
	UFUNCTION()
	void UGameOverScreenInitialize();
	UFUNCTION()
	void SetScore(int32 Score);
	
	UFUNCTION()
	void SetLeaderBoard(TArray<FSaveItem> items);

	UFUNCTION()
	void RestartGame();

	UFUNCTION()
	void SubmitName();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* Place1;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* Place2;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* Place3;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* Place4;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* Place5;

	TArray<UTextBlock*> Slots;
	int32 Score;
	FString Name;
};
