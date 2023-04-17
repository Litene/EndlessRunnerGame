#pragma once
#include "FDifficultyWrapper.h"


#include "FDifficultySetting.generated.h"

USTRUCT(BlueprintType)
struct FDifficultySetting {
	GENERATED_BODY()

public: 
	FDifficultySetting();
	FDifficultySetting(int difficulty);
	int Difficulty;
	float TimeInBetweenBase;
	FDifficultyWrapper GetMoveSpeedAndTimeBetween() const;
private:
	
};

