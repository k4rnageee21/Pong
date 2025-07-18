#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PongPlayerController.generated.h"

class UPongInputData;
struct FInputActionValue;

UCLASS(Abstract)
class PONG_API APongPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void Move(const FInputActionValue& Value);

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Input)
	TObjectPtr<UPongInputData> InputData;
};
