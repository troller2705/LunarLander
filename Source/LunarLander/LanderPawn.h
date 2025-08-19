#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "LunarLanderCharacter.h"
#include "LanderPawn.generated.h"

UCLASS()
class LUNARLANDER_API ALanderPawn : public APawn
{
    GENERATED_BODY()

    /** Move Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* MoveAction;

    public:
        ALanderPawn();

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

        UPROPERTY(EditAnywhere)
        TSubclassOf<class AFPSCharacter> FPSCharacterClass;

    private:
        UPROPERTY()
        AFPSCharacter* SpawnedFPSCharacter;
};
