// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "Gameframework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//Every frame poll the trigger volume
	if (GetTotalMassOfActorsOnPlate() > TriggerMass) {//Esli ves na triggere bolwe 29
		OnOpen.Broadcast();//Vizvat event BluePrint On Open Request
	}else{
		OnClose.Broadcast();
	}
	
	
}


float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float totalMass = 0.0f;
	TArray<AActor*> AllOverLappingActors;
	if (!PressurePlate) { return totalMass; }//If prplate null to return
	PressurePlate->GetOverlappingActors(AllOverLappingActors);

	for (AActor* actor : AllOverLappingActors)
	{
		totalMass = totalMass + actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return totalMass;
}
