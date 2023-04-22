#include "SpawnManager.h"
#include "ALevelPiece.h"
#include "Math/UnrealMathUtility.h"
#include "Containers/List.h"
#include "TimerManager.h"
#include "Containers/UnrealString.h"
#include "DebugMacros.h"
#include "RollingBall.h"


ASpawnManager::ASpawnManager() {
	PrimaryActorTick.bCanEverTick = true;

	for (int i = 1; i <= 10; i++) {
		Settings.Add(FDifficultySetting(i)); //this has to be changed later since difficulty is not the only thing set;
	}
	CurrentSetting = Settings[0];
	Lanes.Add(LaneOne);
	Lanes.Add(LaneTwo);
	Lanes.Add(LaneThree);
}

void ASpawnManager::BeginPlay() {
	Super::BeginPlay();

	for (int i = 0; i < 7; i++) {
		// magic numbers, expose in settings in spawnmanager
		SpawnSet(true);
	}

	GetWorldTimerManager().SetTimer(DifficultyTimerHandle, this, &ASpawnManager::IncreaseDifficulty, 5.0f, true);
}

void ASpawnManager::SpawnSet(bool InitialSpawn) {
	if (GetWorld()) {
		for (int i = 0; i <= 2; i++) {
			if (i == 0) { // this is messy, should break out into spawn method method, special conditions etc...
				TObjectPtr<AALevelPiece> mySpawnedLeftWall = GetWorld()->SpawnActor<AALevelPiece>(Wall, GetOriginVector(i, Lanes[i]) + FVector(-0, -80,0), FRotator::ZeroRotator);
				PiecesInPlay.Add(mySpawnedLeftWall);
			}
			else if (i == 2) {
				TObjectPtr<AALevelPiece> mySpawnedRightWall = GetWorld()->SpawnActor<AALevelPiece>(Wall, GetOriginVector(i, Lanes[i]) + FVector(-0, 100,0), FRotator::ZeroRotator);
				PiecesInPlay.Add(mySpawnedRightWall);
			}
			TObjectPtr<AALevelPiece> mySpawnedActor = GetWorld()->SpawnActor<AALevelPiece>(
				GetRandomPiece(Lanes[i], AvailablePieces), GetOriginVector(i, Lanes[i]), FRotator::ZeroRotator);
			Lanes[i].Add(mySpawnedActor);
			PiecesInPlay.Add(mySpawnedActor);
			if (!InitialSpawn && CheckSpawn(CurrentSetting.ChanceToSpawnBase)) {
				TObjectPtr<ARollingBall> myRollingActor = GetWorld()->SpawnActor<ARollingBall>(
					RollingBall, mySpawnedActor->ProjectileSpawn->GetComponentLocation(), FRotator::ZeroRotator);
			}
		}
	}
}

void ASpawnManager::RemoveSet() {
	// maybe?
}

void ASpawnManager::SpawnProjectile() {
	// maybe?
}

bool ASpawnManager::CheckSpawn(int percentage) {
	return (FMath::RandRange(1, 100 / percentage) == 1 ? true : false);
}


bool ASpawnManager::CheckPlacement(TArray<TObjectPtr<AALevelPiece>> lane, TSubclassOf<AALevelPiece> piece) {
	// move to new class GameRules::
	if (lane.Num() == 0) { return true; }
	if (lane[lane.Num() - 1]->SocketNames.Contains(piece->GetName())) { return true; }

	return false;
}

TSubclassOf<AALevelPiece> ASpawnManager::GetRandomPiece(TArray<TObjectPtr<AALevelPiece>> lane,
                                                        TArray<TSubclassOf<AALevelPiece>> RemainingPieces) {
	// move to new class GameRules::
	if (lane.Num() == 0) { return AvailablePieces[0]; }
	TArray<FString> PossibleSockets = lane.Last()->SocketNames;
	const FString PieceString = PossibleSockets[FMath::RandRange(0, PossibleSockets.Num() - 1)];
	for (int i = 0; i < AvailablePieces.Num(); i++) {
		if (AvailablePieces[i]->GetName() == PieceString) {
			return AvailablePieces[i];
		}
	}

	return AvailablePieces[0]; // default
}

FVector ASpawnManager::GetOriginVector(int laneNumber, TArray<TObjectPtr<AALevelPiece>> lane) {
	// move to new class GameRules::
	if (lane.Num() == 0) {
		switch (laneNumber) {
		case 0: return FVector(0, -100, 0);
		case 1: return FVector(0, 0, 0);
		case 2: return FVector(0, 100, 0);
		default: ;
		}
	}
	return lane[lane.Num() - 1]->Arrow->GetComponentLocation();
}

void ASpawnManager::RemoveAndSpawnPiece() {
	// Iterate over a copy of the PiecesToRemove array to avoid modifying it during iteration
	TArray<TObjectPtr<AALevelPiece>> CopyArray;
	for (auto AALevelPiece : PiecesToRemove) {
		CopyArray.Add(AALevelPiece);
	}
	for (TObjectPtr<AALevelPiece> Piece : CopyArray) {
		if (Piece && Piece->GetWorld()) {
			if (Piece->Destroy()) {
				PiecesInPlay.Remove(Piece);
			}
		}
	}
	// Clear the PiecesToRemove array
	PiecesToRemove.Empty();


	// Spawn new pieces
	SpawnSet(false);
}

void ASpawnManager::IncreaseDifficulty() {
	if (CurrentSetting.Difficulty == 10) return;

	CurrentSetting = Settings[CurrentSetting.Difficulty];
}


void ASpawnManager::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	for (const TObjectPtr<AALevelPiece> Piece : PiecesInPlay) {
		const float XPosition = Piece->MovePiece(CurrentSetting.GetMoveSpeedAndTimeBetween().MoveSpeed, DeltaTime);
		if (XPosition < -2000 && !PiecesToRemove.Contains(Piece)) {
			PiecesToRemove.Add(Piece);
			if (!GetWorldTimerManager().IsTimerActive(RespawnTimerHandle)) {
				GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ASpawnManager::RemoveAndSpawnPiece, 0.01f,
				                                false);
			}
		}
	}
}
