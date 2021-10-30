// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BlacManGameMode.h"
#include "Components/ActorComponent.h"
#include "BaseCharacterComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UBaseCharacterComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseCharacterComponent();

	FVector GetWorldLocation() const { return GetOwner()->GetActorLocation(); }
	void SetWorldLocation(const FVector& NewLocation) { GetOwner()->SetActorLocation(NewLocation); }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


protected:

	UPROPERTY(EditAnywhere)
	float RunSpeed;

	UPROPERTY(EditAnywhere)
	float TempRadius;

	UPROPERTY(EditAnywhere)
	bool AutoRun;
};
