// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "PositionReporte.h"


// Sets default values for this component's properties
UPositionReporte::UPositionReporte()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}


// Called when the game starts
void UPositionReporte::BeginPlay()
{
	Super::BeginPlay();
	FString objectName = (*GetOwner()).GetName();
	FVector location = GetOwner()->GetActorLocation();	
	FString objectPos = *FString::Printf(TEXT("X = %f, Y = %f"), location.X, location.Y);
	UE_LOG(LogTemp, Warning, TEXT("%s is at %s"), *objectName, *objectPos)
	
}


// Called every frame
void UPositionReporte::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

