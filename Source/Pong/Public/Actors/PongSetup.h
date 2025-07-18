#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PongSetup.generated.h"

class APlayerStart;
class APongGoal;

USTRUCT(BlueprintType)
struct FPongPlayerSide
{
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	TObjectPtr<APlayerStart> PlayerSpawn;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	TObjectPtr<APongGoal> PlayerGoal;
};

UCLASS(Abstract)
class PONG_API APongSetup : public AActor
{
	GENERATED_BODY()
	
public:	
	APongSetup();

	FPongPlayerSide GetFreePlayerSide();

protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Config | Runtime")
	TArray<FPongPlayerSide> PlayerSides;
};
