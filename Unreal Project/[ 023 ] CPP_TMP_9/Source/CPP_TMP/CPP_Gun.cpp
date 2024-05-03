// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Gun.h"

// Sets default values
ACPP_Gun::ACPP_Gun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPP_Gun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_Gun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

