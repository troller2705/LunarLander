#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainHUDWidget.h"   // include our new class
#include "SharedHUD.generated.h"

UCLASS()
class LUNARLANDER_API ASharedHUD : public AHUD
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UMainHUDWidget> MainHUDClass;

    UPROPERTY()
    UMainHUDWidget* MainHUD;

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void OnGameover();

    // Mode switching
    UFUNCTION(BlueprintCallable, Category = "HUD")
    void SetPlayerMode(bool bIsInLander);

    // HUD updates
    UFUNCTION(BlueprintCallable, Category = "HUD")
    void UpdateFuel(float NewFuel);

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void UpdateAltitude(float NewAltitude);

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void UpdateVelocity(float NewVelocity);
};
