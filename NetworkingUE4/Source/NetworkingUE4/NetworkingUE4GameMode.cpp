// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "NetworkingUE4GameMode.h"
#include "NetworkingUE4Character.h"
#include "UObject/ConstructorHelpers.h"

ANetworkingUE4GameMode::ANetworkingUE4GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
