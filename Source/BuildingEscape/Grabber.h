// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	//How far ahead of the player can we reach in santimetres
	float Reach = 100.f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;
		

	//Ray-cast and grab
	void Grab();
	void Release();

	//Find physics handle component
	void FindPhysicsHandleComponent();
	///Setup Input Component
	void SetupInputComponent();
	//Return hit for first physics body in reach
	const FHitResult GetFirstPhysicsBodyReach();
	//Returns current start of the reach line
	FVector GetReachLineStart();
	//Returns current end of the reach line
	FVector GetReachLineEnd();
};
