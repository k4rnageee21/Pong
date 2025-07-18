#include "GameModes/PongGameMode.h"
#include "Actors/PongSetup.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"

DEFINE_LOG_CATEGORY_STATIC(LogPongGameMode, Log, All);

void APongGameMode::BeginPlay()
{
	Super::BeginPlay();

	FindPongSetup();
}

void APongGameMode::FindPongSetup()
{
	if (IsValid(PongSetup)) return;

	APongSetup* FoundSetup = Cast<APongSetup>(UGameplayStatics::GetActorOfClass(this, APongSetup::StaticClass()));
	if (!IsValid(FoundSetup))
	{
		UE_LOG(LogPongGameMode, Warning, TEXT("Can't find a pong setup object! Can't start the game properly!"));
		return;
	}

	PongSetup = FoundSetup;
}

AActor* APongGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	AActor* ChosenStart = nullptr;

	if (!IsValid(PongSetup))
	{
		FindPongSetup();
		if (!IsValid(PongSetup)) return ChosenStart;
	}

	FPongPlayerSide PongPlayerSide = PongSetup->GetFreePlayerSide();
	if (!IsValid(PongPlayerSide.PlayerSpawn))
	{
		UE_LOG(LogPongGameMode, Warning, TEXT("Can't find free spot for the player on the arena!"));
		return ChosenStart;
	}

	ChosenStart = PongPlayerSide.PlayerSpawn;

	return ChosenStart;
}