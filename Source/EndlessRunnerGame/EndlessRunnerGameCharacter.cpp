// Copyright Epic Games, Inc. All Rights Reserved.

#include "EndlessRunnerGameCharacter.h"

#include "EndlessCharacterController.h"
#include "EndlessRunnerGameGameMode.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"

AEndlessRunnerGameCharacter::AEndlessRunnerGameCharacter() {
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;


	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
}

void AEndlessRunnerGameCharacter::BeginPlay() {
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller)) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}



// void AEndlessRunnerGameCharacter::SetGameOverKeys(bool GameOver, AController* LocalController ) {
// 	if (GameOver) {
// 		if (APlayerController* PlayerController = Cast<APlayerController>(Controller)) {
// 			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
// 				UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
// 				Subsystem->ClearAllMappings();
// 				Subsystem->AddMappingContext(GameOverMappingContext, 0);
// 				}
// 		}
// 	}
// 	else {
// 		if (APlayerController* PlayerController = Cast<APlayerController>(LocalController)) {
// 			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
// 				UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
// 				Subsystem->RemoveMappingContext(GameOverMappingContext);
// 			}
// 		}
// 	}
// }


void AEndlessRunnerGameCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) {
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this,
		                                   &AEndlessRunnerGameCharacter::Move);

		EnhancedInputComponent->BindAction(P2JumpAction, ETriggerEvent::Triggered, this,
		                                   &AEndlessRunnerGameCharacter::P2Jump);
		EnhancedInputComponent->BindAction(P2JumpAction, ETriggerEvent::Completed, this,
		                                   &AEndlessRunnerGameCharacter::P2StopJump);
		EnhancedInputComponent->BindAction(P2MoveAction, ETriggerEvent::Triggered, this,
		                                   &AEndlessRunnerGameCharacter::P2Move);

		EnhancedInputComponent->BindAction(EscapeGameOver, ETriggerEvent::Triggered, this,
		                                   &AEndlessRunnerGameCharacter::EscapeKey);
		EnhancedInputComponent->BindAction(EnterGameOver, ETriggerEvent::Triggered, this,
		                                   &AEndlessRunnerGameCharacter::EnterKey);
	}
}


void AEndlessRunnerGameCharacter::P2Jump() {
	UGameplayStatics::GetPlayerController(GetWorld(), 1)->GetCharacter()->Jump();
}

void AEndlessRunnerGameCharacter::P2StopJump() {
	UGameplayStatics::GetPlayerController(GetWorld(), 1)->GetCharacter()->StopJumping();
}

void AEndlessRunnerGameCharacter::EnterKey() {
	UE_LOG(LogTemp, Warning, TEXT("ENTERKEY"));
	// overrride in childclass
}

void AEndlessRunnerGameCharacter::EscapeKey() {
	UE_LOG(LogTemp, Warning, TEXT("escapeKEY"));
	// overrride in childclass
}

void AEndlessRunnerGameCharacter::P2Move(const FInputActionValue& Value) {
}


void AEndlessRunnerGameCharacter::Move(const FInputActionValue& Value) {
}
