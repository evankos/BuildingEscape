// Copyright stufs

#include "BuildingEscape.h"
#include "OpenDoor.h"


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

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	InitialQuaternion = GetOwner()->GetActorRotation().Quaternion();
	Owner = GetOwner();
	
}

void UOpenDoor::SlideDoorOpen()
{
	FQuat rotation = Owner->GetActorRotation().Quaternion();
	if (rotation.Z > OpenAngle) {
		rotation.Z -= .01;
		UE_LOG(LogTemp, Warning, TEXT("rotation: %s"), *rotation.ToString());
		GetOwner()->SetActorRotation(rotation);
	} 
}
void UOpenDoor::SlideDoorClose()
{
	{
		FQuat rotation = Owner->GetActorRotation().Quaternion();
		if (rotation.Z < InitialQuaternion.Z) {
			rotation.Z += .01;
			UE_LOG(LogTemp, Warning, TEXT("rotation: %s"), *rotation.ToString());
			GetOwner()->SetActorRotation(rotation);
		}
	}
}

// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	if (PressurePlate->IsOverlappingActor(ActorThatOpens)) {
		SlideDoorOpen();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	else {
		if (GetWorld()->GetTimeSeconds() > LastDoorOpenTime + DoorCloseDelay) SlideDoorClose();
	}
}



