// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractModule.h"

// Sets default values for this component's properties
UInteractModule::UInteractModule()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UInteractModule::BeginPlay()
{
	Super::BeginPlay();
}

void UInteractModule::TriggerInteraction()
{
	OnInteract.Broadcast();
}