#include "SharedHUD.h"
#include "Blueprint/UserWidget.h"

void ASharedHUD::BeginPlay()
{
    Super::BeginPlay();

    if (MainHUDClass)
    {
        MainHUD = CreateWidget<UMainHUDWidget>(GetWorld(), MainHUDClass);
        if (MainHUD)
        {
            MainHUD->AddToViewport();
        }
    }
}

void ASharedHUD::SetPlayerMode(bool bIsInLander)
{
    if (MainHUD)
    {
        UE_LOG(LogTemp, Warning, TEXT("IsInLander: %s"), (bIsInLander ? TEXT("true") : TEXT("false")));
        MainHUD->OnPlayerModeChanged(bIsInLander); // Calls into Blueprint
    }
}

void ASharedHUD::UpdateFuel(float NewFuel)
{
    if (MainHUD)
    {
        MainHUD->OnFuelChanged(NewFuel);
    }
}

void ASharedHUD::UpdateAltitude(float NewAltitude)
{
    if (MainHUD)
    {
        MainHUD->OnAltitudeChanged(NewAltitude);
    }
}

void ASharedHUD::UpdateVelocity(float NewVelocity)
{
    if (MainHUD)
    {
        MainHUD->OnVelocityChanged(NewVelocity);
    }
}