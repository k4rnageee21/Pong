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

	UFUNCTION(BlueprintCallable)
	void Reset(FVector StartLocation = FVector::ZeroVector);

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Config | Runtime")
	float StartXMinVelocity = 2000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Config | Runtime")
	float StartXMaxVelocity = 3000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Config | Runtime")
	float StartYMinVelocity = 250.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Config | Runtime")
	float StartYMaxVelocity = 500.f;
};
