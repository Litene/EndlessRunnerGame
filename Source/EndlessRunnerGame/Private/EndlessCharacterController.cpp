#include "EndlessCharacterController.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Runtime/Engine/Classes/Components/TimelineComponent.h"
#include "GameFramework/SpringArmComponent.h"

AEndlessCharacterController::AEndlessCharacterController() : StartLocation(FVector::Zero()),
                                                             EndLocation(FVector::Zero()), MovementOffset(100),
                                                             CurrentPos(1), CurrentState(CharacterState::InLane) {
	PrimaryActorTick.bCanEverTick = true;
	MyTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimeLine"));
	
	InterpFunction.BindUFunction(this, FName("TimelineFloatReturn"));
	InterpFinished.BindUFunction(this, FName("OnTimelineFinished"));

	CameraBoom->SetRelativeRotation(FRotator(0, -40.0f, 0));
	
}

void AEndlessCharacterController::BeginPlay() {
	Super::BeginPlay();

	if (SmoothCurve) {
		MyTimeline->AddInterpFloat(SmoothCurve, InterpFunction, FName("Alpha"));
		MyTimeline->SetTimelineFinishedFunc(InterpFinished);

		MyTimeline->SetLooping(false);
	}
}

bool AEndlessCharacterController::AllowedTransition(int desiredPos) {
	return desiredPos <= 2 && desiredPos >= 0;
}

void AEndlessCharacterController::TimelineFloatReturn(float Value) {
	SetActorLocation(FMath::Lerp(StartLocation, EndLocation, Value));
}

void AEndlessCharacterController::OnTimelineFinished() {
	CurrentState = InLane;
}




void AEndlessCharacterController::Move(const FInputActionValue& Value) {
	const int moveDirection = static_cast<int>(Value.Get<FVector2D>().X);

	if (CurrentState == InLane && AllowedTransition(CurrentPos + moveDirection) && !GetMovementComponent()->IsFalling()) {
		CurrentPos += moveDirection;
		SCREEN_LOG("YO");
		StartLocation = GetActorLocation();
		EndLocation = FVector(StartLocation.X, StartLocation.Y + (MovementOffset * moveDirection), StartLocation.Z);
		// A bit messy since the world is flipped. 
		CurrentState = MovingLane;
		MyTimeline->PlayFromStart();
	}
}

void AEndlessCharacterController::Jump() {
	if (CurrentState == InLane) {
		Super::Jump();
	}
}
