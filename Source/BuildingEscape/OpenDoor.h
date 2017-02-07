// Copyright stufs

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;

	void SlideDoorOpen();
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	void SlideDoorClose();

private:
		UPROPERTY(EditAnywhere)
		float OpenAngle = -0.45f;

		UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate=nullptr;


		
		UPROPERTY(EditAnywhere)
		float triggerMass = 50.f;

		UPROPERTY(EditAnywhere)
		float DoorCloseDelay = 0.3f;

		FQuat InitialQuaternion;
		float LastDoorOpenTime;
		AActor* Owner=nullptr;

		TSet<AActor*> overlappingActors;

		float GetTotalMassOnPlate();
	
};
