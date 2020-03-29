// Copyright Ameer Hamza 2019


#include "OpenDoor.h"
#include "Engine//World.h"
#include "Components/LightComponent.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"

#define OUTPARAM
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

	// ...

	InitialYaw = CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	OpenAngle = InitialYaw + OffsetYaw; // can also do TargetYaw += InitialYaw (and make TargetYaw Property)

	if (!PressurePlate)
		UE_LOG(LogTemp, Warning, TEXT("Actor:[%s] has 'OpenDoor' component but no 'PressurePlate' attached"), *GetOwner()->GetName());

}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (GetTotalMassOfActorsOnPlate() >= 55.f)
	{
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else
	{
		if ((GetWorld()->GetTimeSeconds() - DoorLastOpened) >= DoorCloseDelay)
		{
			CloseDoor(DeltaTime);
		}
	}
	if (!PressurePlate2) { return; }
	if (PressurePlate2->IsOverlappingActor(GetWorld()->GetFirstPlayerController()->GetPawn()))
	{
		OurLight->FindComponentByClass<ULightComponent>()->SetIntensity(16.f);
	}
	
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	// UE_LOG(LogTemp, Warning, TEXT("Rotation is: %s"), *DoorRotation.ToString());
	// FRotator DoorRotation = { 0.0f, OpenAngle, 0.0f };
	// CurrentYaw = FMath::Lerp(CurrentYaw, OpenAngle, DoorOpenSpeed * DeltaTime);
	// DoorRotation.Yaw = CurrentYaw;
	// GetOwner()->SetActorRotation(DoorRotation);
	OnOpenRequest.Broadcast();
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	// FRotator DoorRotation = { 0.0f, InitialYaw, 0.0f };
	// CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, DoorCloseSpeed * DeltaTime);
	// DoorRotation.Yaw = CurrentYaw;
	// GetOwner()->SetActorRotation(DoorRotation);
	OnCloseRequest.Broadcast();
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.0f;
	TArray<AActor*> OverlappingActors;
	if (!PressurePlate2) { return TotalMass; }
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	for (const auto& Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		//UE_LOG(LogTemp, Warning, TEXT("Mass of %s is %f"), *Actor->GetName(), Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass());
	}

	return TotalMass;
}

