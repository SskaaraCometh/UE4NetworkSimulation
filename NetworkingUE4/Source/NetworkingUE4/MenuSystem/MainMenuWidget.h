// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IMenuInterface.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class NETWORKINGUE4_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* JoinButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* HostButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* BackButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* JoinIPButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* QuitButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UWidget* JoinMenu;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UWidget* MainMenu;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UEditableTextBox* IPTextBox;

	void SetMenuInterface(IIMenuInterface* MenuInterface);

	void Setup();

	void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;

private:
	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void JoinServer();

	UFUNCTION()
	void OpenJoinMenu();

	UFUNCTION()
	void OpenMainMenu();

	UFUNCTION()
	void InGameLoadMenu();

	UFUNCTION()
	void QuitPressed();
	
protected: 
	virtual bool Initialize() override;

	IIMenuInterface* MenuInterface = nullptr;
	
};
