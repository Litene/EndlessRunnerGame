// Fill out your copyright notice in the Description page of Project Settings.

#include "RollingBall.h"
#include "DebugMacros.h"

// Sets default values
ARollingBall::ARollingBall() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
}

// Called when the game starts or when spawned
void ARollingBall::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void ARollingBall::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	FVector Start = GetActorLocation();
	FVector Direction = GetActorUpVector() * -1;
	//float Magnitude = 50.0f;
	FVector End = Direction;
	FCollisionParameters HitParams;
	
	//DrawDebugLine(GetWorld(), Start, End, FColor::Red ,false, -1.0f , 0, 2);
	
	
}
