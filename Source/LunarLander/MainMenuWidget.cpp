// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	StartBTN->OnClicked.AddDynamic(this, &UMainMenuWidget::OnStartClick);
	SettingsBTN->OnClicked.AddDynamic(this, &UMainMenuWidget::OnSettingsClick);
	ExitBTN->OnClicked.AddDynamic(this, &UMainMenuWidget::OnExitClick);
}

void UMainMenuWidget::OnStartClick()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(*GameLevel.GetAssetName()), true);
}

void UMainMenuWidget::OnSettingsClick()
{
}

void UMainMenuWidget::OnExitClick()
{
	UKismetSystemLibrary::QuitGame(
		GetWorld(), // Or a specific UObject* WorldContextObject if available
		GetWorld()->GetFirstPlayerController(), // Or a specific APlayerController*
		EQuitPreference::Quit, // Defines the preference for quitting (e.g., Quit, Background)
		false // bIgnorePlatformRestrictions: Set to true to force quit even if platform restrictions exist
	);
}
