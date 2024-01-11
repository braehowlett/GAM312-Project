// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = false;

	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	// Set Default Walk Speed
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind Axis Events
	InputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	InputComponent->BindAxis("Turn", this, &APlayerCharacter::Turn);

	// Bind Action Events
	InputComponent->BindAction("Sprint", IE_Pressed, this, &APlayerCharacter::StartSprint);
	InputComponent->BindAction("Sprint", IE_Released, this, &APlayerCharacter::StopSprint);


}

// Move Forward
void APlayerCharacter::MoveForward(float InputAxis)
{
	AddMovementInput(GetActorForwardVector(), InputAxis);
}

// Turn
void APlayerCharacter::Turn(float InputAxis)
{
	TurnAmount = InputAxis;
	AddActorLocalRotation(FRotator(0.0f, TurnAmount, 0.0f)); 
}

// Sprinting
void APlayerCharacter::StartSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void APlayerCharacter::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}


float APlayerCharacter::GetHealth()
{
	return HealthPercentage;
}


