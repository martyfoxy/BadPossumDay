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
	APreviewPawn();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(BlueprintReadOnly)
	APreviewCharacter* PreviewCharacter;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> EditorWidgetClass;
	
private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APreviewCharacter> PreviewCharacterClass;
	
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComp;

	void CreateEditorWidget() const;
	void SpawnPreviewCharacter();
};
