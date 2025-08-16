#include "FPSCharacter.h"
#include "GameFramework/PlayerController.h"
#include "LanderPawn.h"
#include "Kismet/GameplayStatics.h"

AFPSCharacter::AFPSCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    //GravityGun = CreateDefaultSubobject<UGravityGunComponent>(TEXT("GravityGunComponent"));
}

void AFPSCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void AFPSCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);
    PlayerInputComponent->BindAction("ExitLander", IE_Pressed, this, &AFPSCharacter::ReturnToLander);

    /*PlayerInputComponent->BindAction("Grab", IE_Pressed, GravityGun, &UGravityGunComponent::Grab);
    PlayerInputComponent->BindAction("Grab", IE_Released, GravityGun, &UGravityGunComponent::Release);
    PlayerInputComponent->BindAction("Launch", IE_Pressed, GravityGun, &UGravityGunComponent::Launch);*/
}

void AFPSCharacter::MoveForward(float Value)
{
    if (Value != 0.f)
        AddMovementInput(GetActorForwardVector(), Value);
}

void AFPSCharacter::MoveRight(float Value)
{
    if (Value != 0.f)
        AddMovementInput(GetActorRightVector(), Value);
}

void AFPSCharacter::ReturnToLander()
{
    if (LanderPawnClass)
    {
        APlayerController* PlayerController = Cast<APlayerController>(GetController());
        if (PlayerController)
        {
            FVector SpawnLocation = GetActorLocation() + FVector(100.f, 0.f, 0.f);
            FRotator SpawnRotation = GetActorRotation();

            ALanderPawn* Lander = GetWorld()->SpawnActor<ALanderPawn>(LanderPawnClass, SpawnLocation, SpawnRotation);
            if (Lander)
            {
                PlayerController->Possess(Lander);
                Destroy(); // Remove the FPS character after switching
            }
        }
    }
}
