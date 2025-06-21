// Fill out your copyright notice in the Description page of Project Settings.


#include "PreviewGameMode.h"

#include "PreviewPawn.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

APreviewGameMode::APreviewGameMode()
{
	static ConstructorHelpers::FClassFinder<APreviewPawn> BPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_PreviewPawn"));
	if (BPClass.Succeeded())
	{
		DefaultPawnClass = BPClass.Class;
	}
}

void APreviewGameMode::BeginPlay()
{
	Super::BeginPlay();
}
