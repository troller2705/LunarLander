#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GravityGunComponent.h"
#include "FPSCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

UCLASS()
class LUNARLANDER_API AFPSCharacter : public ACharacter
{
    GENERATED_BODY()

    /** Pawn mesh: 1st person view (arms; seen only by self) */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
    USkeletalMeshComponent* Mesh1P;

    /** First person camera */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    UCameraComponent* FirstPersonCameraComponent;

    /** Jump Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* JumpAction;

    /** Move Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* MoveAction;

    /** Move Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* ExitLanderAction;

    /** Move Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* GrabAction;

    /** Move Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* LaunchAction;

public:
    AFPSCharacter();

protected:
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    /** Called for movement input */
    void Move(const FInputActionValue& Value);

    /** Called for looking input */
    void Look(const FInputActionValue& Value);

    void ReturnToLander();

public:
    virtual void Tick(float DeltaTime) override;

    /** Look Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    class UInputAction* LookAction;

    UPROPERTY(EditAnywhere)
    TSubclassOf<class ALanderPawn> LanderPawnClass;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gravity Gun")
    UGravityGunComponent* GravityGun;

    /** Returns Mesh1P subobject **/
    USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
    /** Returns FirstPersonCameraComponent subobject **/
    UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }


private:
    UPROPERTY()
    ALanderPawn* SpawnedLander;
};
