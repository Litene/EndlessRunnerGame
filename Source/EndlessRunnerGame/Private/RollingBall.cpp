// Fill out your copyright notice in the Description page of Project Settings.

#include "RollingBall.h"
#include "DebugMacros.h"
#include "EndlessCharacterController.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstanceProxy.h"
#include "Components/SphereComponent.h"


ARollingBall::ARollingBall() : LifeTime(0) {
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
}


void ARollingBall::BeginPlay() {
	Super::BeginPlay();
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ARollingBall::OnOverlapBegin);

	if (GetActorLocation().Y < 230.0f) { Lane = 0; }
	else { Lane = 1; }
}

void ARollingBall::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                  const FHitResult& SweepResult) {
	if (OtherActor->IsA(AEndlessCharacterController::StaticClass())) {
		AEndlessCharacterController* Char = Cast<AEndlessCharacterController>(OtherActor);
		if (Char) {
			Char->RemoveLife();
			Destroy();
		}
	}
	else if (false) {
		// add remove wall, no clue what this is
	}
}

void ARollingBall::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	FVector Start = GetActorLocation();
	FVector Direction = FVector::DownVector;
	float Magnitude = 500.0f;
	FVector End = GetActorLocation() + FVector(0, 0, -80);
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	FHitResult Hit;

	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_WorldStatic, Params);
	if (GetWorld() && Hit.GetActor() != nullptr) {
		float Zlocation = Hit.Location.Z + BallRadie;
		FVector NextStep = FVector(Start.X + (-MovementSpeed * DeltaTime), Start.Y, Zlocation);
		SetActorLocation(NextStep);
	}


	if (GetActorLocation().X < -1000) {
		int32 RandomRoll = FMath::RandRange(0, 3);
		if (RandomRoll == 2) {
			
			TArray<AActor*> Balls;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARollingBall::StaticClass(), Balls);

			TArray<TObjectPtr<ARollingBall>> CastedBalls;
			for (auto Ball : Balls) {
				TObjectPtr<ARollingBall> CastedBall = Cast<ARollingBall>(Ball);  
				if (Ball != this && CastedBall->Lane == Lane) {
					CastedBalls.Add(Cast<ARollingBall>(Ball));
				}
			}
			Algo::SortBy(CastedBalls, &ARollingBall::LifeTime);

			if (CastedBalls.Num() > 0) {
				CastedBalls[0]->Destroy();
			}
			
		}
		Destroy();
	}
}

float ARollingBall::Move(float Deltatime) {
	Super::Tick(Deltatime);
	FVector Start = GetActorLocation();
	FVector Direction = FVector::DownVector;
	float Magnitude = 500.0f;
	FVector End = GetActorLocation() + FVector(0, 0, -80);
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	FHitResult Hit;

	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_WorldStatic, Params);
	if (GetWorld() && Hit.GetActor() != nullptr) {
		float Zlocation = Hit.Location.Z + BallRadie;
		FVector NextStep = FVector(Start.X + (-MovementSpeed * Deltatime), Start.Y, Zlocation);
		SetActorLocation(NextStep);
		return NextStep.X;
	}
	return 0;
}

