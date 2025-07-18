#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Data/PongMatchState.h"
#include "PongGameMode.generated.h"

class APongSetup;
class APongBall;
class APongGoal;
class APongGameState;

/**
 * APongGameMode
 *
 * The main authoritative class fully responsible for game rules, match progression, and overall game flow.
 * Manages match start logic, game preparation, player-goal bindings, and ball spawning.
 *
 * Uses a custom MatchState system — a simplified version of AGameMode’s built-in MatchState —
 * because the task required extending AGameModeBase class, which does not provide built-in match state management.
 */
UCLASS(Abstract)
class PONG_API APongGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	APongGameMode();

	//~ Begin AGameModeBase Interface
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	virtual void InitGameState() override;
	//~ End	  AGameModeBase Interface

protected:
	virtual void BeginPlay() override;

	virtual void PostLogin(APlayerController* NewPlayer) override;

	//~ Begin Pong Game Rules Functions
	void SetMatchState(EPongMatchState NewState);
	void OnPlayerSideChosen(APongGoal* SideGoal, AController* Player);
	void FindPongSetup();
	bool ShouldStartMatch();
	void PrepareToStartMatch();
	void StartMatch();
	void SpawnBall();
	
	UFUNCTION()
	void OnGoalScored(APongGoal* Goal);
	//~ End Pong Game Rules Functions

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Classes)
	TSubclassOf<APongBall> BallClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Config | Defaults")
	FVector BallRestartLocation = FVector::ZeroVector;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Config | Defaults")
	int32 PlayersToStartMatch = 2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Config | Defaults")
	float StartMatchDelay = 5.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Config | Defaults")
	int32 ScoreIncrement = 1;

	UPROPERTY()
	TObjectPtr<APongSetup> PongSetup;

	UPROPERTY()
	TObjectPtr<APongBall> PongBall;

	UPROPERTY()
	TObjectPtr<APongGameState> PongGameState;

	UPROPERTY()
	TMap<TObjectPtr<APongGoal>, TObjectPtr<AController>> GoalsControllersSetup;
};
