#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Camera/CameraComponent.h"
#include "GravityGunComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LUNARLANDER_API UGravityGunComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UGravityGunComponent();

protected:
    virtual void BeginPlay() override;

    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
    void Grab();
    void Release();
    void Launch();

private:
    UPROPERTY()
    UPhysicsHandleComponent* PhysicsHandle;

    UPROPERTY()
    UCameraComponent* PlayerCamera;

    // Tunable values exposed to editor
    UPROPERTY(EditAnywhere, Category = "Gravity Gun")
    float HoldDistance = 300.f;

    UPROPERTY(EditAnywhere, Category = "Gravity Gun")
    float LaunchForce = 2000.f;

    FVector GetLineTraceEnd() const;
};
