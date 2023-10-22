// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	// Set the starting location
	startingLocation = GetOwner()->GetActorLocation();
}

void UMover::setMoverBools(FName actorTag, bool enable)
{

	// Check if the tag is for Larry
	if(actorTag.ToString().Equals(larry))
	{
		
		// Enable Larry's coffin
		isLarryCorrect = enable;
	}

	// Check if the tag is for Bob
	if(actorTag.ToString().Equals(bob))
	{

		// Enable Bob's coffin
		isBobCorrect = enable;
	}

	// Check if the tag is for Tim
	if(actorTag.ToString().Equals(tim))
	{

		// Enable Tim's coffin
		isTimCorrect = enable;
	}

	// Check if the tag is for the User
	if(actorTag.ToString().Equals(user))
	{

		// Check if the User already enabeled the mover
		if(!enable && shouldMove)
		{

			// Return 
			return;
		}

		// Enable the trap
		isTrapSet = enable;
	}

	// Set if the mover should move the Actor
	shouldMove = isLarryCorrect && isTimCorrect && isBobCorrect;
}

// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Hold the primitive component
	UPrimitiveComponent* moveActor = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	// Check if the actor should move 
	if(shouldMove && !isTrapSet && !isUpwardComplete)
	{
		// Turn on physics
		moveActor->SetSimulatePhysics(true);
		
		// Hold the actor's location
		FVector actorLocation =  GetOwner()->GetActorLocation();
		
		// Hold the target location for the actor
		FVector targetLocation = actorLocation + upVelocity * DeltaTime;	 

		// Hold the distance difference from the starting location
		distanceMoved = FVector::Dist(startingLocation, actorLocation);
			
		// Set the location for each step
		GetOwner()->SetActorLocation(targetLocation);
		
		// Check if the actor moved past the max distance
		if(distanceMoved > maxDistance)
		{

			// Hold the overshot distance
			distanceOvershot = distanceMoved - maxDistance;

			// Hold the normal vector of the move direction
			FVector moveDirection = upVelocity.GetSafeNormal();

			// Hold the new starting location using the normal vector
			startingLocation += moveDirection * distanceMoved;
			
			// Set the new location 
			GetOwner()->SetActorLocation(startingLocation);
			
			// Turn off physics
			moveActor->SetSimulatePhysics(false);

			// Set idle
			isUpwardComplete = true;
		}
	}
	
	// Check if the trap is set;
	if(shouldMove && isTrapSet && !isDownwardComplete)
	{

		// Turn on physics
		moveActor->SetSimulatePhysics(true);

		// Hold the actor's location
		FVector actorLocation =  GetOwner()->GetActorLocation();
		
		// Hold the target location for the actor
		FVector targetLocation = actorLocation + downVelocity * DeltaTime;	 

		// Hold the distance difference from the starting location
		distanceMoved = FVector::Dist(startingLocation, actorLocation);
			
		// Set the location for each step
		GetOwner()->SetActorLocation(targetLocation);
		
		// Check if the actor moved past the max distance
		if(distanceMoved > maxDistance)
		{

			// Hold the overshot distance
			distanceOvershot = distanceMoved - maxDistance;

			// Hold the normal vector of the move direction
			FVector moveDirection = downVelocity.GetSafeNormal();

			// Hold the new starting location using the normal vector
			startingLocation += moveDirection * distanceMoved;
			
			// Set the new location 
			GetOwner()->SetActorLocation(startingLocation);

			// Turn off physics
			moveActor->SetSimulatePhysics(false);

			// Set idle
			isDownwardComplete = true;
		}
	}
}

