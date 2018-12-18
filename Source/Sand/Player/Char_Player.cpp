// Fill out your copyright notice in the Description page of Project Settings.

#include "Char_Player.h"

// Sets default values
AChar_Player::AChar_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	bReplicateMovement = true;
}

// Called when the game starts or when spawned
void AChar_Player::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChar_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AChar_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Axis_MoveX", this, &AChar_Player::Input_MoveX);
	PlayerInputComponent->BindAxis("Axis_MoveY", this, &AChar_Player::Input_MoveY);
	PlayerInputComponent->BindAxis("Axis_LookX", this, &AChar_Player::Input_LookX);
	PlayerInputComponent->BindAxis("Axis_LookY", this, &AChar_Player::Input_LookY);
}

void AChar_Player::Input_MoveX(float fValue)
{
	FVector vInputVector = FVector(0, fValue, 0);
	FRotator rPlayerRotation = FRotator(0, GetControlRotation().Yaw, 0);
	vInputVector = rPlayerRotation.RotateVector(vInputVector);
	AddMovementInput(vInputVector);
}

void AChar_Player::Input_MoveY(float fValue)
{
	FVector vInputVector = FVector(fValue, 0, 0);
	FRotator rPlayerRotation = FRotator(0, GetControlRotation().Yaw, 0);
	vInputVector = rPlayerRotation.RotateVector(vInputVector);
	AddMovementInput(vInputVector);
}

void AChar_Player::Input_LookX(float fValue)
{
	AddControllerYawInput(fValue);
}

void AChar_Player::Input_LookY(float fValue)
{
	AddControllerPitchInput(fValue);
}