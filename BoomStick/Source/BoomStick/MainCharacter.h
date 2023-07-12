// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

//Declare classes rather than including header files for faster compile times. 
class AGun;

UCLASS()
class BOOMSTICK_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Shoot();


private:

UPROPERTY(EditAnywhere)
	float RotationRate = 10;

	void MoveForward(float Val);
	void MoveRight(float Val);
	void LookUpRate(float Val);
	void LookRightRate(float Val);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

	UPROPERTY()
	AGun* Gun;
};
