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
	UFUNCTION(BlueprintCallable, Category = "BoatControl")
	int getThrottle();
	UFUNCTION(BlueprintCallable, Category = "BoatControl")
	float getHelm();
	UFUNCTION(BlueprintCallable, Category = "BoatControl")
	void setThrottle(int newThrottle);
	UFUNCTION(BlueprintCallable, Category = "BoatControl")
	void setHelm(float newHelm);
	UFUNCTION(BlueprintCallable, Category = "BoatSetup")
	void setBox(FVector size);
private:
	FVector acceleration;
	FVector n_position;
	UPROPERTY(Replicated)
	FVector velocity;
	UPROPERTY(Replicated)
	FRotator orientation;
	float drag;
	float angularDrag;
	int elasticity;
	UPROPERTY(Replicated)
	int mass;
	UPROPERTY(Replicated)
	int throttle;
	UPROPERTY(Replicated)
	float helm;


	TArray<FHitResult> OutHits;
	FVector ActorLocation = GetActorLocation();
	FCollisionShape CollisionShape;

};