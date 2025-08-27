// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	StartBTN->OnClicked.AddDynamic(this, &UMainMenuWidget::OnStartClick);
	SettingsBTN->OnClicked.AddDynamic(this, &UMainMenuWidget::OnSettingsClick);
	ExitBTN->OnClicked.AddDynamic(this, &UMainMenuWidget::OnExitClick);
}