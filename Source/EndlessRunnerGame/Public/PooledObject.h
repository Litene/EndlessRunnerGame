// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PooledObject.generated.h"

UCLASS()
class ENDLESSRUNNERGAME_API APooledObject : public AActor {
	GENERATED_BODY()

public:

	// Sets default values for this actor's properties
	APooledObject();
	//void Initialize();
	//bool Active();
	//void Deactivate(APooledObject* Object);
	//APooledObject* Activate();
	//bool Destroy();
	//APooledObject* Create();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
