// Fill out your copyright notice in the Description page of Project Settings.
#include "BaseCharacterComponent.h"
#include "../BlacManGameMode.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UBaseCharacterComponent::UBaseCharacterComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	RunSpeed = 200.0f;
	TempRadius = 100.0f;
	// ...
}


// Called when the game starts
void UBaseCharacterComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld()->IsGameWorld())
	{
		ABlacManGameMode* const GameMode = Cast<ABlacManGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		GameMode->RegisterCharacter(this);
	}	
}

void UBaseCharacterComponent::BeginDestroy()
{
	Super::BeginDestroy();

	if (GetWorld() && GetWorld()->IsGameWorld())
	{
		ABlacManGameMode* const GameMode = Cast<ABlacManGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		GameMode->UnregisterCharacter(this);
	}
}

void UBaseCharacterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (AutoRun)
	{
		GetOwner()->SetActorRotation(FRotator(0, 180, 0));
		FVector VecTo = GetOwner()->GetActorRotation().Vector();
		SetWorldLocation(GetWorldLocation() + VecTo * DeltaTime * RunSpeed);
	}
}