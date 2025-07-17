#include "Actors/PongGoal.h"
#include "Components/BoxComponent.h"
#include "Actors/PongBall.h"

APongGoal::APongGoal()
{
	PrimaryActorTick.bCanEverTick = false;

	GoalArea = CreateDefaultSubobject<UBoxComponent>(TEXT("GoalArea"));
	RootComponent = GoalArea;
}

void APongGoal::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
	{
		GoalArea->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnGoalAreaOverlap);
	}
}

void APongGoal::OnGoalAreaOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APongBall* PongBall = Cast<APongBall>(OtherActor);
	if (IsValid(PongBall))
	{
		PongBall->Reset();
	}
}
