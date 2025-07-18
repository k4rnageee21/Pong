#include "UI/Widgets/PongPlayerOverlayWidget.h"
#include "Components/TextBlock.h"

#define LOCTEXT_NAMESPACE "PongGame"

void UPongPlayerOverlayWidget::SetPlayerScoreText(int32 Score)
{
	if (IsValid(PlayerScoreLabel))
	{
		FFormatNamedArguments Args;
		Args.Add("Score", Score);

		FText FormattedText = FText::Format(
			NSLOCTEXT("PongGame", "PlayerScoreLabel", "{Score}"),
			Args
		);

		PlayerScoreLabel->SetText(FormattedText);
	}
}

void UPongPlayerOverlayWidget::SetOpponentScoreText(int32 Score)
{
	if (IsValid(OpponentScoreLabel))
	{
		FFormatNamedArguments Args;
		Args.Add("Score", Score);

		FText FormattedText = FText::Format(
			NSLOCTEXT("PongGame", "OpponentScoreLabel", "{Score}"),
			Args
		);

		OpponentScoreLabel->SetText(FormattedText);
	}
}

void UPongPlayerOverlayWidget::SetMessageText(const FString& InMessage)
{
	if (IsValid(MessageLabel))
	{
		FFormatNamedArguments Args;
		Args.Add("Message", FText::FromString(InMessage));

		FText FormattedText = FText::Format(
			NSLOCTEXT("PongGame", "MessageLabel", "Match Status: {Message}"),
			Args
		);

		MessageLabel->SetText(FormattedText);
	}
}

void UPongPlayerOverlayWidget::SetScoreVisibility(bool bVisibility)
{
	if (IsValid(PlayerScoreLabel))
	{
		PlayerScoreLabel->SetVisibility(bVisibility ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}

	if (IsValid(OpponentScoreLabel))
	{
		OpponentScoreLabel->SetVisibility(bVisibility ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}

void UPongPlayerOverlayWidget::SetMessageVisibility(bool bVisibility)
{
	if (IsValid(MessageLabel))
	{
		MessageLabel->SetVisibility(bVisibility ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}

#undef LOCTEXT_NAMESPACE
