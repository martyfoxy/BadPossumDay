
#pragma once

#include "CoreMinimal.h"
#include "Data/FCharacterCustomizationData.h"
#include "GameFramework/Actor.h"
#include "PreviewCharacter.generated.h"

UCLASS()
class BADPOSSUMDAY_API APreviewCharacter : public AActor
{
	GENERATED_BODY()
	
public:	
	APreviewCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	void SetupMorphs();

	UFUNCTION(BlueprintCallable)
	TArray<FMorphTargetData> GetMorphTargets() const { return CustomizationData.MorphTargets; }

	UFUNCTION(BlueprintCallable)
	void SetMorph(FString MorphName, float Value);

private:
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* BodyMesh;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* EyesMesh;

	UPROPERTY(EditAnywhere)
	FCharacterCustomizationData CustomizationData;
};
