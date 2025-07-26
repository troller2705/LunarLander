#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "LanderPawn.generated.h"

UCLASS()
class LUNARLANDER_API ALanderPawn : public APawn
{
    GENERATED_BODY()

    /** Jump Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* JumpAction;

    /** Move Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* MoveAction;

    public:
        ALanderPawn();

    protected:
        virtual void BeginPlay() override;
        virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

        void ThrustForward(const FInputActionValue& Value);
        void ThrustRight(const FInputActionValue& Value);
        void ExitLander();

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
