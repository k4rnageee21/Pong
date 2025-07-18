#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PongPaddle.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UFloatingPawnMovement;

UCLASS(Abstract)
class PONG_API APongPaddle : public APawn
{
	GENERATED_BODY()

public:
	APongPaddle();

	void Move(float AxisValue);

protected:
	UFUNCTION(Server, Reliable)
	void ServerMove(FVector_NetQuantize TargetLocation);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Components)
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Components)
	TObjectPtr<UCameraComponent> TPCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Components)
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Components)
	TObjectPtr<UFloatingPawnMovement> Movement;
};
