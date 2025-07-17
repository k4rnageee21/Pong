#include "Pawns/PongPaddle.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

APongPaddle::APongPaddle()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	TPCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TPCamera"));
	TPCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TPCamera->bUsePawnControlRotation = false;
}
