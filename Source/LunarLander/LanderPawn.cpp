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
    PlayerInputComponent->BindAxis("MoveForward", this, &ALanderPawn::ThrustForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ALanderPawn::ThrustRight);
    PlayerInputComponent->BindAction("ExitLander", IE_Pressed, this, &ALanderPawn::ExitLander);
}

void ALanderPawn::ThrustForward(float Value)
{
    if (Value != 0.f)
        LanderMesh->AddForce(GetActorForwardVector() * Value * 50000.f);
}

void ALanderPawn::ThrustRight(float Value)
{
    if (Value != 0.f)
        LanderMesh->AddForce(GetActorRightVector() * Value * 50000.f);
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
