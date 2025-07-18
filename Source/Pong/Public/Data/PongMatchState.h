#pragma once

#include "CoreMinimal.h"
#include "PongMatchState.generated.h"

UENUM(BlueprintType)
enum class EPongMatchState : uint8
{
    WaitingForPlayers   UMETA(DisplayName = "Waiting For Players"),
    WaitingToStart      UMETA(DisplayName = "Waiting To Start"),
    InProgress          UMETA(DisplayName = "In Progress")
};

namespace PongMatchState
{
    static FORCEINLINE FString ToString(EPongMatchState State)
    {
        return IsValid(StaticEnum<EPongMatchState>()) 
            ? StaticEnum<EPongMatchState>()->GetNameStringByValue(static_cast<int64>(State)) 
            : FString();
    }
}