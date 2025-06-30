#include "PreviewPawn.h"

#include "PreviewCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

APreviewPawn::APreviewPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmComponent->TargetArmLength = DefaultSpringArmLength;
	SpringArmComponent->TargetOffset.Y = DefaultYOffset;
	SpringArmComponent->TargetOffset.Z = DefaultZOffset;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComponent);

	static ConstructorHelpers::FClassFinder<APreviewCharacter> PreviewCharacterBp(TEXT("/Game/Characters/Meow/BP_PreviewCharacter"));
	if (PreviewCharacterBp.Succeeded())
	{
		PreviewCharacterClass = PreviewCharacterBp.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> EditorWidget(TEXT("/Game/UI/WB_CharacterEditor"));
	if (EditorWidget.Succeeded())
	{
		EditorWidgetClass = EditorWidget.Class;
	}
}

void APreviewPawn::BeginPlay()
{
	Super::BeginPlay();

	SpawnPreviewCharacter();
	CreateEditorWidget();
}

void APreviewPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (SpringArmComponent)
	{
		float CurrentLength = SpringArmComponent->TargetArmLength;
		SpringArmComponent->TargetArmLength = FMath::FInterpTo(CurrentLength, TargetSpringArmLength, DeltaTime, 15.f);
	}
	
	if (SpringArmComponent)
	{
		FVector CurrentOffset = SpringArmComponent->TargetOffset;
		SpringArmComponent->TargetOffset.Y = FMath::FInterpTo(CurrentOffset.Y, TargetYOffset, DeltaTime, 15.f);
		SpringArmComponent->TargetOffset.Z = FMath::FInterpTo(CurrentOffset.Z, TargetZOffset, DeltaTime, 15.f);

		FRotator CurrentRotation = SpringArmComponent->GetRelativeRotation();
		SpringArmComponent->SetRelativeRotation(FRotator(
			FMath::FInterpTo(CurrentRotation.Pitch, TargetPitch, DeltaTime, 15.f), 
			FMath::FInterpTo(CurrentRotation.Yaw, TargetYaw, DeltaTime, 15.f),
			0.f));
	}
}

void APreviewPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MouseX", this, &APreviewPawn::TurnCharacter);
	PlayerInputComponent->BindAction("LeftMouseButton", IE_Pressed, this, &APreviewPawn::OnMouseClicked);
	PlayerInputComponent->BindAction("LeftMouseButton", IE_Released, this, &APreviewPawn::OnMouseReleased);
	PlayerInputComponent->BindAxis("MouseWheel", this, &APreviewPawn::Zoom);
}

void APreviewPawn::SpawnPreviewCharacter()
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector SpawnLocation = FVector(-380.f, -80.f, 20.f);
	FRotator SpawnRotation = FRotator(0.f, -90.f, 0.f);

	if (PreviewCharacterClass)
	{
		PreviewCharacter = GetWorld()->SpawnActor<APreviewCharacter>(
			PreviewCharacterClass,
			SpawnLocation,
			SpawnRotation,
			SpawnParameters);
	}
}

void APreviewPawn::CreateEditorWidget() const
{
	if (EditorWidgetClass)
	{
		UUserWidget* Widget = CreateWidget<UUserWidget>(GetController<APlayerController>(), EditorWidgetClass);
		if (Widget)
		{
			Widget->AddToViewport();

			UFunction* InitFunc = Widget->FindFunction(FName("Initialize"));
			if (InitFunc)
			{
				struct FInitParams
				{
					APreviewCharacter* PreviewCharacter;
				};

				FInitParams Params;
				Params.PreviewCharacter = PreviewCharacter;

				Widget->ProcessEvent(InitFunc, &Params);
			}
		}
	}
}

void APreviewPawn::TurnCharacter(float value)
{
	 if (bRotatingCharacter && PreviewCharacter)
	 {
	 	FRotator PreviousRotator = PreviewCharacter->GetActorRotation();
	 	PreviousRotator.Yaw -= value * TurnSensitivity;
	 	PreviewCharacter->SetActorRotation(PreviousRotator);
	}
}

void APreviewPawn::OnMouseClicked()
{
	FHitResult Hit;
	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	bool HasHit = PC->GetHitResultUnderCursor(ECC_PhysicsBody, false, Hit);

	if (HasHit)
	{
		FString ActorName = GetNameSafe(Hit.GetActor());

		if (Hit.GetActor() == PreviewCharacter)
		{
			bRotatingCharacter = true;
			return;
		}
	}

	bRotatingCharacter = false;
}

void APreviewPawn::OnMouseReleased()
{
	bRotatingCharacter = false;
}

void APreviewPawn::Zoom(float value)
{
	if (bRotatingCharacter)
		return;
	
	if (SpringArmComponent)
	{
		TargetSpringArmLength = SpringArmComponent->TargetArmLength - value * ZoomSensitivity;
		TargetSpringArmLength = FMath::Clamp(TargetSpringArmLength, MinSpringArmLength, MaxSpringArmLength);
		
		if (TargetSpringArmLength <= ActivationSpringArmLength)
		{
			TargetPitch = FMath::Lerp(FocusedYawPitch, 0.f, (TargetSpringArmLength-MinSpringArmLength)/(ActivationSpringArmLength-MinSpringArmLength));
			TargetYaw = FMath::Lerp(FocusedYawPitch, 0.f, (TargetSpringArmLength-MinSpringArmLength)/(ActivationSpringArmLength-MinSpringArmLength));

			TargetYOffset = FMath::Lerp(FocusedYOffset, DefaultYOffset, (TargetSpringArmLength-MinSpringArmLength)/(ActivationSpringArmLength-MinSpringArmLength));
			TargetZOffset = FMath::Lerp(FocusedZOffset, DefaultZOffset, (TargetSpringArmLength-MinSpringArmLength)/(ActivationSpringArmLength-MinSpringArmLength));
		}		
	}
}