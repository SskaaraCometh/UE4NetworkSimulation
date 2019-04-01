// Fill out your copyright notice in the Description page of Project Settings.

#include "PlatTrigger.h"
#include "Components/BoxComponent.h"

// Sets default values
APlatTrigger::APlatTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(FName("Trigger Volume"));
	if (!ensure(TriggerVolume != nullptr)) return;

	RootComponent = TriggerVolume;

	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &APlatTrigger::OnOverlapBegin);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &APlatTrigger::OnOverlapEnd);
}

// Called when the game starts or when spawned
void APlatTrigger::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlatTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlatTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Activate"));
	for (AMovingPlatform* Platform : PlatformsToTrigger)
	{
		Platform->ActiveTrigger();
	}
}

void APlatTrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Deactivate"));
	for (AMovingPlatform* Platform : PlatformsToTrigger)
	{
		Platform->RemoveActiveTrigger();
	}
}

