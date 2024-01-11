// Fill out your copyright notice in the Description page of Project Settings.


#include "LightSwitchButton.h"
#include "Components/PointLightComponent.h"
#include "Components/SphereComponent.h"


// Sets default values
ALightSwitchButton::ALightSwitchButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	LightIntensity = 3000.0f;

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Point Light"));
	PointLight->Intensity = LightIntensity;
	RootComponent = PointLight;

	LightSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Light Sphere Component"));
	LightSphere->InitSphereRadius(300.0f);
	LightSphere->SetCollisionProfileName(TEXT("Trigger"));
	LightSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	LightSphere->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ALightSwitchButton::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALightSwitchButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALightSwitchButton::ToggleLight()
{
	PointLight->ToggleVisibility();
}
