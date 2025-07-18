#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PongPlayerOverlayWidget.generated.h"

class UTextBlock;

UCLASS(Abstract)
class PONG_API UPongPlayerOverlayWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetPlayerScoreText(int32 Score);

	UFUNCTION(BlueprintCallable)
	void SetOpponentScoreText(int32 Score);

	UFUNCTION(BlueprintCallable)
	void SetMessageText(const FString& InMessage);

	UFUNCTION(BlueprintCallable)
	void SetScoreVisibility(bool bVisibility);

	UFUNCTION(BlueprintCallable)
	void SetMessageVisibility(bool bVisibility);

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayerScoreLabel;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> OpponentScoreLabel;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> MessageLabel;
};
