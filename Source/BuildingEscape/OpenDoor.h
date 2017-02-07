// Copyright stufs

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSwingRequest);


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

	UFUNCTION()
	void OnOverlap(AActor* Actor,AActor* OtherActor);

	void SlideDoorClose();

	UPROPERTY(BlueprintAssignable)
	FOnSwingRequest OnOpenRequest;

	UPROPERTY(BlueprintAssignable)
	FOnSwingRequest OnCloseRequest;

private:

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate=nullptr;



		
	UPROPERTY(EditAnywhere)
	float triggerMass = 22.f;

	AActor* Owner=nullptr;

	TSet<AActor*> overlappingActors;

	float GetTotalMassOnPlate();
	
};
