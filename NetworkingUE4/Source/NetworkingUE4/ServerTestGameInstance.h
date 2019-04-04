// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSubsystem.h"
#include "MenuSystem/IMenuInterface.h"
#include "MenuSystem/MainMenuWidget.h"
#include "MenuSystem/InGameMenu.h"
#include "ServerTestGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class NETWORKINGUE4_API UServerTestGameInstance : public UGameInstance, public IIMenuInterface
{
	GENERATED_BODY()
	
public:
	UServerTestGameInstance(const FObjectInitializer &ObjectInitialiser);

	virtual void Init() override;

	UFUNCTION(Exec)
	void Host();

	UFUNCTION(Exec)
	void Join(const FString &Address);

	UFUNCTION(BlueprintCallable)
	void LoadMenu();

	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	UFUNCTION(BlueprintCallable)
	virtual void InGameLoadMenu() override;

private:
	IOnlineSessionPtr SessionInterface;

	void CreateSession();

	void OnCreateSessionComplete(FName SessionName, bool Success);

	void OnDestroySession(FName SessionName, bool Success);

	void OnFindSessionComplete(bool Success);

	
	
	TSubclassOf<class UUserWidget> MenuClass;

	UMainMenuWidget* Menu;

	TSubclassOf<class UUserWidget> InGameMenuClass;

};