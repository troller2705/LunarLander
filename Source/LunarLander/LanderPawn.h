#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FPSCharacter.h"
#include "LanderPawn.generated.h"

UCLASS()
class LUNARLANDER_API ALanderPawn : public APawn
{
    GENERATED_BODY()

    /** Move Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* MoveAction;

    /** Move Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* ExitLanderAction;

    public:
        ALanderPawn();

        // Tunable values exposed to editor
        UPROPERTY(EditAnywhere)
        float Fuel = 100.f;

    protected:
        virtual void BeginPlay() override;
        virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

        /** Called for movement input */
        void Move(const FInputActionValue& Value);

        void ExitLander();

    public:
        virtual void Tick(float DeltaTime) override;

        UPROPERTY(VisibleAnywhere)
        class UStaticMeshComponent* LanderMesh;

        UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Thrusters")
        class UPhysicsThrusterComponent* MainThruster;

        // 2.5D Rotation Thrusters
        UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Thrusters")
        UPhysicsThrusterComponent* RotateLeftThruster;

        UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Thrusters")
        UPhysicsThrusterComponent* RotateRightThruster;

        // Base strengths you can tweak in editor
        UPROPERTY(EditAnywhere, Category = "Thrusters")
        float MainThrustBase = 3.0e5f;

        UPROPERTY(EditAnywhere, Category = "Thrusters")
        float RotThrustBase = 3.0e5f;


        UPROPERTY(EditAnywhere)
        TSubclassOf<class AFPSCharacter> FPSCharacterClass;

    private:
        bool isGameover;

        UPROPERTY()
        AFPSCharacter* SpawnedFPSCharacter;
};
