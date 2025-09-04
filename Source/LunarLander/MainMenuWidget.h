// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MainMenuWidget.generated.h"

UCLASS()
class LUNARLANDER_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, Category = Levels, meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UWorld> GameLevel;

	UPROPERTY(meta = (BindWidget))
	UButton* StartBTN;

	UPROPERTY(meta = (BindWidget))
	UButton* SettingsBTN;

	UPROPERTY(meta = (BindWidget))
	UButton* ExitBTN;

	UFUNCTION(Category = "Menu")
	void OnStartClick();

	UFUNCTION(Category = "Menu")
	void OnSettingsClick();

	UFUNCTION(Category = "Menu")
	void OnExitClick();

};
