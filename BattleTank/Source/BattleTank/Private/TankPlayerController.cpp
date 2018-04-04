// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

//	Tick
	//	Super
	//	AimTowardsCrossHair();

void ATankPlayerController::BeginPlay() 
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller not possessing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller possessing : %s"), *(ControlledTank->GetName()));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrossHair();
	//UE_LOG(LogTemp, Warning, TEXT("Player Controller ticking"));
}

ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>( GetPawn() );
}

void ATankPlayerController::AimTowardsCrossHair()
{
	if (!GetControlledTank()) { return;	}

	FVector HitLocation; // Out parameter

	// Get world location of linetrace through crosshair
	// if it hits the landscape
	if (GetSightRayHitLocation(HitLocation)) // Has "side-effect", is going to line trace
	{
		GetControlledTank()->AimAt(HitLocation);
		// Tell controlled tank to aim this point
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, 
									ViewportSizeY * CrossHairYLocation);
	//UE_LOG(LogTemp, Warning, TEXT("ScreenLocation : %s"), *ScreenLocation.ToString());

	// "De-project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Look Direction : %s"), *LookDirection.ToString());
		
		// Line-trace along that look direction, and see what we hit(up to max range)
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}
		
	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + ( LookDirection * LineTraceRange );

	// if Line Trace Succeeds
	if ( GetWorld()->LineTraceSingleByChannel(	
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility) )
	{
		// Set hit location
		HitLocation = HitResult.Location;
		return true;
	}
	return false;	// line trace didn't succeed
}

bool ATankPlayerController::GetLookDirection(FVector2D& ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection);
}