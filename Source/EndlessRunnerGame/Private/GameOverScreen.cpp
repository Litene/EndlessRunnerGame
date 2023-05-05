// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverScreen.h"

#include <string>

#include "NetworkReplayStreaming.h"
#include "SaveManager.h"
#include "GameFramework/GameMode.h"
#include "Kismet/GameplayStatics.h"

void UGameOverScreen::UGameOverScreenInitialize() {
	YourNameInput->SetSelectAllTextWhenFocused(true);
	YourNameInput->SetKeyboardFocus();

	Slots.Add(Place1);
	Slots.Add(Place2);
	Slots.Add(Place3);
	Slots.Add(Place4);
	Slots.Add(Place5);

	SubmitButton->OnClicked.AddDynamic(this, &UGameOverScreen::SubmitName);
	RestartButton->OnClicked.AddDynamic(this, &UGameOverScreen::RestartGame);
	//YourNameInput->OnTextCommitted.Add();
	//YourNameInput->SetUserFocus(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void UGameOverScreen::SetScore(int32 LocalScore) {
	APlayerController* localController = GetWorld()->GetFirstPlayerController();
	localController->bShowMouseCursor = true;
	Score = LocalScore;
	YourScore->SetText(FText::FromString(FString::FromInt(LocalScore)));
	AActor* FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ASaveManager::StaticClass());
	ASaveManager* Manager = Cast<ASaveManager>(FoundActor);
	if (Manager) {
		TArray<FSaveItem> Items = Manager->LoadGame();
		UE_LOG(LogTemp, Warning, TEXT("%d"), Items.Num())
		SetLeaderBoard(Items);
	}
}

void UGameOverScreen::SetLeaderBoard(TArray<FSaveItem> items) {
	for (int i = 0; i < items.Num(); i++) {
		if (i < Slots.Num()) {
			Slots[i]->SetText(items[i].GetText());
		}
	}
}

void UGameOverScreen::RestartGame() {
	APlayerController* localController = GetWorld()->GetFirstPlayerController();
	localController->bShowMouseCursor = false;
	UGameplayStatics::OpenLevel(GetWorld(), FName(*GetWorld()->GetName()), false);
}

void UGameOverScreen::SubmitName() {
	AActor* FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ASaveManager::StaticClass());
	ASaveManager* Manager = Cast<ASaveManager>(FoundActor);
	if (Manager) {
		Manager->SaveGame(Score, YourNameInput->GetText().ToString());
		TArray<FSaveItem> Items = Manager->LoadGame();
		SetLeaderBoard(Items);
	}
	SubmitButton->SetIsEnabled(false);
	//UGameplayStatics::OpenLevel(GetWorld(), FName(*GetWorld()->GetName()), false);
}
