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
	UFUNCTION(BlueprintCallable, Category = "BoatSetup")
	float getThrottle();
	UFUNCTION(BlueprintCallable, Category = "BoatControl")
	float getHelm();
	UFUNCTION(BlueprintCallable, Category = "BoatControl")
	void setThrottle(float newThrottle);
	UFUNCTION(BlueprintCallable, Category = "BoatControl")
	void setHelm(float newHelm);
	UFUNCTION(BlueprintCallable, Category = "BoatSetup")
	void setBox(FVector size);
	UFUNCTION(BlueprintCallable, Category = "BoatSetup")
	void setMaxThrottle(float newMaxThrottle);
	UFUNCTION(BlueprintCallable, Category = "BoatSetup")
	float getMaxThrottle();
	//There is a reason we have private variables and it's to stop people like me from doing things like this
	UPROPERTY(BlueprintReadWrite)
	float drag;
	UPROPERTY(BlueprintReadWrite)
	float angularDrag;
	UPROPERTY(BlueprintReadWrite)
	int elasticity;
	UPROPERTY(BlueprintReadWrite, Replicated)
	int mass;
private:
	FVector acceleration;
	FVector n_position;
	UPROPERTY(Replicated)
	FVector velocity;
	UPROPERTY(Replicated)
	FRotator orientation;
	UPROPERTY(Replicated)
	float throttle;
	UPROPERTY(Replicated)
	float helm;
	float maxThrottle;


	TArray<FHitResult> OutHits;
	FVector ActorLocation = GetActorLocation();
	FCollisionShape CollisionShape;

};