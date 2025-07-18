#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PongHUD.generated.h"

class UPongPlayerOverlayWidget;

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
};
