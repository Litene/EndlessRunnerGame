// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveManager.h"

#include "Kismet/GameplayStatics.h"

void ASaveManager::SaveGame(int32 InputScore, FString Name) {
	FSaveItem newSave;
	newSave.Name = Name;
	newSave.Score = InputScore;
	SaveInstance->LeaderBoard.Add(newSave);
	if (SaveInstance->LeaderBoard.Num() > 1) {
		SaveInstance->LeaderBoard.Sort();
	}
	if (SaveInstance->LeaderBoard.Num() == 1) {
		
	UE_LOG(LogTemp, Warning, TEXT("Saved data: %s"), *SaveInstance->LeaderBoard[0].GetText().ToString())
	}
	UGameplayStatics::SaveGameToSlot(SaveInstance, "HighScoreSave", 0);
}

TArray<FSaveItem> ASaveManager::LoadGame() {
	TArray<FSaveItem> items;
	if (UGameplayStatics::DoesSaveGameExist("HighScoreSave", 0)) {
		UE_LOG(LogTemp, Warning, TEXT("File Exists, trying to load"))
		SaveInstance = Cast<USaveInstance>(UGameplayStatics::LoadGameFromSlot("HighScoreSave", 0));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("File Doesn't exist"))
		SaveInstance = Cast<USaveInstance>(UGameplayStatics::CreateSaveGameObject(USaveInstance::StaticClass()));
	}

	for (FSaveItem item : SaveInstance->LeaderBoard) {
		UE_LOG(LogTemp, Warning, TEXT("Data that is loaded: %s"), *item.GetText().ToString())
		items.Add(item);
	}
	items.Sort();
	return items;
}
