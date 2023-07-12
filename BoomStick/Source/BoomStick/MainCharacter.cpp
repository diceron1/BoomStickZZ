// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "Gun.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	Gun->AttachToComponent(Root);
	Gun->SetOwner(this);
	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}




void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);

	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AMainCharacter::Shoot);

	//Gamepad Stick (Controller) Bindings
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AMainCharacter::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AMainCharacter::LookRightRate);

}



void AMainCharacter::MoveForward(float Val)
{
	if (Val != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector() * Val);
	}
}

void AMainCharacter::MoveRight(float Val)
{
	if (Val != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector() * Val);
	}
}



void AMainCharacter::LookUpRate(float Val)
{
	AddControllerPitchInput(Val * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AMainCharacter::LookRightRate(float Val)
{
	AddControllerYawInput(Val * RotationRate * GetWorld()->GetDeltaSeconds());
}



void AMainCharacter::Shoot()
{
	Gun->PullTrigger();
}




