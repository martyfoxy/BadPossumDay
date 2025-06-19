

#include "PreviewCharacter.h"

APreviewCharacter::APreviewCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(RootComponent);
}

void APreviewCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void APreviewCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

