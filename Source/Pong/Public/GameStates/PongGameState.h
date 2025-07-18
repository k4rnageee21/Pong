#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Data/PongMatchState.h"
#include "PongGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMatchStateChangedSignature, EPongMatchState, NewMatchState);

UCLASS(Abstract)
class PONG_API APongGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	APongGameState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintAssignable, Category = Events)
	FOnMatchStateChangedSignature OnMatchStateChanged;

	UFUNCTION(BlueprintPure)
	EPongMatchState GetMatchState() const;

	void SetMatchState(EPongMatchState InMatchState);

private:
	UFUNCTION()
	void OnRep_MatchState();

	UPROPERTY(ReplicatedUsing = OnRep_MatchState)
	EPongMatchState MatchState = EPongMatchState::WaitingForPlayers;
};
