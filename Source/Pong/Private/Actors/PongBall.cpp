#include "Actors/PongBall.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

APongBall::APongBall()
{
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;
	SetReplicateMovement(true);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	RootComponent = Sphere;
	Sphere->InitSphereRadius(50.f);
	Sphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->InitialSpeed = 0.f;
	Movement->MaxSpeed = 0.f;
	Movement->bRotationFollowsVelocity = false;
	Movement->bInitialVelocityInLocalSpace = false;
	Movement->bShouldBounce = true;
	Movement->Bounciness = 1.f;
	Movement->Friction = 0.f;
	Movement->ProjectileGravityScale = 0.f;
	Movement->bInterpMovement = true;
	Movement->InterpLocationTime = 0.03f;
}

void APongBall::PostNetReceiveLocationAndRotation()
{
	const FRepMovement& LocalRepMovement = GetReplicatedMovement();
	const FVector NewLocation = FRepMovement::RebaseOntoLocalOrigin(LocalRepMovement.Location, this);

	if (IsValid(Movement))
	{
		Movement->MoveInterpolationTarget(NewLocation, LocalRepMovement.Rotation);
	}

	Super::PostNetReceiveLocationAndRotation();
}

void APongBall::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(Movement)) Movement->SetInterpolatedComponent(Mesh);

	if (HasAuthority())
	{
		Start();
	}
	else
	{
		if (IsValid(Movement)) Movement->bSimulationEnabled = false;
	}
}

void APongBall::Start()
{
	if (HasAuthority())
	{
		// Vertical (X) velocity
		const float XVelocity = (FMath::RandBool() ? 1.f : -1.f) * FMath::RandRange(StartXMinVelocity, StartXMaxVelocity);

		// Horizontal (Y) velocity
		const float YVelocity = (FMath::RandBool() ? 1.f : -1.f) * FMath::RandRange(StartYMinVelocity, StartYMaxVelocity);

		const FVector StartVelocity = FVector(XVelocity, YVelocity, 0.f);
		Movement->Velocity = StartVelocity;
	}
}

void APongBall::Reset(FVector StartLocation)
{
	if (HasAuthority())
	{
		SetActorLocation(StartLocation);
		Start();
	}
}
