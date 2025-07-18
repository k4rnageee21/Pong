#include "PlayerStates/PongPlayerState.h"
#include "Net/UnrealNetwork.h"

void APongPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APongPlayerState, PlayerScore);
}

void APongPlayerState::OnRep_PlayerScore()
{
	OnPlayerScoreChanged.Broadcast(PlayerScore);
}

void APongPlayerState::SetPlayerScore(int32 InPlayerScore)
{
	if (!HasAuthority()) return;

	if (PlayerScore != InPlayerScore)
	{
		PlayerScore = InPlayerScore;
		OnRep_PlayerScore();
	}
}
