// Fill out your copyright notice in the Description page of Project Settings.

#include "Char_Player.h"

// Sets default values
AChar_Player::AChar_Player()
{
	//set flags
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	bReplicateMovement = true;
	//Collision
	GetCapsuleComponent()->SetCollisionProfileName("Player");
	//Movement
	GetCharacterMovement()->JumpZVelocity = 1000;
	GetCharacterMovement()->GravityScale = 3;
	//Setup skeletal mesh
	GetMesh()->SetSkeletalMesh(LoadObject<USkeletalMesh>(NULL, TEXT("/Game/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin")));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	GetMesh()->bOwnerNoSee = true;
	//Set skeletal animations bp
	UAnimBlueprint* AnimationBP = LoadObject<UAnimBlueprint>(NULL, TEXT("AnimBlueprint'/Game/AnimStarterPack/UE4ASP_HeroTPP_AnimBlueprint.UE4ASP_HeroTPP_AnimBlueprint'"));
	GetMesh()->SetAnimInstanceClass(AnimationBP->GetAnimBlueprintGeneratedClass());
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

	PlayerInputComponent->BindAction("Key_Jump", IE_Pressed, this, &AChar_Player::Input_JumpPressed);
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

void AChar_Player::Input_JumpPressed()
{
	ACharacter::Jump();
}