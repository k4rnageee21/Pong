#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PongBall.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS(Abstract)
class PONG_API APongBall : public AActor
{
	GENERATED_BODY()
	
public:	
	APongBall();

	virtual void PostNetReceiveLocationAndRotation() override;

	void Restart(FVector StartLocation = FVector::ZeroVector);

protected:
	virtual void BeginPlay() override;

	void Start();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Components)
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Components)
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Components)
	TObjectPtr<UProjectileMovementComponent> Movement;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Config | Defaults")
	float StartXMinVelocity = 2000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Config | Defaults")
	float StartXMaxVelocity = 3000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Config | Defaults")
	float StartYMinVelocity = 250.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Config | Defaults")
	float StartYMaxVelocity = 500.f;
};
