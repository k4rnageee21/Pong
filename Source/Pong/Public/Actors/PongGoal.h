// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PongGoal.generated.h"

class UBoxComponent;

UCLASS(Abstract)
class PONG_API APongGoal : public AActor
{
	GENERATED_BODY()
	
public:	
	APongGoal();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnGoalAreaOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Components)
	TObjectPtr<UBoxComponent> GoalArea;
};
