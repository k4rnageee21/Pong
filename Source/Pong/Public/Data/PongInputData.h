#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PongInputData.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class PONG_API UPongInputData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UInputAction> MoveAction;
};
