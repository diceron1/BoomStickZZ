// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Gun.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->MaxWalkSpeed = 300;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(30.44, 1.75, 64)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	//Gun->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
	//Gun->SetOwner(this);
	
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
	PlayerInputComponent->BindAxis("Sprint", this, &AMainCharacter::Sprint);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
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
	if(Gun)
	{
		Gun->PullTrigger();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Gun is null"));
	}
}

void AMainCharacter::Sprint(float Val)
{
	
	if(Val >= 1.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("SPRINT"));
		GetCharacterMovement()->MaxWalkSpeed = 800;//->MaxWalkSpeed = 1200.f;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = 300;
	}
	

}




