#include "EndlessCharacterController.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Math/UnrealMathUtility.h"
#include "DebugMacros.h"
#include "UIManager.h"
#include "EndlessRunnerGame/EndlessRunnerGameGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Components/TimelineComponent.h"
#include "GameFramework/SpringArmComponent.h"

AEndlessCharacterController::AEndlessCharacterController() : CurrentLife(3),
                                                             StartLocation(FVector::Zero()),
                                                             EndLocation(FVector::Zero()),
                                                             MovementOffset(100), CurrentPos(1),
                                                             CurrentState(CharacterState::InLane) {
	PrimaryActorTick.bCanEverTick = true;
	MyTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimeLine"));

	InterpFunction.BindUFunction(this, FName("TimelineFloatReturn"));
	InterpFinished.BindUFunction(this, FName("OnTimelineFinished"));

	CameraBoom->SetRelativeRotation(FRotator(0, -40.0f, 0));

	SetPositions1.Add(-50.0f); // these need to change...
	SetPositions1.Add(50.0f);
	SetPositions1.Add(150.0f);

	SetPositions2.Add(330.0f); // these need to change...
	SetPositions2.Add(430.0f);
	SetPositions2.Add(530.0f);
}

void AEndlessCharacterController::BeginPlay() {
	Super::BeginPlay();

	if (this->GetName() == "BP_ThirdPersonCharacter_C_0")
		this->SetActorLocation(FVector(150, 50, 200));
	else
		this->SetActorLocation(FVector(150, 430, 200));


	if (this->GetActorLocation().Y < 300)
		playerNumber = 0;
	else
		playerNumber = 1;

	if (SmoothCurve) {
		MyTimeline->AddInterpFloat(SmoothCurve, InterpFunction, FName("Alpha"));
		MyTimeline->SetTimelineFinishedFunc(InterpFinished);

		MyTimeline->SetLooping(false);
	}
}

float AEndlessCharacterController::GetCorrectPosition(int ID, int Pos) {
	if (ID == 0) {
		return SetPositions1[Pos];
	}

	return SetPositions2[Pos];
}



bool AEndlessCharacterController::AllowedTransition(int desiredPos) {
	return desiredPos <= 2 && desiredPos >= 0;
}

bool AEndlessCharacterController::CheckDirection(int DesiredPos, AEndlessCharacterController* OtherController,
                                                 int PlayerID) {
	int Direction = 1;
	if (DesiredPos < OtherController->CurrentPos) {
		Direction *= -1;
	}

	if (PlayerID == 0) {
		FVector Start = GetActorLocation() + FVector(0, 0, -50.0f);
		float Magnitude = 60.0f;
		FVector End = GetActorLocation() + FVector(0, Magnitude * Direction, -50.0f); // magic numbers
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);
		FHitResult Hit;
		GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_WorldStatic, Params);
		if (Hit.GetActor() == nullptr) {
			return true;
		}

		DrawDebugLine(GetWorld(), Start, End, FColor::Cyan, true, 10.0f, 0, 2);
		return false;
	}
	else {
		FVector Start = OtherController->GetActorLocation() + FVector(0, 0, -50.0f);
		float Magnitude = 60.0f;
		FVector End = OtherController->GetActorLocation() + FVector(0, Magnitude * Direction, -50.0f); // magic numbers
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(OtherController);
		FHitResult Hit;
		GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_WorldStatic, Params);
		if (Hit.GetActor() == nullptr) {
			return true;
		}
		UE_LOG(LogTemp, Warning, TEXT("HIT ACTOR %s"), *Hit.GetActor()->GetName())

		DrawDebugLine(GetWorld(), Start, End, FColor::Cyan, true, 10.0f, 0, 2);
		return false;
	}
}

void AEndlessCharacterController::P2Move(const FInputActionValue& Value) {
	const int moveDirection = static_cast<int>(Value.Get<FVector2D>().X);
	AEndlessCharacterController* OtherCharacter = Cast<AEndlessCharacterController>(
		UGameplayStatics::GetPlayerController(GetWorld(), 1)->GetCharacter());

	if (OtherCharacter->CurrentState == InLane && OtherCharacter->AllowedTransition(
			OtherCharacter->CurrentPos + moveDirection) && !
		OtherCharacter->GetMovementComponent()->IsFalling()
		&& CheckDirection(OtherCharacter->CurrentPos + moveDirection, OtherCharacter, 1)) {
		OtherCharacter->CurrentPos += moveDirection;
		OtherCharacter->StartLocation = OtherCharacter->GetActorLocation();
		OtherCharacter->EndLocation = FVector(OtherCharacter->StartLocation.X,
		                                      GetCorrectPosition(1, OtherCharacter->CurrentPos),
		                                      OtherCharacter->StartLocation.Z);
	
		OtherCharacter->CurrentState = MovingLane;
		OtherCharacter->MyTimeline->PlayFromStart();
	}
}

void AEndlessCharacterController::EscapeKey() {
	//Super::EscapeKey();
	UE_LOG(LogTemp, Warning, TEXT("YO we do be pressing Escape"));
}

void AEndlessCharacterController::EnterKey() {
	//Super::EnterKey();
	UE_LOG(LogTemp, Warning, TEXT("Yo we do be pressing enter"));
	
}

void AEndlessCharacterController::Move(const FInputActionValue& Value) {
	const int moveDirection = static_cast<int>(Value.Get<FVector2D>().X);
	

	if (CurrentState == InLane && AllowedTransition(CurrentPos + moveDirection) && !GetMovementComponent()->IsFalling()
		&& CheckDirection(CurrentPos + moveDirection, this, 0)) {
		CurrentPos += moveDirection;
		StartLocation = GetActorLocation();
		//fix locaction based on level 
		EndLocation = FVector(StartLocation.X, GetCorrectPosition(playerNumber, CurrentPos), StartLocation.Z);
		CurrentState = MovingLane;
		MyTimeline->PlayFromStart();
	}
}

void AEndlessCharacterController::RemoveLife() {
	CurrentLife--;
	int ClampedLife = FMath::Clamp(CurrentLife, 0, 3);
	if (!GetWorld()) return;
	
	AActor* FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AUIManager::StaticClass());
	AUIManager* Manager = Cast<AUIManager>(FoundActor);
	if (Manager) {
		Manager->RemoveLife(ClampedLife, playerNumber); // take in player ID
		if (CurrentLife == 0) {
			Manager->PlayerDie(playerNumber);
			GetMesh()->SetVisibility(false, true);
		}
	}
}


void AEndlessCharacterController::TimelineFloatReturn(float Value) {
	SetActorLocation(FMath::Lerp(StartLocation, EndLocation, Value));
}

void AEndlessCharacterController::OnTimelineFinished() {
	CurrentState = InLane;
}


//
// void AEndlessCharacterController::P2Move(const FInputActionValue& Value) {
// 	const int moveDirection = static_cast<int>(Value.Get<FVector2D>().X);
//
// 	if (CurrentState == InLane && AllowedTransition(CurrentPos + moveDirection) && !GetMovementComponent()->IsFalling()
// 		&& CheckDirection(CurrentPos + moveDirection, 1)) {
// 		CurrentPos += moveDirection;
// 		StartLocation = GetActorLocation();
// 		//fix locaction based on level 
// 		EndLocation = FVector(StartLocation.X, GetCorrectPosition(playerNumber, CurrentPos), StartLocation.Z);
// 		CurrentState = MovingLane;
// 		MyTimeline->PlayFromStart();
// 		}
// }

void AEndlessCharacterController::Jump() {
	if (CurrentState == InLane) {
		Super::Jump();
	}
}
