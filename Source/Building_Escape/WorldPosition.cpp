// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPosition.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();

	// ...
	// UE_LOG(LogTemp, Warning, TEXT("Hello warning!"));
	// UE_LOG(LogTemp, Error, TEXT("Hello Error!"));
	// UE_LOG(LogTemp, Display, TEXT("Hello nothing!"));
	FString name = GetOwner()->GetName();
	FVector loc = GetOwner()->GetActorLocation();
	UE_LOG(LogTemp, Display, TEXT("Hello %s "), *loc.ToCompactString());
}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

