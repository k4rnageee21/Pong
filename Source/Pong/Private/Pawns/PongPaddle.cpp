#include "Pawns/PongPaddle.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

APongPaddle::APongPaddle()
{
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;
	SetReplicateMovement(true);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	TPCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TPCamera"));
	TPCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TPCamera->bUsePawnControlRotation = false;

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
}

void APongPaddle::Move(float AxisValue)
{
	AddMovementInput(GetActorRightVector(), AxisValue);

	if (GetLocalRole() == ENetRole::ROLE_AutonomousProxy)
	{
		ServerMove(GetActorLocation());
	}
}

void APongPaddle::ServerMove_Implementation(FVector_NetQuantize TargetLocation)
{
	SetActorLocation(TargetLocation, true);
}
