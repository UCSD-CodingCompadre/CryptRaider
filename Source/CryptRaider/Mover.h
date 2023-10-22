// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Mover.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UMover : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMover();
	
	/*
	Sets the bools of the component.
	@param	FName actorTag the name of the actor that triggered the function
	bool enable the bool to set the corresponding variable
	@return void		
	*/
	void setMoverBools(FName actorTag, bool enable);


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Hold the starting location of the mover 
	UPROPERTY(VisibleAnywhere)
	FVector startingLocation;

	// Hold the velocity in the upwards direction
	UPROPERTY(EditAnywhere)
	FVector upVelocity = FVector(0, 0, 200);
	
	// Holds the velocity in the downwards direction
	UPROPERTY(EditAnywhere)
	FVector downVelocity =  FVector(0, 0, -200);
	
	// Hold the travel distance limit
	UPROPERTY(EditAnywhere)
	float maxDistance = 600;
	
	// Hold the distance between the mover and it's starting location
	UPROPERTY(VisibleAnywhere)
	float distanceMoved;

	// Hold the overshot distance between the mover and it's ending location
	UPROPERTY(VisibleAnywhere)
	float distanceOvershot;
	
	// Hold if the mover should move the actor
	UPROPERTY(EditAnywhere)
	bool shouldMove = false;
	
	// Hold if Larry is in the right coffin
	UPROPERTY(EditAnywhere)
	bool isLarryCorrect = false;
	
	// Hold if Bob is in the right coffin
	UPROPERTY(EditAnywhere)
	bool isBobCorrect = false;
	
	// Hold if Tim is in the right coffin
	UPROPERTY(EditAnywhere)
	bool isTimCorrect = false;

	// Hold if the trap is set
	UPROPERTY(EditAnywhere)
	bool isTrapSet = false;

	// Hold the tag for Bob
	UPROPERTY(VisibleAnywhere);
	FString bob = "Bob";

	// Hold the tag for Larry
	UPROPERTY(VisibleAnywhere)
	FString larry = "Larry";

	// Hold the tag for Tim
	UPROPERTY(VisibleAnywhere)
	FString tim = "Tim";
	
	// Hold the tag for User
	UPROPERTY(VisibleAnywhere)
	FString user = "User";

	// Hold if the upward movement is complete
	UPROPERTY(VisibleAnywhere)
	bool isUpwardComplete = false;

	// Hold if the downward movement is complete
	UPROPERTY(VisibleAnywhere)
	bool isDownwardComplete = false;
};
