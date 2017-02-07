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

	if(PressurePlate){
		PressurePlate->OnActorBeginOverlap.AddDynamic(this, &UOpenDoor::OnOverlap);
		PressurePlate->OnActorEndOverlap.AddDynamic(this,&UOpenDoor::OnOverlap);
	}
	
}



// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	
}


void UOpenDoor::OnOverlap(AActor* Actor, AActor* OtherActor)
{
	if (GetTotalMassOnPlate() > triggerMass) {
		SlideDoorOpen();
	}
	else {
		SlideDoorClose();
	}
}





void UOpenDoor::SlideDoorOpen()
{
	//FQuat rotation = Owner->GetActorRotation().Quaternion();
	//if (rotation.Z > OpenAngle) {
	//	rotation.Z = OpenAngle;
	//	//UE_LOG(LogTemp, Warning, TEXT("rotation: %s"), *rotation.ToString());
	//	GetOwner()->SetActorRotation(rotation);
	//}
	OnOpenRequest.Broadcast();
}
void UOpenDoor::SlideDoorClose()
{

	//FQuat rotation = Owner->GetActorRotation().Quaternion();
	//if (rotation.Z < InitialQuaternion.Z) {
	//	rotation.Z = InitialQuaternion.Z;
	//	//UE_LOG(LogTemp, Warning, TEXT("rotation: %s"), *rotation.ToString());
	//	GetOwner()->SetActorRotation(rotation);
	//}
	OnCloseRequest.Broadcast();

}
float UOpenDoor::GetTotalMassOnPlate() {
	float TotalMass = 0.f;
	PressurePlate->GetOverlappingActors(overlappingActors);
	for (AActor* overlappingActor : overlappingActors) {
		TotalMass += overlappingActor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		//UE_LOG(LogTemp, Warning, TEXT("Actor: %s"), *overlappingActor->GetName());
	}
	return TotalMass;
}

