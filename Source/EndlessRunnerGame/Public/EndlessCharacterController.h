// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "DebugMacros.h"
#include "Components/StaticMeshComponent.h"
#include "EndlessRunnerGame/EndlessRunnerGameCharacter.h"
#include "EndlessCharacterController.generated.h"

/**
 * TODO: 
 * 1. CoyoteTimer and InputTimer for move and jump.
 * 
 * */
UCLASS()
class ENDLESSRUNNERGAME_API AEndlessCharacterController : public AEndlessRunnerGameCharacter {
	GENERATED_BODY()

public:
	AEndlessCharacterController();

	UPROPERTY(EditAnywhere, Category="MyTimeline")
	class UCurveFloat* SmoothCurve;
	UPROPERTY(EditAnywhere, Category="MyTimeline")
	class UTimelineComponent* MyTimeline; // raw pointer? why can't this be a smartpointer? 

	//Coyote Timer
	UPROPERTY(VisibleAnywhere)
	int CurrentLife;

	UFUNCTION()
	void TimelineFloatReturn(float Value); //event?
	UFUNCTION()
	void OnTimelineFinished();

	FOnTimelineFloat InterpFunction{};

	FOnTimelineEvent InterpFinished{};

	UPROPERTY()
	FVector StartLocation;
	UPROPERTY()
	FVector EndLocation;


	UPROPERTY(VisibleAnywhere)
	int32 playerNumber;
	
	const float MovementOffset = 300;
	
	enum CharacterState {
		InLane,
		MovingLane,
	};

	void RemoveLife();

protected:

	virtual void Jump() override;

	virtual void BeginPlay() override;

	virtual void Move(const FInputActionValue& Value);
	virtual void P2Move(const FInputActionValue& Value);

	virtual void EscapeKey();
	virtual void EnterKey();
public:
	UPROPERTY(VisibleAnywhere)
	int CurrentPos;
	TArray<float> SetPositions1;
	TArray<float> SetPositions2;
	float GetCorrectPosition(int ID, int Pos); 
	CharacterState CurrentState;
	void Die();
	bool AllowedTransition(int DesiredPos);
	bool CheckDirection(int DesiredPos, AEndlessCharacterController* Controller, int PlayerID);
};
