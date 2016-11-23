// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"


void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent * BarrelToSet)
{
	this->Barrel = BarrelToSet;
}

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	
	
}

void UTankAimingComponent::AimAt(FVector location, float LaunchSpeed)
{
	if (!this->Barrel) { return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = this->Barrel->GetSocketLocation(FName("Exit"));

	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		location,
		LaunchSpeed,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	)) {
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		this->OrientBarrel(AimDirection);
	}
	

}

void UTankAimingComponent::OrientBarrel(FVector AimDirection) const
{
	FRotator CurrentRotation = this->Barrel->GetForwardVector().Rotation();
	FRotator AimRotation = AimDirection.Rotation();
	FRotator DeltaRotation = AimRotation - CurrentRotation;

	UE_LOG(LogTemp, Warning, TEXT("%s -- %s"), *GetOwner()->GetName(), *AimRotation.ToString());
}
