// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManager.h"

#include "EndlessCharacterController.h"
#include "SaveManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AUIManager::AUIManager() : GameOverBool(false) {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PlayerDead.Add(false);
	PlayerDead.Add(false);
}

// Called when the game starts or when spawned
void AUIManager::BeginPlay() {
	Super::BeginPlay();
	if (GetWorld()) {
		Hud = CreateWidget<UScoreHud>(GetWorld()->GetFirstPlayerController(), HudInterface);
		Hud->AddToViewport(9999);
		Hud->InitializeHud();
		GameOverHud = CreateWidget<UGameOverScreen>(GetWorld()->GetFirstPlayerController(), GameOverInterface);
		GameOverHud->AddToViewport(9999);

		GameOverHud->SetVisibility(ESlateVisibility::Hidden);
	}
}

// Called every frame
void AUIManager::Tick(float DeltaTime) {
	if (Hud && !GameOverBool) {
		currentScore += DeltaTime;
		Hud->UpdateScore(currentScore);
	}
	Super::Tick(DeltaTime);
}

void AUIManager::RemoveLife(int CurrentLife, int PlayerID) {
	UE_LOG(LogTemp, Warning, TEXT("PlayerID on Call: %d"), PlayerID)
	if (Hud) {
		Hud->RemoveLife(CurrentLife, PlayerID);
	}
}

void AUIManager::PlayerDie(int32 PlayerNumber) {
	PlayerDead[PlayerNumber] = true;
	
	if (PlayerNumber == 0 && PlayerDead[1]) {
		GameOver();
	}
	else if (PlayerNumber == 1 && PlayerDead[0]) {
		GameOver();
	}
}

void AUIManager::GameOver() {
	GameOverBool = true;
	GameOverHud->SetScore(static_cast<int32>(currentScore));
	//GameOverHud->SetLeaderBoard();
	GameOverHud->SetVisibility(ESlateVisibility::Visible);
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	GameOverHud->UGameOverScreenInitialize();
	Hud->SetVisibility(ESlateVisibility::Hidden);
}
