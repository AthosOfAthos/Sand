// Fill out your copyright notice in the Description page of Project Settings.

#include "Actor_Boat.h"
#include "DrawDebugHelpers.h"
#include "unrealNetwork.h"
// Sets default values
AActor_Boat::AActor_Boat()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bAlwaysRelevant = true;
	bReplicates = true;
	bReplicateMovement = true;

	velocity = FVector(10, 0, 0);
	acceleration = FVector(0, 0, 0);
	n_position = FVector(0, 0, 0);
	orientation = GetActorRotation();
	mass = 10;
	drag = 0.8;
	angularDrag = 0.8;
	elasticity = 0.9;
	throttle = 40000;
	helm = 0.05;
}

// Called when the game starts or when spawned
void AActor_Boat::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActor_Boat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ActorLocation = GetActorLocation();
//inherited
	float turn = helm*angularDrag;
	orientation.operator+=(FRotator(0,turn,0));
	SetActorRotation(orientation);
	acceleration = FVector(cos(orientation.Yaw* PI / 180)*throttle/mass, sin(orientation.Yaw * PI/180)*throttle / mass,0);//this is somewhata
	velocity.operator*=(drag);
	velocity.operator+=(acceleration.operator*(DeltaTime));
	n_position.operator=(velocity.operator*(DeltaTime));
	
	
	FVector targetlocation = ActorLocation;
	targetlocation.operator+=(n_position);

	//this should be collision code
	FCollisionQueryParams params = FCollisionQueryParams(FName(TEXT("YES")), false, this);
	bool isHit = GetWorld()->SweepMultiByProfile(OutHits, ActorLocation, ActorLocation, FQuat::Identity, "BoatHull", FCollisionShape::MakeBox(FVector(200, 200, 5)), params);
	if(isHit){
		if (GEngine) {
			FVector redirection = FVector();
			for (auto& Hit : OutHits) {
				redirection = Hit.ImpactNormal.operator-(FVector(0,0, Hit.ImpactNormal.Z));
				redirection = redirection.operator*=(velocity.Size());
			}

			targetlocation=(ActorLocation.operator+(n_position.operator*(-2)));
			velocity=redirection;
			orientation = redirection.Rotation();
			
		}
		
	}
	
	//DrawDebugSphere(GetWorld(), ActorLocation, CollisionShape.GetSphereRadius(), 20, FColor::Purple);
	//DrawDebugBox(GetWorld(), ActorLocation, FVector(200,200,50), FColor::Purple);
	
	SetActorLocation(targetlocation);
}
void AActor_Boat::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AActor_Boat, velocity);
	DOREPLIFETIME(AActor_Boat, mass);
	DOREPLIFETIME(AActor_Boat, throttle);
	DOREPLIFETIME(AActor_Boat, helm);
}
int AActor_Boat::getThrottle() {
	return throttle;
}
float AActor_Boat::getHelm() {
	return helm;
}
void AActor_Boat::setThrottle(int newThrottle) {
	throttle = newThrottle;
}
void AActor_Boat::setHelm(float newHelm) {
	helm = newHelm;
}
