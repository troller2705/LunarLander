#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "MainHUDWidget.generated.h"

UCLASS()
class LUNARLANDER_API UMainHUDWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    UPROPERTY(EditAnywhere, Category = Levels, meta = (AllowPrivateAccess = "true"))
    TSoftObjectPtr<UWorld> MenuLevel;

    UPROPERTY(EditAnywhere, Category = Levels, meta = (AllowPrivateAccess = "true"))
    TSoftObjectPtr<UWorld> GameLevel;

    UPROPERTY(meta = (BindWidget))
    UCanvasPanel* FPS_UI;

    UPROPERTY(meta = (BindWidget))
    UCanvasPanel* Lander_UI;

    UPROPERTY(meta = (BindWidget))
    UCanvasPanel* Gameover_UI;

    UPROPERTY(meta = (BindWidget))
    UProgressBar* Fuel;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* Speed;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* Altitude;

    UPROPERTY(meta = (BindWidget))
    UButton* RestartBTN;

    UPROPERTY(meta = (BindWidget))
    UButton* MenuBTN;

    // Called when player mode changes (FPS ↔ Lander)
    UFUNCTION(Category = "HUD")
    void OnPlayerModeChanged(bool bIsInLander);

    // Called when Gameover is hit
    UFUNCTION(Category = "HUD")
    void OnGameover();

    // Called to update Lander HUD values
    UFUNCTION(Category = "HUD")
    void OnFuelChanged(float NewFuel);

    UFUNCTION(Category = "HUD")
    void OnAltitudeChanged(float NewAltitude);

    UFUNCTION(Category = "HUD")
    void OnVelocityChanged(float NewVelocity);

    UFUNCTION(Category = "Menu")
    void OnRestartClick();

    UFUNCTION(Category = "Menu")
    void OnMenuClick();
};
