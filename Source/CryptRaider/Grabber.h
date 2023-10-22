// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

public:	

	// Sets default values for this component's properties
	UGrabber();

	/*
	Triggers the grab functionality of the component
	@param none
	@return void
	*/
	UFUNCTION(BlueprintCallable)
	void grab();

	/*
	Triggers the release functionality of the component
	@param none
	@return void
	*/
	UFUNCTION(BlueprintCallable)
	void release();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/*
	Sweeps to find if the grabber has hit an accepted actor
	@param FHitResult the result of the sweep
	@return bool is true of the sweep found an accepted actor
	*/
	bool hasHitResult(FHitResult& hitResult);

	/*
	Handles the grab using the physics handle component
	@param UPhysicsHandleCompoent* physicsHandle the handle that is going to grab the accepted actor
	FHitResult hitResult the result of the sweep
	bool canGrab is true if the handle can grab the actor
	@return void
	*/
	void handleGrab(UPhysicsHandleComponent* physicsHandle, FHitResult& hitResult, bool canGrab);

	/*
	Handles the release using the physics handle component
	@param UPhysicsHandleCompoent* physicsHandle the handle that is going to release the accepted actor
	@return void
	*/
	void handleRelease(UPhysicsHandleComponent* physicsHandle);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	// Hold the grab range of the component
	UPROPERTY(EditAnywhere)
	float grabRange = 200;

	// Hold the hold distance from the User
	UPROPERTY(EditAnywhere)
	float holdDistance = 200;

	// Hold the radius of sphere sweeping
	UPROPERTY(EditAnywhere)
	float sphereRadius = 100;	
};
