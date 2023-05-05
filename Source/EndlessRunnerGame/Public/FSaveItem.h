// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSaveItem.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct ENDLESSRUNNERGAME_API FSaveItem {
public:
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	int32 Score;
	UPROPERTY(EditAnywhere)
	FString Name;

	bool operator<(const FSaveItem& B) const {
		return Score > B.Score;
	}

	FText GetText();
};
