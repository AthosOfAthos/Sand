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
	PlayerInputComponent->BindAction("Key_Use", IE_Pressed, this, &AChar_Player::Input_UsePressed);
	PlayerInputComponent->BindAction("Key_Up", IE_Pressed, this, &AChar_Player::Input_UpPressed);
	PlayerInputComponent->BindAction("Key_Down", IE_Pressed, this, &AChar_Player::Input_DownPressed);
	PlayerInputComponent->BindAction("Key_Left", IE_Pressed, this, &AChar_Player::Input_LeftPressed);
	PlayerInputComponent->BindAction("Key_Left", IE_Released, this, &AChar_Player::Input_LeftReleased);
	PlayerInputComponent->BindAction("Key_Right", IE_Pressed, this, &AChar_Player::Input_RightPressed);
	PlayerInputComponent->BindAction("Key_Right", IE_Released, this, &AChar_Player::Input_RightReleased);
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

void AChar_Player::Input_UsePressed()
{
	Interact(0);
}

void AChar_Player::Input_UpPressed()
{
	Interact(1);
}

void AChar_Player::Input_DownPressed()
{
	Interact(2);
}

void AChar_Player::Input_LeftPressed()
{
	Interact(3);
}

void AChar_Player::Input_LeftReleased()
{

}

void AChar_Player::Input_RightPressed()
{
	Interact(4);
}

void AChar_Player::Input_RightReleased()
{

}

bool AChar_Player::Interact_Validate(int iState)
{
	return true;
}

void AChar_Player::Interact_Implementation(int iState)
{
	FHitResult Hit;
	FVector StartLocation = GetActorLocation();
	StartLocation.Z += 50;
	FVector EndLocation = FVector(450, 0, 0);
	EndLocation = GetControlRotation().RotateVector(EndLocation);
	EndLocation += StartLocation;
	FCollisionQueryParams params = FCollisionQueryParams(FName(TEXT("YES")), false, this);
	if (GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECC_WorldDynamic, params))
	{
		if (Hit.Actor != nullptr && Hit.Actor->GetClass()->ImplementsInterface(UInterface_Interact::StaticClass()))
		{
			switch (iState)
			{
			case 0:
				IInterface_Interact::Execute_Interact_Use(Cast<UObject>(Hit.Actor));
				break;
			case 1:
				IInterface_Interact::Execute_Interact_Up(Cast<UObject>(Hit.Actor));
				break;
			case 2:
				IInterface_Interact::Execute_Interact_Down(Cast<UObject>(Hit.Actor));
				break;
			case 3:
				IInterface_Interact::Execute_Interact_Left(Cast<UObject>(Hit.Actor));
				break;
			case 4:
				IInterface_Interact::Execute_Interact_Right(Cast<UObject>(Hit.Actor));
				break;
			}
		}
	}
}