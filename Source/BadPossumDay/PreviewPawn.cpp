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
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComponent);

	static ConstructorHelpers::FClassFinder<APreviewCharacter> BpClass(TEXT("/Game/Characters/Meow/BP_PreviewCharacter"));
	if (BpClass.Succeeded())
	{
		PreviewCharacterClass = BpClass.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> EditorWidget(TEXT("/Game/UI/WB_CharacterEditor"));
	if(EditorWidget.Succeeded())
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
}

void APreviewPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APreviewPawn::SpawnPreviewCharacter()
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector SpawnLocation = FVector(-380.f,-80.f,20.f);
	FRotator SpawnRotation = FRotator(0.f,-90.f,0.f);

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
