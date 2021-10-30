// Fill out your copyright notice in the Description page of Project Settings.


#include "RacistCharacterComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "BaseCharacterComponent.h"

// Sets default values for this component's properties
URacistCharacterComponent::URacistCharacterComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URacistCharacterComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void URacistCharacterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (AutoRun == false)
	{
		UBaseCharacterComponent* const Player = ABlacManGameMode::Get()->GetPlayer();
		FRotator NewRotator = UKismetMathLibrary::FindLookAtRotation(GetWorldLocation(), Player->GetWorldLocation());
		GetOwner()->SetActorRotation(NewRotator);

		const float DistanceToPlayer = FVector::Dist2D(GetWorldLocation(), Player->GetWorldLocation());
		if (DistanceToPlayer > TempRadius)
		{
			FVector VecTo = (Player->GetWorldLocation() - GetWorldLocation());
			VecTo.Z = 0;
			VecTo.Normalize();

			SetWorldLocation(GetWorldLocation() + VecTo * DeltaTime * RunSpeed);
		}
	}
	else
	{
		GetOwner()->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetWorldLocation(), GetWorldLocation() + FVector(0.0f, 10.0f, 0.0f)));
	}
}

