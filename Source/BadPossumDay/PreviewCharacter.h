
#pragma once

#include "CoreMinimal.h"
#include "Data/FCharacterCustomizationData.h"
#include "GameFramework/Actor.h"
#include "PreviewCharacter.generated.h"

class UBoxComponent;

UCLASS()
class BADPOSSUMDAY_API APreviewCharacter : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* BodyMesh;

	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere)
	UAnimMontage* IdleAnimMontage;

	UPROPERTY(EditAnywhere)
	FCharacterCustomizationData CustomizationData;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* HeadFocus;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* BodyFocus;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* PawsFocus;

	
public:	
	APreviewCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable)
	TArray<FMorphTargetData> GetMorphTargets() const { return CustomizationData.MorphTargets; }

	UFUNCTION(BlueprintCallable)
	void SetMorph(FString MorphName, float Value);
	
private:
	void SetupMorphs();
};
