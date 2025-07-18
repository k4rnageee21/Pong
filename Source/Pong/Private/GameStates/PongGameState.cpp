#include "GameStates/PongGameState.h"
#include "Net/UnrealNetwork.h"

APongGameState::APongGameState()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APongGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APongGameState, MatchState);
}

EPongMatchState APongGameState::GetMatchState() const
{
	return MatchState;
}

void APongGameState::SetMatchState(EPongMatchState InMatchState)
{
	if (HasAuthority() && MatchState != InMatchState)
	{
		MatchState = InMatchState;
		OnRep_MatchState();
	}
}

APlayerState* APongGameState::GetOpponentPlayerState(APlayerState* RequestingPlayerState) const
{
	for (APlayerState* PlayerState : PlayerArray)
	{
		if (PlayerState != RequestingPlayerState) return PlayerState;
	}

	return nullptr;
}

void APongGameState::OnRep_MatchState()
{
	OnMatchStateChanged.Broadcast(MatchState);
}
