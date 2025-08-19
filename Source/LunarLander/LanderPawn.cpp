#include "LanderPawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "FPSCharacter.h"
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

    if (Controller != nullptr)
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
            }
        }
    }
}
