#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PreviewGameMode.generated.h"

UCLASS()
class BADPOSSUMDAY_API APreviewGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APreviewGameMode();

protected:
	virtual void BeginPlay() override;
};
