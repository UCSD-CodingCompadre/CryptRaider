// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
}

bool UGrabber::hasHitResult(FHitResult& hitResult)
{

	// Hold the rotation of the scene component
	FRotator rotation = GetComponentRotation();

	// Hold the starting location of the component
	FVector start = GetComponentLocation();

	// Hold the end of the debug line
	FVector end = start + GetForwardVector() * grabRange;

	// Hold the collision shape
	FCollisionShape mySphere = FCollisionShape::MakeSphere(sphereRadius);

	// Return hit result
	return GetWorld()->SweepSingleByChannel(
		hitResult,
		start, end,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		mySphere
	);
}

void UGrabber::handleGrab(UPhysicsHandleComponent* physicsHandle, FHitResult& hitResult, bool canGrab)
{
	
	// Hold the pointer to the component that hit the actor
	UPrimitiveComponent* componentHit = hitResult.GetComponent();

	// Check if an object has been hit
	if(canGrab)
	{

		// Wake the component
		componentHit->WakeAllRigidBodies();

		// Grab the component using the physics handle
		physicsHandle->GrabComponentAtLocationWithRotation(
			componentHit,
			NAME_None,
			hitResult.ImpactPoint,
			GetComponentRotation()
		);
	}
}

void UGrabber::grab()
{
	
	// Hold the Physics handle component
	UPhysicsHandleComponent* physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	// Check if the pointer is null
	if(physicsHandle == nullptr)
	{
		return;
	}

	// Hold the hit result
	FHitResult myResult;
	
	// Hold if the hit has happened
	bool hasHit = hasHitResult(myResult);

	// Call helper function that handles the grab
	handleGrab(physicsHandle, myResult, hasHit);
}

void UGrabber::handleRelease(UPhysicsHandleComponent* physicsHandle)
{
	
	// Check if the handle has a component
	if(physicsHandle->GetGrabbedComponent() == nullptr)
	{
		return;
	}
	else
	{

		// Wake the object when releasing
		physicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();

		// Release the component
		physicsHandle->ReleaseComponent();
	}
}

void UGrabber::release()
{
	
	// Hold the Physics handle component
	UPhysicsHandleComponent* physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	// Check if the pointer is null
	if(physicsHandle == nullptr)
	{
		return;
	}

	// Call helper function to handle the release
	handleRelease(physicsHandle);
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// Hold the Physics handle component
	UPhysicsHandleComponent* physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	// Check if the pointer is null
	if(physicsHandle == nullptr)
	{
		return;
	}	
	
	// Hold the new location for the object being moved
	FVector targetLocation = GetComponentLocation() + GetForwardVector() * holdDistance;

	// Set the location of the component grabbed
	physicsHandle->SetTargetLocationAndRotation(targetLocation, GetComponentRotation());
}

