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
	class UButton* Join;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* Host;

	void SetMenuInterface(IIMenuInterface* MenuInterface);

	void Setup();

	void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;

private:
	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void JoinServer();

	
protected: 
	virtual bool Initialize() override;

	IIMenuInterface* MenuInterface = nullptr;
	
};
