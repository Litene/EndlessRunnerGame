#pragma once

#include "CoreMinimal.h"
#include "PooledObject.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "ALevelPiece.generated.h"


UENUM()
enum class EPieceType : uint8 {
	Floor,
	Top,
	RampUp,
	RampDown
};


UCLASS()
class ENDLESSRUNNERGAME_API AALevelPiece : public APooledObject {
	GENERATED_BODY()

public:
	AALevelPiece();

	FRotator GetCurrentRotation(); // cleanup
	//	class ASpawnManager* Spawner;

	UPROPERTY(EditDefaultsOnly, Category="Setup") // maybe not, get name maybe?
	EPieceType PieceType;

	UPROPERTY(EditDefaultsOnly, Category="Setup")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditDefaultsOnly, Category="Setup")
	TObjectPtr<UArrowComponent> Arrow;

	UPROPERTY(EditDefaultsOnly, Category="Setup")
	TArray<FString> SocketNames;

	UPROPERTY(EditAnywhere, Category="Setup")
	FString NameIdentifier;

	FString GetCorrectName(EPieceType pieceType);
	//void Initialize(ASpawnManager* self);

	
	void OnFinishedMoving();

protected:
	virtual void BeginPlay() override;

public:
	float MovePiece(float MovementSpeed, float DeltaTime);
};
