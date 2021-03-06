// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IMenuInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIMenuInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class NETWORKINGUE4_API IIMenuInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void Host() = 0;
	virtual void Join(const FString& Address) = 0;
	virtual void InGameLoadMenu() = 0;
	virtual void RefreshingServerList() = 0;
};
