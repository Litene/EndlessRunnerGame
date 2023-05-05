// Copyright Epic Games, Inc. All Rights Reserved.

#include "EndlessRunnerGameGameMode.h"
#include "EndlessRunnerGameCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AEndlessRunnerGameGameMode::AEndlessRunnerGameGameMode() {
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(
		TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL) {
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AEndlessRunnerGameGameMode::BeginPlay() {
	if (GetWorld()) {
		TwoPlayer = Cast<AEndlessRunnerGameCharacter>(UGameplayStatics::CreatePlayer(GetWorld(), 1, true));
	}
	else {
		
	}
	Super::BeginPlay();
	//APlayerController* OnePlayer = UGameplayStatics::CreatePlayer(GetWorld(), 0, true);
}
