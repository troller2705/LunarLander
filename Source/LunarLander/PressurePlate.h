#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PressurePlate.generated.h"

UCLASS()
class LUNARLANDER_API APressurePlate : public AActor
{
    GENERATED_BODY()

public:
    APressurePlate();

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
        const FHitResult& SweepResult);

    UFUNCTION()
    void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
    // Mesh
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* PlateMesh;

    // Trigger box
    UPROPERTY(VisibleAnywhere)
    class UBoxComponent* TriggerBox;

    // Door reference
    UPROPERTY(EditAnywhere, Category = "Plate")
    AActor* LinkedDoor;

    // If you want multiple actors to open it
    UPROPERTY(EditAnywhere, Category = "Plate")
    int RequiredActors = 1;

private:
    int CurrentActors = 0;
};
