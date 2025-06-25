#include "PreviewGameMode.h"

#include "PreviewPawn.h"
#include "PreviewPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

APreviewGameMode::APreviewGameMode()
{
	static ConstructorHelpers::FClassFinder<APreviewPawn> BPPreviewPawn(TEXT("/Game/ThirdPerson/Blueprints/BP_PreviewPawn"));
	if (BPPreviewPawn.Succeeded())
	{
		DefaultPawnClass = BPPreviewPawn.Class;
	}

	static ConstructorHelpers::FClassFinder<APreviewPlayerController> BPPreviewPlayerController(TEXT("/Game/Characters/BP_PreviewPlayerController"));
	if (BPPreviewPlayerController.Succeeded())
	{
		PlayerControllerClass = BPPreviewPlayerController.Class;
	}
}

void APreviewGameMode::BeginPlay()
{
	Super::BeginPlay();

	
}
