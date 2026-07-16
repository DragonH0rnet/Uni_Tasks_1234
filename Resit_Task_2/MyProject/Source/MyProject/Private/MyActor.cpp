// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

//Called when the actor is constructed
void AMyActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	UE_LOG(LogTemp, Display, TEXT("Actor Constructed"));
}


// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Display, TEXT("Actor Began Play"));
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UE_LOG(LogTemp, Display, TEXT("Actor Ticked"));

	this->Destroy();
}

//Called when the actor is destroyed
void AMyActor::EndPlay(const EEndPlayReason::Type EndPlayReason) 
{
	UE_LOG(LogTemp, Display, TEXT("Actor Destroyed"));
	FActorSpawnParameters Params;
	Super::EndPlay(EndPlayReason);

}

