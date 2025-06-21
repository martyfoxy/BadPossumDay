#pragma once

#include "CoreMinimal.h"
#include "FMorphTargetData.generated.h"

USTRUCT(BlueprintType)
struct FMorphTargetData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString MorphName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Value;
};
