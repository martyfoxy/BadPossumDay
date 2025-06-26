#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PreviewPawn.generated.h"

class APreviewCharacter;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class BADPOSSUMDAY_API APreviewPawn : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	APreviewCharacter* PreviewCharacter;

	UPROPERTY(BlueprintReadOnly)
	TSubclassOf<UUserWidget> EditorWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APreviewCharacter> PreviewCharacterClass;
	
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(EditDefaultsOnly, Category = "Sensitivity")
	float TurnSensitivity = 3.f;

	UPROPERTY(EditDefaultsOnly, Category = "Sensitivity")
	float ZoomSensitivity = 5.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Spring Arm Defaults")
	float DefaultSpringArmLength = 150.f;

	UPROPERTY(EditDefaultsOnly, Category = "Spring Arm Defaults")
	float MinSpringArmLength = 40.f;

	UPROPERTY(EditDefaultsOnly, Category = "Spring Arm Defaults")
	float ActivationSpringArmLength = 120.f;

	UPROPERTY(EditDefaultsOnly, Category = "Spring Arm Defaults")
	float MaxSpringArmLength = 250.f;

	UPROPERTY(EditDefaultsOnly, Category = "Spring Arm Defaults")
	FVector DefaultTargetOffset = FVector(0.f, 40.f, 0.f);

	UPROPERTY(EditDefaultsOnly, Category = "Target Values")
	float DefaultYOffset = 35.f;

	UPROPERTY(EditDefaultsOnly, Category = "Target Values")
	float FocusedYOffset = 10.f;

	UPROPERTY(EditDefaultsOnly, Category = "Target Values")
	float DefaultZOffset = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "Target Values")
	float FocusedZOffset = 30.f;

	UPROPERTY(EditDefaultsOnly, Category = "Target Values")
	float FocusedYawPitch = 8.f;

private:
	bool bRotatingCharacter = false;
	
public:
	APreviewPawn();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
private:
	float TargetSpringArmLength = 0.f;
	float TargetPitch = 0.f;
	float TargetYaw = 0.f;
	float TargetYOffset = 0.f;
	float TargetZOffset = 0.f;
	
	void CreateEditorWidget() const;
	void SpawnPreviewCharacter();
	void TurnCharacter(float value);
	void OnMouseClicked();
	void OnMouseReleased();
	void Zoom(float value);
};
