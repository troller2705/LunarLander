#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainHUDWidget.generated.h"

UCLASS()
class LUNARLANDER_API UMainHUDWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    // Called when player mode changes (FPS ↔ Lander)
    UFUNCTION(BlueprintImplementableEvent, Category = "HUD")
    void OnPlayerModeChanged(bool bIsInLander);

    // Called to update Lander HUD values
    UFUNCTION(BlueprintImplementableEvent, Category = "HUD")
    void OnFuelChanged(float NewFuel);

    UFUNCTION(BlueprintImplementableEvent, Category = "HUD")
    void OnAltitudeChanged(float NewAltitude);

    UFUNCTION(BlueprintImplementableEvent, Category = "HUD")
    void OnVelocityChanged(float NewVelocity);
};
