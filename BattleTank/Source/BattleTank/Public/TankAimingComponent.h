// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Forward Declaration
class UTankBarrel; 
class UTankTurret;
class AProjectile;

// Enum for aiming state
UENUM()
enum class EFiringState: uint8
{
	Reloading,
	Aiming,
	Locked
};

// Holds barrel's properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet);

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Aiming;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	void MoveBarrel(FVector AimDirection);

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Firing) // Can be editted only in Blueprint
	float LaunchSpeed = 4000; // 40 m/s

	UPROPERTY(EditAnywhere, Category = Setup) // Can be editted anywhere
											  //UClass* ProjectileBlueprint;	// Alternative http://api.unrealengine.com/KOR/Programming/UnrealArchitecture/TSubclassOf/
	TSubclassOf<AProjectile> ProjectileBluePrint;

	float ReloadTimeInSeconds = 3.f;

	double LastFireTime = 0.0;
};