#include "FDifficultySetting.h"

FDifficultySetting::FDifficultySetting(): Difficulty(0), TimeInBetweenBase(0) {
}

FDifficultySetting::FDifficultySetting(int difficulty) : TimeInBetweenBase(10) {
	Difficulty = difficulty;
}

FDifficultyWrapper FDifficultySetting::GetMoveSpeedAndTimeBetween() const {
	FDifficultyWrapper wrapper;
	wrapper.MoveSpeed = Difficulty > 5 ? 500 : Difficulty * 100;
	wrapper.TimeInBetween = TimeInBetweenBase/Difficulty;
	return wrapper; // magic numbers
}
