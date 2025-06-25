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
	
	CursorWidget = CreateWidget<UUserWidget>(this, MyCursorWidgetClass);
	if (CursorWidget)
	{
		CursorWidget->AddToViewport(9999);
		CursorWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}

void APreviewPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector2D MousePos;
	if (GetMousePosition(MousePos.X, MousePos.Y))
	{
		float Scale = UWidgetLayoutLibrary::GetViewportScale(this);
		FVector2D UiPos = MousePos / Scale;
		CursorWidget->SetPositionInViewport(UiPos, false);
	}
}
