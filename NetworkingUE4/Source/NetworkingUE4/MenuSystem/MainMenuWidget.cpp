// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuWidget.h"
#include "Components/Button.h"

bool UMainMenuWidget::Initialize()
{
	bool Success = Super::Initialize();

	if (!Success) return false;
	
	if (!ensure(Host != nullptr)) return false;
	Host->OnClicked.AddDynamic(this, &UMainMenuWidget::HostServer);
	
	if (!ensure(Join != nullptr)) return false;
	Join->OnClicked.AddDynamic(this, &UMainMenuWidget::JoinServer);

	return true;
}


void UMainMenuWidget::SetMenuInterface(IIMenuInterface* MenuInterface)
{
	this->MenuInterface = MenuInterface;
}

void UMainMenuWidget::Setup()
{
	//Set widget and focus
	this->AddToViewport();

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	APlayerController* PlayerCont = World->GetFirstPlayerController();
	if (!ensure(PlayerCont != nullptr)) return;

	//Set widget and focus
	FInputModeUIOnly InputMode;
	InputMode.SetWidgetToFocus(this->TakeWidget());
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerCont->SetInputMode(InputMode);
	PlayerCont->bShowMouseCursor = true;
}

void UMainMenuWidget::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	Super::OnLevelRemovedFromWorld(InLevel, InWorld);

	FInputModeGameOnly InputModeData;
	GetWorld()->GetFirstPlayerController()->SetInputMode(InputModeData);
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;

}

void UMainMenuWidget::HostServer()
{
	UE_LOG(LogTemp, Warning, TEXT("Host Server"));
	if (MenuInterface != nullptr)
	{
		MenuInterface->Host();
	}
}

void UMainMenuWidget::JoinServer()
{
	UE_LOG(LogTemp, Warning, TEXT("Join Server"));
}
