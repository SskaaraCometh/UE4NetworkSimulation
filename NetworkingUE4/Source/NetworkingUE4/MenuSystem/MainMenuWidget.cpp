// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuWidget.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"

bool UMainMenuWidget::Initialize()
{
	bool Success = Super::Initialize();

	if (!Success) return false;
	
	if (!ensure(HostButton != nullptr)) return false;
	HostButton->OnClicked.AddDynamic(this, &UMainMenuWidget::HostServer);
	
	if (!ensure(JoinButton != nullptr)) return false;
	JoinButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OpenJoinMenu);

	if (!ensure(BackButton != nullptr)) return false;
	BackButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OpenMainMenu);

	if (!ensure(JoinIPButton != nullptr)) return false;
	JoinIPButton->OnClicked.AddDynamic(this, &UMainMenuWidget::JoinServer);

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
	if (MenuInterface != nullptr)
	{
		if (!ensure(JoinIPButton != nullptr)) return;
		if (!ensure(IPTextBox != nullptr)) return;
		const FString Address = IPTextBox->GetText().ToString();
		MenuInterface->Join(Address);
	}
}

void UMainMenuWidget::OpenJoinMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;

	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenuWidget::OpenMainMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(MainMenu != nullptr)) return;

	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenuWidget::InGameLoadMenu()
{
	MenuInterface->InGameLoadMenu();
}
