#include "PreviewPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"

APreviewPlayerController::APreviewPlayerController()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> MyCursorWidget(TEXT("/Game/UI/WBP_Cursor"));

	if (MyCursorWidget.Succeeded())
	{
		MyCursorWidgetClass = MyCursorWidget.Class;
	}
}

void APreviewPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;

	SetMouseCursorWidget(EMouseCursor::Default, CreateWidget<UUserWidget>(this, MyCursorWidgetClass));
}

void APreviewPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
