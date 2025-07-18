#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Data/PongMatchState.h"
#include "PongHUD.generated.h"

class UPongPlayerOverlayWidget;

/**
 * APongHUD
 * Acts like a controller in MVC for the gameplay logic (model) and widgets (view). Also is responsible
 * for widgets creation.
 */
UCLASS(Abstract)
class PONG_API APongHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config | Widgets | Player Overlay")
	TSubclassOf<UPongPlayerOverlayWidget> PlayerOverlayWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config | Widgets | Player Overlay")
	TObjectPtr<UPongPlayerOverlayWidget> PlayerOverlayWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config | Widgets | Player Overlay")
	int32 PlayerOverlayWidgetOrderZ = 1;

private:
	void CreatePlayerOverlayWidget();
	void InitPlayerOverlayWidget();
	void InitScore();

	UFUNCTION()
	void OnMatchStateChanged(EPongMatchState NewMatchState);

	UFUNCTION()
	void OnPlayerScoreChanged(int32 NewPlayerScore);

	UFUNCTION()
	void OnOpponentScoreChanged(int32 NewOpponentScore);
};
