// Copyright Epic Games, Inc. All Rights Reserved.

#include "LunarLanderGameMode.h"
#include "FPSCharacter.h"
#include "SharedHUD.h"
#include "UObject/ConstructorHelpers.h"

ALunarLanderGameMode::ALunarLanderGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	HUDClass = ASharedHUD::StaticClass();


}
