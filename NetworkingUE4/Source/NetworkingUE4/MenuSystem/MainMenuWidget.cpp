// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Button.h"
#include "MainMenuWidget.h"

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


void UMainMenuWidget::HostServer()
{
	UE_LOG(LogTemp, Warning, TEXT("Host Server"));
}

void UMainMenuWidget::JoinServer()
{
	UE_LOG(LogTemp, Warning, TEXT("Join Server"));
}
