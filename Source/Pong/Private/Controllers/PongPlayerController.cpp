#include "Controllers/PongPlayerController.h"
#include "Data/PongInputData.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "Pawns/PongPaddle.h"

DEFINE_LOG_CATEGORY_STATIC(LogPongPlayerController, Log, All);

void APongPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(InputData))
	{
		UE_LOG(LogPongPlayerController, Warning, TEXT("Invalid Input Data Asset! Select a valid one!"));
		return;
	}

	if (!IsValid(InputData->InputMappingContext))
	{
		UE_LOG(LogPongPlayerController, Warning, TEXT("Invalid Input Mapping Context! Select a valid one!"));
		return;
	}

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputData->InputMappingContext, 0);
	}
}

void APongPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (!IsValid(InputData))
	{
		UE_LOG(LogPongPlayerController, Warning, TEXT("Invalid Input Data Asset! Select a valid one!"));
		return;
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(InputData->MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
	}
}

void APongPlayerController::Move(const FInputActionValue& Value)
{
	const float AxisValue = Value.Get<float>();
	APongPaddle* Paddle = GetPawn<APongPaddle>();
	if (IsValid(Paddle) && IsLocalController())
	{
		Paddle->Move(AxisValue);
	}
}
