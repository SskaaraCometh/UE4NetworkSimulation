// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class NETWORKINGUE4_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
	
	
public:
	AMovingPlatform();
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

	UPROPERTY (EditAnywhere)
	float velocity = 10.f;

	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
	FVector TargetLocation; 

	void ActiveTrigger();
	void RemoveActiveTrigger();
	
private:

	FVector GlobalTargetLocation;
	FVector GlobalStartLocation;

	bool HitTargetLocation;

	UPROPERTY(EditAnywhere)
	int ActiveTriggers = 1;

};
