#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "LunarLanderCharacter.h"
#include "LanderPawn.generated.h"

UCLASS()
class LUNARLANDER_API ALanderPawn : public APawn
{
    GENERATED_BODY()

    public:
        ALanderPawn();

    protected:
        virtual void BeginPlay() override;
        virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

        void ThrustForward(float Value);
        void ThrustRight(float Value);
        //void ExitLander();

    public:
        virtual void Tick(float DeltaTime) override;

        UPROPERTY(VisibleAnywhere)
        class UStaticMeshComponent* LanderMesh;

        UPROPERTY(EditAnywhere)
        TSubclassOf<class AFPSCharacter> FPSCharacterClass;

    private:
        UPROPERTY()
        AFPSCharacter* SpawnedFPSCharacter;
};
