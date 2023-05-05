// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RollingBall.generated.h"

UCLASS()
class ENDLESSRUNNERGAME_API ARollingBall : public AActor { // they need an identifier
	
	GENERATED_BODY()
public:
	ARollingBall();
	float const BallRadie = 50.0f;
	float MovementSpeed = 800.0f;
	float LifeTime;
	
	UPROPERTY(VisibleAnywhere)
	int32 Lane;

	float Move(float Deltatime);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Details Ref")
	TObjectPtr<UStaticMeshComponent> Mesh;

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void Tick(float DeltaTime) override;
};
