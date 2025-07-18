#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PongPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerScoreChangedSignature, int32, NewScore);

UCLASS(Abstract)
class PONG_API APongPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintAssignable, Category = Events)
	FOnPlayerScoreChangedSignature OnPlayerScoreChanged;

	void SetPlayerScore(int32 InPlayerScore);
	FORCEINLINE int32 GetPlayerScore() const { return PlayerScore; }

private:
	UFUNCTION()
	void OnRep_PlayerScore();

	UPROPERTY(ReplicatedUsing = OnRep_PlayerScore)
	int32 PlayerScore;
};
