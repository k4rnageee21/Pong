#include "GameModes/PongGameMode.h"
#include "Actors/PongSetup.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "Actors/PongBall.h"
#include "GameStates/PongGameState.h"

DEFINE_LOG_CATEGORY_STATIC(LogPongGameMode, Log, All);

APongGameMode::APongGameMode()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APongGameMode::BeginPlay()
{
	Super::BeginPlay();

	FindPongSetup();
}

void APongGameMode::InitGameState()
{
	Super::InitGameState();

	PongGameState = GetGameState<APongGameState>();
	if (!IsValid(PongGameState))
	{
		UE_LOG(LogPongGameMode, Warning, TEXT("Can't find an appropriate game state! Can't start the game properly! Select the appropriate game state class (derived from APongGameState)!"));
		return;
	}
}

void APongGameMode::SetMatchState(EPongMatchState NewState)
{
	if (IsValid(PongGameState))
	{
		PongGameState->SetMatchState(NewState);
	}
}

void APongGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (ShouldStartMatch())
	{
		PrepareToStartMatch();
	}
}

bool APongGameMode::ShouldStartMatch()
{
	return GetNumPlayers() >= PlayersToStartMatch;
}

void APongGameMode::PrepareToStartMatch()
{
	UWorld* World = GetWorld();
	if (!IsValid(World)) return;

	SetMatchState(EPongMatchState::WaitingToStart);

	FTimerHandle TH;
	World->GetTimerManager().SetTimer(TH, this, &ThisClass::StartMatch, StartMatchDelay, false);
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

void APongGameMode::StartMatch()
{
	SetMatchState(EPongMatchState::InProgress);

	SpawnBall();
}

void APongGameMode::SpawnBall()
{
	if (!BallClass)
	{
		UE_LOG(LogPongGameMode, Warning, TEXT("Can't find a ball class! Can't start the game properly!"));
		return;
	}

	UWorld* World = GetWorld();
	if (!IsValid(World)) return;

	const FRotator ZeroRotator = FRotator::ZeroRotator;
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	PongBall = World->SpawnActor<APongBall>(BallClass, BallSpawnLocation, ZeroRotator, SpawnParams);
	if (!IsValid(PongBall))
	{
		UE_LOG(LogPongGameMode, Warning, TEXT("Can't spawn a ball object! Can't start the game properly!"));
	}
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
