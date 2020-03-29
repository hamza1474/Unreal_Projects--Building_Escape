// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#define OUTPARAM
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


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// Pointer Protection
	if (!PhysicsHandle) { return; }

	if(PhysicsHandle->GrabbedComponent)
	{
		FVector LineTraceEnd = GetReachLineEnd();
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}
	
}

void UGrabber::Grab()
{
	auto HitResult = GetFirstPhysicsBodyInReach();
	if (HitResult.GetComponent())
	{
		PhysicsHandle->GrabComponent(
			HitResult.GetComponent(),
			NAME_None,
			HitResult.GetActor()->GetActorLocation(),
			true
		);
	}
}

void UGrabber::Release()
{
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->ReleaseComponent();
	}
}

void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("[%s] object has no Physics Handle"), *GetOwner()->GetName());
	}
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	FVector PlayerViewLocation;
	FRotator PlayerViewRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUTPARAM PlayerViewLocation,
		OUTPARAM PlayerViewRotation
		);

	FVector LineTraceEnd = PlayerViewLocation + PlayerViewRotation.Vector() * Reach;
	FHitResult HitResult;
	FCollisionQueryParams TracerParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUTPARAM HitResult,
		GetReachLineStart(),
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TracerParams
		);
	return HitResult;
}

FVector UGrabber::GetReachLineStart()
{
	FVector PlayerViewLocation;
	FRotator PlayerViewRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUTPARAM PlayerViewLocation,
		OUTPARAM PlayerViewRotation
		);

	return PlayerViewLocation;

}

FVector UGrabber::GetReachLineEnd()
{
	FVector PlayerViewLocation;
	FRotator PlayerViewRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUTPARAM PlayerViewLocation,
		OUTPARAM PlayerViewRotation
		);

	return PlayerViewLocation + PlayerViewRotation.Vector() * Reach;
	
}

