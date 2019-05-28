// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Gameframework/Actor.h"
#include "Engine/World.h"
#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Public/DrawDebugHelpers.h"

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
	FindPhysicsHandleComponent();
	SetupInputComponent();
	
}

void UGrabber::SetupInputComponent(){
	// Look for attached Input component (only appears in run time)
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);//posle najatiya knopki vizov metoda Grab etogo classa
	}
	else {//esli nety componenta to logirovat
		UE_LOG(LogTemp, Error, TEXT("%s missing Input component"), *GetOwner()->GetName());//Log warning yellow color zcezdo4ka eto pointer
	}
}

void UGrabber::FindPhysicsHandleComponent(){
	// Look for attached Physics Handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr) {//Esli nety physics handle
		UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component"),*GetOwner()->GetName());//Log warning yellow color zcezdo4ka eto pointer
	}
}



// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (!PhysicsHandle){ return; }//Esli Ravno NULL to prekrawaem
	//if the physics handle is attached move the object we holding
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(GetReachLineEnd());//Stavit component kotorii derjim ryadom s PAWN
	}
}

//knopka najata
void UGrabber::Grab()
{
	
	auto HitResult = GetFirstPhysicsBodyReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto Actorhit = HitResult.GetActor();
	//If we hit something then attach a physics handle
	if (Actorhit)
	{
		if (!PhysicsHandle) { return; } //Esli Ravno NULL to prekrawaem
		PhysicsHandle->GrabComponent(ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(), true);
	}
}


//kogda knopka opuwena
void UGrabber::Release()
{
	if (!PhysicsHandle) { return; } //Esli Ravno NULL to prekrawaem
	PhysicsHandle->ReleaseComponent();
}


const FHitResult UGrabber::GetFirstPhysicsBodyReach()
{
	//Setup query params
	FCollisionQueryParams traceParams(FName(TEXT("")), false, GetOwner());//Getowner zna4it ignore ourself
	//Line trace (AKA ray-cast) out to reach distance
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByObjectType(
		HitResult,
		GetReachLineStart(),
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		traceParams
	);

	return HitResult;
}

FVector UGrabber::GetReachLineStart()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);
	
	return PlayerViewPointLocation;
}


FVector UGrabber::GetReachLineEnd()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);
	FVector lineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
	return lineTraceEnd;
}
