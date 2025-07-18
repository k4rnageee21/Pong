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

void APongGameState::OnRep_MatchState()
{
	OnMatchStateChanged.Broadcast(MatchState);
}
