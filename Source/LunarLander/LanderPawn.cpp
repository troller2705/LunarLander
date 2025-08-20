#include "LanderPawn.h"
#include "Components/StaticMeshComponent.h"
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
}

void ALanderPawn::BeginPlay()
{
    Super::BeginPlay();
}

void ALanderPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Compute altitude & velocity
    float Altitude = GetActorLocation().Z;
    float Velocity = GetVelocity().Size();

    if (Velocity != 0)
    {
        // Example: fuel drains
        Fuel -= DeltaTime * 0.5f;
    }

    // Push updates to HUD
    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        if (ASharedHUD* HUD = Cast<ASharedHUD>(PC->GetHUD()))
        {
            HUD->UpdateFuel(Fuel);
            HUD->UpdateAltitude(Altitude);
            HUD->UpdateVelocity(Velocity);
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
    }
}

void ALanderPawn::Move(const FInputActionValue& Value)
{
    // input is a Vector2D
    FVector2D MovementVector = Value.Get<FVector2D>();

    if (Controller != nullptr && Fuel > 0)
    {
        // add movement 
        if (MovementVector.Y != 0.f)
            LanderMesh->AddForce(GetActorForwardVector() * MovementVector.Y * 50000.f);
        if (MovementVector.X != 0.f)
            LanderMesh->AddForce(GetActorRightVector() * MovementVector.X * 50000.f);
    }
}

void ALanderPawn::ExitLander()
{
    if (FPSCharacterClass)
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;

        FVector SpawnLocation = GetActorLocation() + FVector(100.f, 0.f, 0.f);
        FRotator SpawnRotation = GetActorRotation();

        SpawnedFPSCharacter = GetWorld()->SpawnActor<AFPSCharacter>(FPSCharacterClass, SpawnLocation, SpawnRotation, SpawnParams);
        if (SpawnedFPSCharacter)
        {
            AController* PlayerController = Cast<AController>(GetController());
            if (PlayerController)
            {
                PlayerController->Possess(SpawnedFPSCharacter);
                // HUD access requires cast to APlayerController
                if (APlayerController* PC = Cast<APlayerController>(Controller))
                {
                    if (ASharedHUD* HUD = Cast<ASharedHUD>(PC->GetHUD()))
                    {
                        HUD->SetPlayerMode(false); // switch to FPS UI
                    }
                }
                Destroy();
            }
        }
    }
}
