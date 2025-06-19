
#pragma once

#include "CoreMinimal.h"
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

private:
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* SkeletalMesh;
	
};
