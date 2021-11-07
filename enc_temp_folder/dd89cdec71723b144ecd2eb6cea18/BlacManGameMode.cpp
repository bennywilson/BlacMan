// Copyright Epic Games, Inc. All Rights Reserved.

#include "BlacManGameMode.h"
#include "BlacManPlayerController.h"
#include "BlacManCharacter.h"
#include "Public/BlacManWorldSettings.h"
#include "Private/RacistCharacterComponent.h"
#include "UObject/ConstructorHelpers.h"

ABlacManGameMode* ABlacManGameMode::s_BlacManGameMode = nullptr;

ABlacManGameMode::ABlacManGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ABlacManPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ABlacManGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld() && GetWorld()->IsGameWorld())
	{
		s_BlacManGameMode = this;
	}
}

void ABlacManGameMode::BeginDestroy()
{
	Super::BeginDestroy();

	if (GetWorld() && GetWorld()->IsGameWorld())
	{
		s_BlacManGameMode = nullptr;
	}

}

void ABlacManGameMode::RegisterCharacter(UBaseCharacterComponent* const ComponentToRegister)
{
	CharacterList.Add(ComponentToRegister);
}

void ABlacManGameMode::UnregisterCharacter(UBaseCharacterComponent* const ComponentToRemove)
{
	CharacterList.Remove(ComponentToRemove);
}

UBaseCharacterComponent* ABlacManGameMode::GetPlayer()
{
	for (int i = 0; i < CharacterList.Num(); i++)
	{
		UBaseCharacterComponent* const Player = CharacterList[i];
		if (Cast<URacistCharacterComponent>(Player) == nullptr)
		{
			return Player;
		}
	}

	return nullptr;
}

void ABlacManGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	bool bHasEnemies = false;
	for (int i = 0; i < CharacterList.Num(); i++)
	{
		if (Cast<URacistCharacterComponent>(CharacterList[i]) != nullptr)
		{
			bHasEnemies = true;
			break;
		}
	}

	if (bHasEnemies == false && GetPlayer())
	{
		ABlacManWorldSettings* const WorldSettings = Cast<ABlacManWorldSettings>(GetWorldSettings());

		FRotator DefaultRot(90.0f, 90.0f, 0.0f);
		FVector CurOffset(1200.0f, 1700.0f, 0.0f);

		for (int i = 0; i < 2; i++)
		{
			FVector DefaultLoc = GetPlayer()->GetOwner()->GetActorLocation() + CurOffset;
			AActor* NewEnemy = GetWorld()->SpawnActor(WorldSettings->GetEnemyTypesList()[i]->GetDefaultObject()->GetClass(), &DefaultLoc, &DefaultRot);
			
			if (NewEnemy)
			{
				NewEnemy->SetActorRotation(DefaultRot);
				CharacterList.Add((UBaseCharacterComponent*)NewEnemy->GetComponentByClass(UBaseCharacterComponent::StaticClass()));
			}
//			CurOffset.Y -= 300.0f;
			CurOffset.X += 300.0f;
		}
	}
}
