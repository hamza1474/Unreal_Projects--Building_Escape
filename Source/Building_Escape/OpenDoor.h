// Copyright Ameer Hamza 2019

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine\TriggerVolume.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorRequest);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(BlueprintAssignable)
		FDoorRequest OnOpenRequest;
	UPROPERTY(BlueprintAssignable)
		FDoorRequest OnCloseRequest;

private:
	float InitialYaw;
	float CurrentYaw;
	float OpenAngle;
	float DoorLastOpened = 0.0f;

	UPROPERTY(EditAnywhere)
		float DoorCloseDelay = 0.1f;

	UPROPERTY(EditAnywhere)
		float OffsetYaw = 90.0f;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate2 = nullptr;

	UPROPERTY(EditAnywhere)
		AActor* OurLight = nullptr;

	UPROPERTY(EditAnywhere)
		float DoorOpenSpeed = 1.0f;

	UPROPERTY(EditAnywhere)
		float DoorCloseSpeed = 2.0f;

	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	float GetTotalMassOfActorsOnPlate(); // total mass in KG
		
};
