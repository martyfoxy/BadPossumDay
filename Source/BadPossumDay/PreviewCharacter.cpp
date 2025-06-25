

#include "PreviewCharacter.h"

#include "Components/BoxComponent.h"

APreviewCharacter::APreviewCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	BodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(RootComponent);

	EyesMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("EyesMesh"));
	EyesMesh->SetupAttachment(BodyMesh);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(RootComponent);
	BoxComponent->SetRelativeLocation(FVector(0.f,0.f,90.f));
	BoxComponent->SetRelativeScale3D(FVector(1.25f, 1.f, 3.f));
	BoxComponent->SetCollisionProfileName(FName("BlockAll"));

	HeadFocus = CreateDefaultSubobject<USceneComponent>(TEXT("HeadFocus"));
	HeadFocus->SetupAttachment(BodyMesh);
	HeadFocus->SetRelativeLocation(FVector(0.f,0.f,150.f));

	BodyFocus = CreateDefaultSubobject<USceneComponent>(TEXT("BodyFocus"));
	BodyFocus->SetupAttachment(BodyMesh);
	BodyFocus->SetRelativeLocation(FVector(0.f,0.f,100.f));

	PawsFocus = CreateDefaultSubobject<USceneComponent>(TEXT("PawsFocus"));
	PawsFocus->SetupAttachment(BodyMesh);
	PawsFocus->SetRelativeLocation(FVector(0.f,0.f,50.f));
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
