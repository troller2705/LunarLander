#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSCharacter.generated.h"

UCLASS()
class LUNARLANDER_API AFPSCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AFPSCharacter();

protected:
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void MoveForward(float Value);
    void MoveRight(float Value);
    void ReturnToLander();

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere)
    TSubclassOf<class ALanderPawn> LanderPawnClass;

private:
    UPROPERTY()
    ALanderPawn* SpawnedLander;
};
