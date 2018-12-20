// Fill out your copyright notice in the Description page of Project Settings.

#include "Actor_Boat.h"

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
	mass = 10;
	drag = 0.8;
	angularDrag = 0.8;
	elasticity = 0.9;

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
	int throttle = 200000; //inherited
	float helm = 0.05; //inherited
	float turn = helm*angularDrag;
	orientation.operator+=(FRotator(0,turn,0));
	SetActorRotation(orientation);
	acceleration = FVector(cos(orientation.Yaw* PI / 180)*throttle/mass, sin(orientation.Yaw * PI/180)*throttle / mass,0);//this is somewhat
	velocity.operator*=(drag);
	velocity.operator+=(acceleration.operator*=(DeltaTime));
	n_position.operator=(velocity.operator*=(DeltaTime));
	if (GEngine) {
		//if(n_position.Size()>10){
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, acceleration.ToString());
		//}
		
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::SanitizeFloat(n_position.Size()));
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, velocity.ToString());
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, acceleration.ToString());
	}
	FVector targetlocation = GetActorLocation();
	targetlocation.operator+=(n_position);
	//this should be collision code
	/*
	if(collision(targetlocation)){
		targetlocation.operator+=(n_position.operator*=(-1));
		velocity.operator*=(-1);
	}
	*/
	SetActorLocation(targetlocation);
}

