#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PreviewPlayerController.generated.h"

UCLASS()
class BADPOSSUMDAY_API APreviewPlayerController : public APlayerController
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> MyCursorWidgetClass;
	
public:
	APreviewPlayerController();
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	UUserWidget* CursorWidget;
};
