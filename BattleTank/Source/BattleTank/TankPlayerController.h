// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// get the pawn the associated with this player controller
	ATank* GetControlledTank() const;
	// point the barrel towards what the crosshair overlays in the world
	void AimTowardsCrosshair();
	// raycast from the crosshair position into the world
	bool GetSightRayHitLocation(FVector &HitLocation) const;
	// get a vector representing the direction the player is looking
	bool GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const;
	// get the world position where the crosshair overlays
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

	UPROPERTY(EditAnywhere)
		float CrosshairLocationX = .5;
	UPROPERTY(EditAnywhere)
		float CrosshairLocationY = 1.f / 3.f;
	UPROPERTY(EditAnywhere)
		float MaxHitDistance = 1000000.f; // distance in centimeters
};
