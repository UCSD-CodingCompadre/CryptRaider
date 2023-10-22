// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Mover.h"
#include "TriggerComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTRAIDER_API UTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTriggerComponent();

	/*
	Attach a mover to the trigger component
	@param UMover* a pointer to the mover being attached
	@return void
	*/
	UFUNCTION(BlueprintCallable)
	void addMover(UMover* mover);

	// Hold the trigger tag for the component
	UPROPERTY(EditAnywhere)
	FName triggerTag;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/*
	Loop through the overlapping actors and check for the tag to trigger
	the corresponding bool in the the mover component
	@param TArray<AActor*> the overlapping actors that triggered the component
	@return void
	*/
	void handleTriggerActors(TArray<AActor*>& actors);

private:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Hold the mover components attached to this trigger
	TArray<UMover*> myMovers;

	/*
	Enable the corresponding bool in the mover component
	@param FName tag the tag to enable
	@return void
	*/
	void enableMoverBool(FName& tag);

	/*
	Disabel the corresponding bool in the mover component
	@param FName tag the tag to disabel
	@return void
	*/
	void disableMoverBool(FName& tag);
};
