// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward Declaration
class UTankBarrel;
class UTankAimingComponent;
class UTankMovementComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

protected:
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent * TankAimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent * TankMovementComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();

	UPROPERTY(EditAnywhere, Category = Setup) // Can be editted anywhere
	//UClass* ProjectileBlueprint;	// Alternative http://api.unrealengine.com/KOR/Programming/UnrealArchitecture/TSubclassOf/
	TSubclassOf<AProjectile> ProjectileBluePrint;

	UPROPERTY(EditDefaultsOnly, Category = Firing) // Can be editted only in Blueprint
	float LaunchSpeed = 4000; // 40 m/s

	// Local barrel ref for spawning projectile
	UTankBarrel * Barrel = nullptr;

	float ReloadTimeInSeconds = 3.f;

	double LastFireTime = 0.0;
};
