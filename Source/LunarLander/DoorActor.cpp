#include "DoorActor.h"
#include "Components/StaticMeshComponent.h"

ADoorActor::ADoorActor()
{
    PrimaryActorTick.bCanEverTick = true;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;

    LeftDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftDoor"));
    LeftDoor->SetupAttachment(Root);

    RightDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightDoor"));
    RightDoor->SetupAttachment(Root);
}

void ADoorActor::BeginPlay()
{
    Super::BeginPlay();

    // Record closed rotations
    LeftClosedRot = LeftDoor->GetRelativeRotation();
    RightClosedRot = RightDoor->GetRelativeRotation();

    // Define open rotations (adjust as needed)
    LeftOpenRot = LeftClosedRot + FRotator(0.f, -90.f, 0.f);
    RightOpenRot = RightClosedRot + FRotator(0.f, 90.f, 0.f);
}

void ADoorActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Update CurrentAlpha towards target
    float TargetAlpha = bTargetOpen ? 1.f : 0.f;
    CurrentAlpha = FMath::FInterpTo(CurrentAlpha, TargetAlpha, DeltaTime, DoorSpeed);

    // Apply smooth lerp
    FRotator NewLeftRot = FMath::Lerp(LeftClosedRot, LeftOpenRot, CurrentAlpha);
    FRotator NewRightRot = FMath::Lerp(RightClosedRot, RightOpenRot, CurrentAlpha);

    LeftDoor->SetRelativeRotation(NewLeftRot);
    RightDoor->SetRelativeRotation(NewRightRot);
}

void ADoorActor::OpenDoor()
{
    bTargetOpen = true;
}

void ADoorActor::CloseDoor()
{
    bTargetOpen = false;
}
