// Fill out your copyright notice in the Description page of Project Settings.


#include "PositionReport.h"
#include "MyClass.h"
#include "Gameframework/Actor.h"

// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bWantsBeginPlay = true;
}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();
	
	FString objectName = GetOwner()->GetName();//Polu4it imya objecta
	FString	objectPos = GetOwner()->GetTransform().GetLocation().ToString();//Polu4it mestopolojenie objecta
	UE_LOG(LogTemp, Warning, TEXT("%s is at %s"), *objectName,*objectPos);//Log warning yellow color zcezdo4ka eto pointer
	//MyClass mClass(*objectName);
	//UE_LOG(LogTemp, Warning, TEXT("Position Report %s"), *mClass.getName());//Log s pomowy classa 
}


// Called every frame
void UPositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}