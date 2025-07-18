// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PongGoal.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoredSignature, APongGoal*, Goal);

class UBoxComponent;

UCLASS(Abstract)
class PONG_API APongGoal : public AActor
{
	GENERATED_BODY()
	
public:	
	APongGoal();

	UPROPERTY(BlueprintAssignable, Category = Events)
	FOnScoredSignature OnScored;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnGoalAreaOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Components)
	TObjectPtr<UBoxComponent> GoalArea;
};
