#include "GravityGunComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"

UGravityGunComponent::UGravityGunComponent()
{
    PrimaryComponentTick.bCanEverTick = true; // enable ticking for object holding
}

void UGravityGunComponent::BeginPlay()
{
    Super::BeginPlay();

    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    PlayerCamera = GetOwner()->FindComponentByClass<UCameraComponent>();
}

void UGravityGunComponent::Grab()
{
    if (!PhysicsHandle || !PlayerCamera) return;

    FHitResult Hit;
    FVector Start = PlayerCamera->GetComponentLocation();
    FVector End = GetLineTraceEnd();

    FCollisionQueryParams Params;
    Params.AddIgnoredActor(GetOwner());

    if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_PhysicsBody, Params))
    {
        if (Hit.GetComponent()->IsSimulatingPhysics())
        {
            PhysicsHandle->GrabComponentAtLocation(Hit.GetComponent(), NAME_None, Hit.Location);
        }
    }
}

void UGravityGunComponent::Release()
{
    if (PhysicsHandle && PhysicsHandle->GrabbedComponent)
    {
        PhysicsHandle->ReleaseComponent();
    }
}

void UGravityGunComponent::Launch()
{
    if (PhysicsHandle && PhysicsHandle->GrabbedComponent)
    {
        FVector LaunchDirection = PlayerCamera->GetForwardVector();
        PhysicsHandle->GetGrabbedComponent()->AddImpulse(LaunchDirection * LaunchForce, NAME_None, true);
        PhysicsHandle->ReleaseComponent();
    }
}

void UGravityGunComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (PhysicsHandle && PhysicsHandle->GrabbedComponent && PlayerCamera)
    {
        // Keep held object floating in front of the player
        FVector TargetLocation = PlayerCamera->GetComponentLocation() + PlayerCamera->GetForwardVector() * HoldDistance;
        PhysicsHandle->SetTargetLocation(TargetLocation);
    }
}

FVector UGravityGunComponent::GetLineTraceEnd() const
{
    return PlayerCamera->GetComponentLocation() + PlayerCamera->GetForwardVector() * 500.f;
}
