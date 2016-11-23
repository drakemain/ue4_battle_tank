// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto myTank = this->GetControlledTank();

	if (!myTank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController could not posses tank!"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *(myTank->GetName()));
	}

	
}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	this->AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() 
{
	if (!this->GetControlledTank()) { return; }

	FVector HitLocation; // out parameter
	if (this->GetSightRayHitLocation(HitLocation)) {
		this->GetControlledTank()->AimAt(HitLocation);
	}
	
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const 
{
	//find crosshiar pos
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);
	FVector2D ScreenLocation = FVector2D(ViewPortSizeX * this->CrosshairLocationX, ViewPortSizeY * this->CrosshairLocationY);
	
	// 'de-project' the screen position of crosshair into world position
	FVector LookDirection; // out parameter
	if (this->GetLookDirection(ScreenLocation, LookDirection)) {
		// line trace along that direction
		this->GetLookVectorHitLocation(LookDirection, HitLocation);
		return true;
	}
	else {
		HitLocation = FVector(0.0);
		return false;
	}
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const
{
	FVector WorldLocation; // discarded

	return this->DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + (LookDirection * this->MaxHitDistance);

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility)
		) 
	{
		HitLocation = HitResult.Location;
		return true;
	}
	else {
		return false;
	}
}