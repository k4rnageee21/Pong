#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Data/PongMatchState.h"
#include "PongGameMode.generated.h"

class APongSetup;
class APongBall;
class APongGoal;
class APongGameState;

UCLASS(Abstract)
class PONG_API APongGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	APongGameMode();

	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	virtual void InitGameState() override;

protected:
	virtual void BeginPlay() override;

	virtual void PostLogin(APlayerController* NewPlayer) override;

	bool ShouldStartMatch();
	void PrepareToStartMatch();

	void FindPongSetup();

	UFUNCTION(BlueprintCallable)
	void StartMatch();

	void InitGoals();
	void SpawnBall();

	void SetMatchState(EPongMatchState NewState);

	void OnPlayerSideChosen(APongGoal* SideGoal, AController* Player);

	UFUNCTION()
	void OnGoalScored(APongGoal* Goal);

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
