// Fill out your copyright notice in the Description page of Project Settings.


#include "PooledObject.h"

// Sets default values
APooledObject::APooledObject() {
	
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APooledObject::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void APooledObject::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}
