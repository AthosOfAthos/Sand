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

	velocity = FVector(0, 0, 0);
	acceleration = FVector(0, 0, 0);
	n_position = FVector(0, 0, 0);
	orientation = GetActorRotation();
	mass = 1000;
	drag = 0.001;
	angularDrag = 0.1;
	elasticity = 1.1;
	throttle = 0;
	helm = 0.00;
	maxThrottle = 10;

	CollisionShape = FCollisionShape::MakeBox(FVector(200,200,50));
	
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
	float turn = helm*((float)1-angularDrag);
	orientation.operator+=(FRotator(0,turn,0));
	SetActorRotation(orientation);
	acceleration = FVector(cos(orientation.Yaw* PI / 180)*throttle*maxThrottle/mass, sin(orientation.Yaw * PI/180)*throttle*maxThrottle / mass,0);//this is somewhata
	velocity.operator*=((float)1 - drag);
	velocity.operator+=(acceleration);
	n_position.operator=(velocity);
	
	
	FVector targetlocation = ActorLocation;
	targetlocation.operator+=(n_position);
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White, velocity.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Blue, acceleration.ToString());
	}
	FCollisionQueryParams params = FCollisionQueryParams(FName(TEXT("YES")), false, this);
	bool isHit = GetWorld()->SweepMultiByProfile(OutHits, ActorLocation, ActorLocation, FQuat(orientation), "BoatHull", CollisionShape, params);
	if(isHit){
		//What should happen if it hits something?
		FVector redirection = FVector();
		for (auto& Hit : OutHits) {
			redirection = Hit.ImpactNormal.operator-(FVector(0,0, Hit.ImpactNormal.Z));
			redirection = redirection.operator*=(velocity.Size());
		}

		targetlocation=(ActorLocation.operator+(n_position.operator*(-2)));
		velocity = redirection*elasticity;//Ok so this is bad physics 
			
		
	}
	DrawDebugBox(GetWorld(), ActorLocation, CollisionShape.GetBox(), FQuat(orientation), FColor::Green);
	SetActorLocation(targetlocation);
}
void AActor_Boat::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AActor_Boat, velocity);
	DOREPLIFETIME(AActor_Boat, mass);
	DOREPLIFETIME(AActor_Boat, throttle);
	DOREPLIFETIME(AActor_Boat, helm);
}
float AActor_Boat::getThrottle() {
	return throttle;
}
float AActor_Boat::getHelm() {
	return helm;
}
void AActor_Boat::setThrottle(float newThrottle) {
	throttle = newThrottle;
}
void AActor_Boat::setHelm(float newHelm) {
	helm = newHelm;
}
float AActor_Boat::getMaxThrottle() {
	return maxThrottle;
}
void AActor_Boat::setMaxThrottle(float newMaxThrottle) {
	maxThrottle = newMaxThrottle;
}
/**Give it the axis of the shape as X Y Z about the center
*/
void AActor_Boat::setBox(FVector size) {
	CollisionShape = FCollisionShape::MakeBox(size);
}
