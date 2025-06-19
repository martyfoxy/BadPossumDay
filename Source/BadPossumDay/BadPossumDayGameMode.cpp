// Copyright Epic Games, Inc. All Rights Reserved.

#include "BadPossumDayGameMode.h"
#include "BadPossumDayCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABadPossumDayGameMode::ABadPossumDayGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> EditorPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_EditorPawn"));
	if (EditorPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = EditorPawnBPClass.Class;
	}
}
