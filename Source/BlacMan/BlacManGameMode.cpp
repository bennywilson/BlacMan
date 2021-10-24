// Copyright Epic Games, Inc. All Rights Reserved.

#include "BlacManGameMode.h"
#include "BlacManPlayerController.h"
#include "BlacManCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABlacManGameMode::ABlacManGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ABlacManPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}