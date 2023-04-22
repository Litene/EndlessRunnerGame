// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RollingBall.generated.h"

UCLASS()
class ENDLESSRUNNERGAME_API ARollingBall : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARollingBall();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Details Ref")
	TObjectPtr<UStaticMeshComponent> Mesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};