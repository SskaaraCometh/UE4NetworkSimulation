// Fill out your copyright notice in the Description page of Project Settings.

#include "ServerTestGameInstance.h"
#include <EngineGlobals.h>
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "OnlineSessionInterface.h"
#include "UObject/ConstructorHelpers.h"
#include "MovingPlatform.h"
#include "MenuSystem/MainMenuWidget.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Engine.h"

UServerTestGameInstance::UServerTestGameInstance(const FObjectInitializer &ObjectInitialiser)
{
	UE_LOG(LogTemp, Warning, TEXT("const GI"));

	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuWidgets/WBP_MainMenu"));
	if (!ensure(MenuBPClass.Class != nullptr)) return;

	MenuClass = MenuBPClass.Class;
	
}

void UServerTestGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Menu Class: %s"), *MenuClass->GetName());
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found online subsystem %s"), *Subsystem->GetSubsystemName().ToString());
		SessionInterface = Subsystem->GetSessionInterface(); //Allows for matchmaking session
		if (SessionInterface.IsValid())
		{
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UServerTestGameInstance::OnCreateSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UServerTestGameInstance::OnDestroySession);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UServerTestGameInstance::OnFindSessionComplete);

			SessionSearch = MakeShareable(new FOnlineSessionSearch());
			if (SessionSearch.IsValid())
			{
				SessionSearch->bIsLanQuery = true;
				UE_LOG(LogTemp, Warning, TEXT("Starting find session"));
				SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
			}

			
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No subsystem"));
	}
}

void UServerTestGameInstance::LoadMenu()
{
	UMainMenuWidget* Menu = CreateWidget<UMainMenuWidget>(this, MenuClass);
	if (!ensure(Menu != nullptr)) return;

	Menu->Setup();
	Menu->SetMenuInterface(this);
}

void UServerTestGameInstance::Host()
{
	if (SessionInterface.IsValid())
	{
		
		FNamedOnlineSession* ExistingSession = SessionInterface->GetNamedSession(TEXT("New game session"));
		if (ExistingSession != nullptr)
		{
			SessionInterface->DestroySession(TEXT("New game session"));
		}
		else
		{
			CreateSession();
		}
		
	}
}

void UServerTestGameInstance::OnCreateSessionComplete(FName SessionName, bool Success)
{
	//if (!Success)
	//{
	//	UE_LOG(LogTemp, Error, TEXT("Could Not Create Session"));
	//	return;
	//}

	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;
	if (Engine)
	{
		Engine->AddOnScreenDebugMessage(INDEX_NONE, 2.f, FColor::Green, TEXT("Hosting"));
		UWorld* World = GetWorld();
		if (!ensure(World != nullptr)) return;
		if (World)
		{
			World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("World was null"));
		}
	}
	
}

void UServerTestGameInstance::OnDestroySession(FName SessionName, bool Success)
{
	if (Success)
	{
		CreateSession();
	}
}

void UServerTestGameInstance::OnFindSessionComplete(bool Success)
{
	if (Success && SessionSearch.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Finished finding session"));
		for (const FOnlineSessionSearchResult& SearchResult : SessionSearch->SearchResults) //range based for loop
		{
			UE_LOG(LogTemp, Warning, TEXT("Found Session names: %s"), *SearchResult.GetSessionIdStr());
		}
		
	}
}

void UServerTestGameInstance::CreateSession()
{
	if (SessionInterface.IsValid())
	{
		FOnlineSessionSettings SessionSettings;
		SessionSettings.bIsLANMatch = true;
		SessionSettings.NumPublicConnections = 2;
		SessionSettings.bShouldAdvertise = true;
		
		SessionInterface->CreateSession(0, TEXT("New game session"), SessionSettings);
	}
}

void UServerTestGameInstance::Join(const FString &Address)
{
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(INDEX_NONE, 10.f, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));
	
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerCont = GetFirstLocalPlayerController();
	if (!ensure(PlayerCont != nullptr)) return;

	PlayerCont->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}


