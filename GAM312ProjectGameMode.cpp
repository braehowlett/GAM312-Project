// Copyright Epic Games, Inc. All Rights Reserved.

#include "GAM312ProjectGameMode.h"
#include "GAM312ProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGAM312ProjectGameMode::AGAM312ProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
