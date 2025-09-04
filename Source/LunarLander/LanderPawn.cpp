#include "LanderPawn.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsThrusterComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "FPSCharacter.h"
#include "SharedHUD.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"

ALanderPawn::ALanderPawn()
{
    PrimaryActorTick.bCanEverTick = true;

    LanderMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LanderMesh"));
    RootComponent = LanderMesh;
    LanderMesh->SetSimulatePhysics(true);
    LanderMesh->SetEnableGravity(true);
    LanderMesh->SetLinearDamping(0.1f);   // Tweak for stability
    LanderMesh->SetAngularDamping(0.5f);  // Prevent endless spinning

    // Main thruster (bottom of lander)
    MainThruster = CreateDefaultSubobject<UPhysicsThrusterComponent>(TEXT("MainThruster"));
    MainThruster->SetupAttachment(LanderMesh);
    MainThruster->ThrustStrength = MainThrustBase; // tweak depending on mesh mass
    MainThruster->bAutoActivate = false;

    // Rotate Left Thruster
    RotateLeftThruster = CreateDefaultSubobject<UPhysicsThrusterComponent>(TEXT("RotateLeftThruster"));
    RotateLeftThruster->SetupAttachment(RootComponent);
    RotateLeftThruster->ThrustStrength = RotThrustBase; // adjust for control feel
    RotateLeftThruster->bAutoActivate = false;

    // Rotate Right Thruster
    RotateRightThruster = CreateDefaultSubobject<UPhysicsThrusterComponent>(TEXT("RotateRightThruster"));
    RotateRightThruster->SetupAttachment(RootComponent);
    RotateRightThruster->ThrustStrength = RotThrustBase;
    RotateRightThruster->bAutoActivate = false;

}

void ALanderPawn::BeginPlay()
{
    Super::BeginPlay();

    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        if (ASharedHUD* HUD = Cast<ASharedHUD>(PC->GetHUD()))
        {
            HUD->SetPlayerMode(true);
        }
    }
}

void ALanderPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Compute altitude & velocity
    float Altitude = GetActorLocation().Z - 100;
    float Velocity = GetVelocity().Size();

    if (isGameover) return;

    // Push updates to HUD
    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        if (ASharedHUD* HUD = Cast<ASharedHUD>(PC->GetHUD()))
        {
            HUD->UpdateFuel(Fuel);
            HUD->UpdateAltitude(Altitude);
            HUD->UpdateVelocity(Velocity);
            if (Fuel <= 0 || Altitude > 5000)
            {
                isGameover = true;
                HUD->OnGameover();
            }
        }
    }
}

void ALanderPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    // Set up action bindings
    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        // Moving
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ALanderPawn::Move);
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ALanderPawn::Move);

        //Lander Swapping
        EnhancedInputComponent->BindAction(ExitLanderAction, ETriggerEvent::Completed, this, &ALanderPawn::ExitLander);
    }
}

void ALanderPawn::Move(const FInputActionValue& Value)
{
    // input is a Vector2D
    FVector2D MovementVector = Value.Get<FVector2D>();

    if (Controller && Fuel > 0)
    {
        // Fire main thruster
        if (MovementVector.Y > 0.f)
        {
            // Scale thrust by input (hold for analog; keyboard = 1)
            MainThruster->ThrustStrength = MainThrustBase * MovementVector.Y;
            if (!MainThruster->IsActive()) MainThruster->Activate(true);

            Fuel -= GetWorld()->GetDeltaSeconds() * (0.5f * MovementVector.Y);
        }
        else
        {
            //UE_LOG(LogTemp, Warning, TEXT("Thrust Cut"))
            MainThruster->Deactivate();
        }

        if (MovementVector.X > 0.f)
        {
            RotateLeftThruster->ThrustStrength = RotThrustBase * MovementVector.X; // scale if analog
            if (!RotateLeftThruster->IsActive()) RotateLeftThruster->Activate(true);
            RotateRightThruster->Deactivate();

            Fuel -= GetWorld()->GetDeltaSeconds() * (0.25f * MovementVector.X);
        }
        else if (MovementVector.X < 0.f)
        {
            RotateRightThruster->ThrustStrength = RotThrustBase * (-MovementVector.X);
            if (!RotateRightThruster->IsActive()) RotateRightThruster->Activate(true);
            RotateLeftThruster->Deactivate();

            Fuel -= GetWorld()->GetDeltaSeconds() * (0.25f * -MovementVector.X);
        }
        else
        {
            //UE_LOG(LogTemp, Warning, TEXT("Thrust Cut"))
            RotateLeftThruster->Deactivate();
            RotateRightThruster->Deactivate();
        }
    }
    else
    {
        // No fuel -> all thrusters off
        MainThruster->SetActive(false);
        RotateLeftThruster->SetActive(false);
        RotateRightThruster->SetActive(false);
    }
}

void ALanderPawn::ExitLander()
{
    if (FPSCharacterClass)
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

        FVector SpawnLocation = GetActorLocation() + FVector(100.f, 0.f, 0.f);
        FRotator SpawnRotation = GetActorRotation();

        SpawnedFPSCharacter = GetWorld()->SpawnActor<AFPSCharacter>(FPSCharacterClass, SpawnLocation, SpawnRotation, SpawnParams);
        if (SpawnedFPSCharacter)
        {
            AController* PlayerController = Cast<AController>(GetController());
            if (PlayerController)
            {
                // HUD access requires cast to APlayerController
                if (APlayerController* PC = Cast<APlayerController>(GetController()))
                {
                    if (ASharedHUD* HUD = Cast<ASharedHUD>(PC->GetHUD()))
                    {
                        HUD->SetPlayerMode(false); // switch to FPS UI
                    }
                }
                PlayerController->Possess(SpawnedFPSCharacter);
                Destroy();
            }
        }
    }
}
