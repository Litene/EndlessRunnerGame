#include "FDifficultySetting.h"

FDifficultySetting::FDifficultySetting(): Difficulty(0), ChanceToSpawnBase(0) {
}

FDifficultySetting::FDifficultySetting(int difficulty) : ChanceToSpawnBase(10) {
	Difficulty = difficulty;
}

FDifficultyWrapper FDifficultySetting::GetMoveSpeedAndTimeBetween() const {
	FDifficultyWrapper wrapper;
	wrapper.MoveSpeed = Difficulty > 5 ? 500 : Difficulty * 100;
	wrapper.ChanceToSpawn = Difficulty * 10;;
	return wrapper; // magic numbers
}
