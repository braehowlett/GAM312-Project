// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCamera.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"

// Constructor
APlayerCamera::APlayerCamera()
{
	GetCameraComponent()->SetAspectRatio(2.35);
	GetCameraComponent()->SetFieldOfView(75.0f);

}

// Begin Play
void APlayerCamera::BeginPlay()
{

	if (StartingCamera)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

		if (PlayerController)
		{
			FViewTargetTransitionParams TransitionParams;
			PlayerController->SetViewTarget(this, TransitionParams);

		}



	}


}