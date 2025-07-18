#include "Actors/PongSetup.h"

APongSetup::APongSetup()
{
	PrimaryActorTick.bCanEverTick = false;
}

FPongPlayerSide APongSetup::GetFreePlayerSide()
{
	return PlayerSides.Num() > 0 ? PlayerSides.Pop() : FPongPlayerSide();
}
