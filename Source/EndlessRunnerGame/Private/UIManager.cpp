// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManager.h"

// Sets default values
AUIManager::AUIManager() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AUIManager::BeginPlay() {
	Super::BeginPlay();
	if (GetWorld()) {
		Hud = CreateWidget<UScoreHud>(GetWorld()->GetFirstPlayerController(), HudInterface);
		Hud->AddToViewport(9999);
		Hud->InitializeHud();
	}
}

// Called every frame
void AUIManager::Tick(float DeltaTime) {
	currentScore += DeltaTime;
	if (Hud) {
		Hud->UpdateScore(currentScore);
	}
	Super::Tick(DeltaTime);
}
