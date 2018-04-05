// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


void UTankTrack::SetThrottle(float Throttle)
{
	//Throttle = FMath::Clamp<float>(Throttle, -1.f, 1.f);

	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s throttles : %f"), *Name, Throttle);

	// clamp actual throttle value so player can't over-drive
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	TankRoot->AddForceAtLocation( ForceApplied, ForceLocation );
}


