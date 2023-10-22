// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

// Sets default values for this component's properties
UTriggerComponent::UTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTriggerComponent::addMover(UMover* mover)
{
	
	// Add the mover
	myMovers.Add(mover);	
}

void UTriggerComponent::enableMoverBool(FName& tag)
{

	// Loop through movers
	for(int counter = 0; counter < myMovers.Num(); counter++)
	{

		// Enable the mover
		myMovers[counter]->setMoverBools(tag, true);
	}
}

void UTriggerComponent::disableMoverBool(FName& tag)
{

	// Loop through movers
	for(int counter = 0; counter < myMovers.Num(); counter++)
	{

		// Enable the mover
		myMovers[counter]->setMoverBools(tag, false);
	}
}

void UTriggerComponent::handleTriggerActors(TArray<AActor*>& actors)
{

	// Loop through the actor pointers
	for(int counter = 0; counter < actors.Num(); counter++)
	{

		// Check if the actor has the trigger tag
		if (actors[counter]->ActorHasTag(triggerTag))
		{

			// Enable the movers
			enableMoverBool(triggerTag);
			
			// Call each mover's trigger function
			return;
		}
	}

}

// Called every frame
void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Hold the actors
    TArray<AActor*> myActors;

	// Populate myActors array
	GetOverlappingActors(myActors);

	// Check if the array has one element
	if(myActors.Num() > 0)
	{

		// Print the actors in the array
        handleTriggerActors(myActors);
	}
	else
	{

		// Disable the mover
		disableMoverBool(triggerTag);
	}
}

