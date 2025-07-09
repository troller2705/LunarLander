// Copyright Epic Games, Inc. All Rights Reserved.

#include "LunarLanderGameMode.h"
#include "LunarLanderCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALunarLanderGameMode::ALunarLanderGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
