// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "FDifficultyWrapper.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FDifficultyWrapper {
	GENERATED_BODY()
public:
	float MoveSpeed = 0.0f;
	float TimeInBetween = 0.0f;
};
