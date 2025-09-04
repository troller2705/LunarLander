// Fill out your copyright notice in the Description page of Project Settings.

#include "MainHUDWidget.h"

void UMainHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	RestartBTN->OnClicked.AddDynamic(this, &UMainHUDWidget::OnRestartClick);
	MenuBTN->OnClicked.AddDynamic(this, &UMainHUDWidget::OnMenuClick);
}

void UMainHUDWidget::OnPlayerModeChanged(bool bIsInLander)
{
	if (bIsInLander)
	{
		Gameover_UI->SetVisibility(ESlateVisibility::Hidden);
		FPS_UI->SetVisibility(ESlateVisibility::Hidden);
		Lander_UI->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Gameover_UI->SetVisibility(ESlateVisibility::Hidden);
		FPS_UI->SetVisibility(ESlateVisibility::Visible);
		Lander_UI->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UMainHUDWidget::OnGameover()
{
	Gameover_UI->SetVisibility(ESlateVisibility::Visible);
	FPS_UI->SetVisibility(ESlateVisibility::Hidden);
	Lander_UI->SetVisibility(ESlateVisibility::Hidden);
}

void UMainHUDWidget::OnFuelChanged(float NewFuel)
{
	float percent = NewFuel / 100;
	Fuel->SetPercent(percent);
}

void UMainHUDWidget::OnAltitudeChanged(float NewAltitude)
{
	Altitude->SetText(FText::FromString("Alt: " + FString::FromInt(NewAltitude)));
}

void UMainHUDWidget::OnVelocityChanged(float NewVelocity)
{
	Speed->SetText(FText::FromString("Velocity: " + FString::FromInt(NewVelocity)));
}

void UMainHUDWidget::OnRestartClick()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(*GameLevel.GetAssetName()), true);
}

void UMainHUDWidget::OnMenuClick()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(*MenuLevel.GetAssetName()), true);
}
