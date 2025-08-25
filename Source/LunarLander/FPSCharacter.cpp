#include "FPSCharacter.h"
#include "GameFramework/PlayerController.h"
#include "LanderPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "SharedHUD.h"

AFPSCharacter::AFPSCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    GravityGun = CreateDefaultSubobject<UGravityGunComponent>(TEXT("GravityGunComponent"));

    CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandleComponent"));

    // Set size for collision capsule
    GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

    // Create a CameraComponent	
    FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
    FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
    FirstPersonCameraComponent->bUsePawnControlRotation = true;

    // Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
    Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
    Mesh1P->SetOnlyOwnerSee(true);
    Mesh1P->SetupAttachment(FirstPersonCameraComponent);
    Mesh1P->bCastDynamicShadow = false;
    Mesh1P->CastShadow = false;
    //Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
    Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
}

void AFPSCharacter::BeginPlay()
{
    Super::BeginPlay();

    APlayerController* PlayerController = Cast<APlayerController>(GetController());
    if (PlayerController) {
        if (ASharedHUD* HUD = Cast<ASharedHUD>(PlayerController->GetHUD()))
        {
            HUD->SetPlayerMode(false);
        }
    }
}

void AFPSCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    // Set up action bindings
    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        // Jumping
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

        // Moving
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFPSCharacter::Move);

        // Looking
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFPSCharacter::Look);

        //Lander Swapping
        EnhancedInputComponent->BindAction(ExitLanderAction, ETriggerEvent::Completed, this, &AFPSCharacter::ReturnToLander);

        // Gravity Gun
        EnhancedInputComponent->BindAction(GrabAction, ETriggerEvent::Started, GravityGun, &UGravityGunComponent::Grab);
        EnhancedInputComponent->BindAction(ReleaseAction, ETriggerEvent::Completed, GravityGun, &UGravityGunComponent::Release);
        EnhancedInputComponent->BindAction(LaunchAction, ETriggerEvent::Completed, GravityGun, &UGravityGunComponent::Launch);
    }
}

void AFPSCharacter::Move(const FInputActionValue& Value)
{
    // input is a Vector2D
    FVector2D MovementVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        // add movement 
        AddMovementInput(GetActorForwardVector(), MovementVector.Y);
        AddMovementInput(GetActorRightVector(), MovementVector.X);
    }
}

void AFPSCharacter::Look(const FInputActionValue& Value)
{
    // input is a Vector2D
    FVector2D LookAxisVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        // add yaw and pitch input to controller
        AddControllerYawInput(LookAxisVector.X);
        AddControllerPitchInput(LookAxisVector.Y);
    }
}

void AFPSCharacter::ReturnToLander()
{
    //UE_LOG(LogTemp, Warning, TEXT("Returning to Lander"))
    if (LanderPawnClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("Lander Class Found"))
        APlayerController* PlayerController = Cast<APlayerController>(GetController());
        if (PlayerController)
        {
            UE_LOG(LogTemp, Warning, TEXT("Player Controller Obtained"))
            FVector SpawnLocation = GetActorLocation() + FVector(100.f, 0.f, 0.f);
            FRotator SpawnRotation = GetActorRotation();

            FActorSpawnParameters SpawnParams;
            SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;


            ALanderPawn* Lander = GetWorld()->SpawnActor<ALanderPawn>(LanderPawnClass, SpawnLocation, SpawnRotation, SpawnParams);
            if (Lander)
            {
                UE_LOG(LogTemp, Warning, TEXT("Returning to Lander"))
                PlayerController->Possess(Lander);
                if (ASharedHUD* HUD = Cast<ASharedHUD>(PlayerController->GetHUD()))
                {
                    HUD->SetPlayerMode(true);
                }
                Destroy(); // Remove the FPS character after switching
            }
        }
    }
}
