// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PongGameMode.generated.h"

class APongSetup;

UCLASS(Abstract)
class PONG_API APongGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

protected:
	virtual void BeginPlay() override;

	void FindPongSetup();

private:
	UPROPERTY()
	TObjectPtr<APongSetup> PongSetup;
};
