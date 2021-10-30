// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/WorldSettings.h"
#include "BlacManWorldSettings.generated.h"

/**
 * 
 */
UCLASS(config = game)
class BLACMAN_API ABlacManWorldSettings : public AWorldSettings
{
	GENERATED_BODY()
	
public:
	TArray<class UClass*>& GetEnemyTypesList() { return EnemyTypes; }

private:

	UPROPERTY(EditAnywhere)
	TArray<class UClass*> EnemyTypes;
};
