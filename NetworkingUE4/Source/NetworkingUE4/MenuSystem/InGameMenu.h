// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.h"
#include "InGameMenu.generated.h"

/**
 * 
 */
UCLASS()
class NETWORKINGUE4_API UInGameMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void CancelMenu();

	UFUNCTION()
	void QuitServer();

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* CancelButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;

protected:
	virtual bool Initialize() override;
	
	
	
};
