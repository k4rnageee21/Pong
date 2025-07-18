#include "UI/PongHUD.h"
#include "UI/Widgets/PongPlayerOverlayWidget.h"

void APongHUD::BeginPlay()
{
	Super::BeginPlay();

	CreatePlayerOverlayWidget();
}

void APongHUD::CreatePlayerOverlayWidget()
{
	if (!PlayerOverlayWidgetClass || IsValid(PlayerOverlayWidget)) return;

	PlayerOverlayWidget = CreateWidget<UPongPlayerOverlayWidget>(GetOwningPlayerController(), PlayerOverlayWidgetClass);
	if (IsValid(PlayerOverlayWidget))
	{
		PlayerOverlayWidget->AddToViewport(PlayerOverlayWidgetOrderZ);
	}
}
