#include "UI/PongHUD.h"
#include "UI/Widgets/PongPlayerOverlayWidget.h"
#include "Controllers/PongPlayerController.h"
#include "GameStates/PongGameState.h"
#include "PlayerStates/PongPlayerState.h"

void APongHUD::BeginPlay()
{
	Super::BeginPlay();

	CreatePlayerOverlayWidget();
	InitPlayerOverlayWidget();
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

void APongHUD::InitPlayerOverlayWidget()
{
	if (!IsValid(PlayerOverlayWidget)) return;

	UWorld* World = GetWorld();
	if (!IsValid(World)) return;
	
	APongGameState* PongGS = World->GetGameState<APongGameState>();
	if (!IsValid(PongGS)) return;
	
	OnMatchStateChanged(PongGS->GetMatchState());
	PongGS->OnMatchStateChanged.AddDynamic(this, &ThisClass::OnMatchStateChanged);
}

void APongHUD::InitScore()
{
	UWorld* World = GetWorld();
	if (!IsValid(World)) return;

	APongGameState* PongGS = World->GetGameState<APongGameState>();
	if (!IsValid(PongGS)) return;

	APlayerController* PC = GetOwningPlayerController();
	if (!IsValid(PC)) return;

	APongPlayerState* OwnerPlayerState = PC->GetPlayerState<APongPlayerState>();
	if (IsValid(OwnerPlayerState))
	{
		OnPlayerScoreChanged(OwnerPlayerState->GetPlayerScore());
		OwnerPlayerState->OnPlayerScoreChanged.AddDynamic(this, &ThisClass::OnPlayerScoreChanged);
	}

	APongPlayerState* OpponentPlayerState = Cast<APongPlayerState>(PongGS->GetOpponentPlayerState(OwnerPlayerState));
	if (IsValid(OpponentPlayerState))
	{
		OnOpponentScoreChanged(OpponentPlayerState->GetPlayerScore());
		OpponentPlayerState->OnPlayerScoreChanged.AddDynamic(this, &ThisClass::OnOpponentScoreChanged);
	}
}

void APongHUD::OnMatchStateChanged(EPongMatchState NewMatchState)
{
	if (NewMatchState == EPongMatchState::InProgress)
	{
		InitScore();
	}

	if (IsValid(PlayerOverlayWidget))
	{
		PlayerOverlayWidget->SetMessageText(PongMatchState::ToString(NewMatchState));
	}
}

void APongHUD::OnPlayerScoreChanged(int32 NewPlayerScore)
{
	if (IsValid(PlayerOverlayWidget))
	{
		PlayerOverlayWidget->SetPlayerScoreText(NewPlayerScore);
	}
}

void APongHUD::OnOpponentScoreChanged(int32 NewOpponentScore)
{
	if (IsValid(PlayerOverlayWidget))
	{
		PlayerOverlayWidget->SetOpponentScoreText(NewOpponentScore);
	}
}
