// Fill out your copyright notice in the Description page of Project Settings.


#include "ALevelPiece.h"

#include "DiffResults.h"


AALevelPiece::AALevelPiece() {
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	Mesh->SetWorldScale3D(FVector(10.0f, 0.0f, 0.0f));
	Arrow = CreateDefaultSubobject<UArrowComponent>("Arrow");
	Arrow->SetupAttachment(Mesh);
	Arrow->AddLocalOffset(FVector(1000.0f, 0.0f, 0.0f));
	Arrow->ArrowSize = 0.1f;
	ProjectileSpawn = CreateDefaultSubobject<UArrowComponent>("ProjectileArrow");
	ProjectileSpawn->SetupAttachment(Mesh);
	ProjectileSpawn->AddLocalOffset(FVector(100.0f, 50.0f, 150.0f));
	NameIdentifier = GetCorrectName(PieceType);
}

FRotator AALevelPiece::GetCurrentRotation() { // remove
	return this->GetActorRotation();
}

FString AALevelPiece::GetCorrectName(EPieceType pieceType) { // move to  utility?
	switch (pieceType) {
	case EPieceType::Floor:
		return "BP_LevelFloor_C";
	case EPieceType::RampUp:
		return "BP_RampUp_C";
	case EPieceType::RampDown:
		return "BP_RampDown_C";
	case EPieceType::Top:
		return "BP_TopFloor_C";
	}
	return "";
}

void AALevelPiece::OnFinishedMoving() { // wrong remove
	
}

void AALevelPiece::BeginPlay() { // when is this called?
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("CALLED"));
}



float AALevelPiece::MovePiece(float MovementSpeed, float DeltaTime) {
	AddActorLocalOffset(FVector(-MovementSpeed * DeltaTime, 0,0));
	return GetActorLocation().X;
}

