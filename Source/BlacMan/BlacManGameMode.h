// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BlacManGameMode.generated.h"

UCLASS(minimalapi)
class ABlacManGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	static ABlacManGameMode* Get() { return s_BlacManGameMode; }

	ABlacManGameMode();
	
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	virtual void Tick(float DeltaSeconds) override;

	void RegisterCharacter(class UBaseCharacterComponent* const ComponentToRegister);
	void UnregisterCharacter(UBaseCharacterComponent* constComponentToRemove); 
	UBaseCharacterComponent* GetPlayer();

private:

	static ABlacManGameMode* s_BlacManGameMode;

	TArray<class UBaseCharacterComponent*> CharacterList;
};