// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "UnrealNetwork.h"
#include "GameFramework/Actor.h"
#include "Actor_Boat.generated.h"

UCLASS()
class SAND_API AActor_Boat : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AActor_Boat();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	FVector velocity;
	FVector acceleration;
	FVector n_position;
	FRotator orientation;
	int mass;
	float drag;
	float angularDrag;
	int elasticity;
	int throttle = 40000; //inherited
	float helm = 0.05;

	TArray<FHitResult> OutHits;
	FVector ActorLocation = GetActorLocation();
	FCollisionShape CollisionShape = FCollisionShape::MakeSphere(200.f);

};