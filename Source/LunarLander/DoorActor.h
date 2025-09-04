#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorActor.generated.h"

UCLASS()
class LUNARLANDER_API ADoorActor : public AActor
{
    GENERATED_BODY()

public:
    ADoorActor();

    UPROPERTY(VisibleAnywhere)
    USceneComponent* Root;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* LeftDoor;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* RightDoor;

    UFUNCTION(BlueprintCallable)
    void OpenDoor();

    UFUNCTION(BlueprintCallable)
    void CloseDoor();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

private:
    UPROPERTY(VisibleAnywhere)
    bool bTargetOpen = false;       // desired state
    float CurrentAlpha = 0.f;       // 0 = closed, 1 = open
    float DoorSpeed = 3.f;         // seconds to fully open/close

    FRotator LeftClosedRot;
    FRotator LeftOpenRot;

    FRotator RightClosedRot;
    FRotator RightOpenRot;
};
