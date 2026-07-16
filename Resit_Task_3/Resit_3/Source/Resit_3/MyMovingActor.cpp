#include "MyMovingActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/EngineTypes.h"

struct FInputActionValue;

// Sets default values
AMyMovingActor::AMyMovingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoReceiveInput = EAutoReceiveInput::Player0;
	AutoPossessPlayer = EAutoReceiveInput::Player0;


	//Activate player controller and input mapping
	if (GetWorld())
	{
		APlayerController* PC = GetWorld()->GetFirstPlayerController();

		if (PC)
		{
			DefaultMappingContext = Cast<UInputMappingContext>(StaticLoadObject(UInputMappingContext::StaticClass(), nullptr, TEXT("/Game/Inputs/ActorMoveContext.ActorMoveContext")));
			MoveForBack = Cast<UInputAction>(StaticLoadObject(UInputAction::StaticClass(), nullptr, TEXT("/Game/Inputs/Move_ForBac.Move_ForBac")));
			MoveLeftRight = Cast<UInputAction>(StaticLoadObject(UInputAction::StaticClass(), nullptr, TEXT("/Game/Inputs/Move_LefRig.Move_LefRig")));

			if (ULocalPlayer* LocalPlayer = PC->GetLocalPlayer())
			{
				if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
				{
					if (DefaultMappingContext)
					{
						Subsystem->AddMappingContext(DefaultMappingContext, 10);
					}
				}
			}

			EnableInput(PC);

		}
	}

	//Create collision and size
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;
	CollisionBox->SetBoxExtent(FVector(50.f, 50.f, 50.f));
	CollisionBox->SetCollisionProfileName(TEXT("Actor"));

	//Set mesh to basic cube
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));

	//Check if cube found
	if (CubeMeshAsset.Succeeded())
	{
		MeshComponent->SetStaticMesh(CubeMeshAsset.Object);
	}


	CollisionBox->SetSimulatePhysics(true);

	//position camera
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
}

//Bind input actions to movement functions
void AMyMovingActor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInput->BindAction(MoveForBack, ETriggerEvent::Triggered, this, &AMyMovingActor::HandleMoveFor);
		EnhancedInput->BindAction(MoveLeftRight, ETriggerEvent::Triggered, this, &AMyMovingActor::HandleMoveStrafe);
	}
}

//Move forward/backward
void AMyMovingActor::HandleMoveFor(const FInputActionValue& Value) 
{
    if (CollisionBox)
    {
		float DeltaX = Value.Get<float>() * MoveSpeed * GetWorld()->GetDeltaSeconds();
		FVector DeltaLocation = FVector(DeltaX, 0.0f, 0.0f);
		AddActorLocalOffset(DeltaLocation, true);
    }
}

//Move left/right
void AMyMovingActor::HandleMoveStrafe(const FInputActionValue& Value)
{
	if (CollisionBox)
	{
		float DeltaY = Value.Get<float>() * MoveSpeed * GetWorld()->GetDeltaSeconds();
		FVector DeltaLocation = FVector(0.0f, DeltaY, 0.0f);
		AddActorLocalOffset(DeltaLocation, true);
	}
}

// Called when the game starts or when spawned
void AMyMovingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyMovingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

