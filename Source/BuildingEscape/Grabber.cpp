// Copyright stufs

#include "BuildingEscape.h"
#include "Grabber.h"

#define OUT
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
	
	FindPhysicsComponent();
	SetupInputComponent();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (physicsHandle->GrabbedComponent) {
		FVector LineTraceEnd = GetReachEnd();
		physicsHandle->SetTargetLocation(LineTraceEnd);
	}
	
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	FVector LineTraceEnd = GetReachEnd();
	DrawDebugLine(GetWorld(), playerLocation, LineTraceEnd, FColor(255, 0, 0));
	FCollisionQueryParams collisionQuery = FCollisionQueryParams(FName(TEXT("")), false, GetOwner());
	///Ray cast
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		playerLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		collisionQuery
	);
	return Hit;
}

FVector UGrabber::GetReachEnd()
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT playerLocation,
		OUT playerRotation
	);
	return playerLocation + playerRotation.Vector() * Reach;
}

void UGrabber::SetupInputComponent()
{
	///only appears at runtime
	inputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (inputComponent) {
		UE_LOG(LogTemp, Warning, TEXT("Input component found"));
		///Bind input action
		inputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		inputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s has no input component"), *GetOwner()->GetName());
	}
}

void UGrabber::FindPhysicsComponent()
{
	/// Look for physics handle on the actor (pawn) 
	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (physicsHandle) {
		UE_LOG(LogTemp, Warning, TEXT("Physics handle found"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s has no physics handle"), *GetOwner()->GetName());
	}
}




void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabbing"));
	FHitResult Hit = GetFirstPhysicsBodyInReach();
	AActor* actorHit = Hit.GetActor();
	if (actorHit) {
		UE_LOG(LogTemp, Warning, TEXT("HIT: %s"), *actorHit->GetName());
		UPrimitiveComponent* primitiveComponent = Hit.GetComponent();
		physicsHandle->GrabComponent(primitiveComponent, NAME_None, actorHit->GetActorLocation(), true);
	}
}
void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Releasing"));

	if (physicsHandle->GrabbedComponent) {
		physicsHandle->ReleaseComponent();
	}
}

