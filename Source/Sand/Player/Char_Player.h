// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimBlueprint.h"
#include "Interface_Interact.h"
#include "Char_Player.generated.h"

UCLASS()
class SAND_API AChar_Player : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AChar_Player();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Input_MoveX(float);
	void Input_MoveY(float);
	void Input_LookX(float);
	void Input_LookY(float);
	void Input_JumpPressed();
	void Input_UsePressed();
	void Input_UpPressed();
	void Input_DownPressed();
	void Input_LeftPressed();
	void Input_LeftReleased();
	void Input_RightPressed();
	void Input_RightReleased();

	UFUNCTION(Server, Reliable, WithValidation)
	void Interact(int iState);
};
