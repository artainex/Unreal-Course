// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "BattleTank.h" 


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerTank = GetControlledTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller can't find player tank"));
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("AI Controller found player : %s"), *(PlayerTank->GetName()));
}

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController();

	if (!PlayerPawn)
		return nullptr;

	return Cast<ATank>(PlayerPawn);
}
