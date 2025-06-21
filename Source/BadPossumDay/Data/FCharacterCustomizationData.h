#pragma once

#include "CoreMinimal.h"
#include "FMorphTargetData.h"
#include "FCharacterCustomizationData.generated.h"

struct FMorphTargetData;

USTRUCT(BlueprintType)
struct FCharacterCustomizationData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FMorphTargetData> MorphTargets;
};
