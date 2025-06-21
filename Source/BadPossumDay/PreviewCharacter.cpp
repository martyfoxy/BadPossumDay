

#include "PreviewCharacter.h"

APreviewCharacter::APreviewCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	BodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(RootComponent);

	EyesMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("EyesMesh"));
	EyesMesh->SetupAttachment(BodyMesh);
}

void APreviewCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetupMorphs();
}

void APreviewCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APreviewCharacter::SetupMorphs()
{
	if (BodyMesh && BodyMesh->GetSkinnedAsset())
	{
		const TArray<UMorphTarget*>& MorphTargets = BodyMesh->GetSkinnedAsset()->GetMorphTargets();

		CustomizationData.MorphTargets.Reset();
		
		for (UMorphTarget* MorphTarget : MorphTargets)
		{
			FString MorphName = MorphTarget->GetName();
			float Value = BodyMesh->GetMorphTarget(FName(MorphName));
			
			CustomizationData.MorphTargets.Add(FMorphTargetData(MorphName, Value));
		}
	}
}

void APreviewCharacter::SetMorph(FString MorphName, float Value)
{
	if (BodyMesh && BodyMesh->GetSkinnedAsset())
	{
		BodyMesh->SetMorphTarget(FName(MorphName), Value);
		
		for (FMorphTargetData MorphTarget : CustomizationData.MorphTargets)
		{
			if (MorphTarget.MorphName == MorphName)
			{
				MorphTarget.Value = Value;
			}
		}
	}
}
