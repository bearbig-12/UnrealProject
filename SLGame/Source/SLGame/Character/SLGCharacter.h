// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SLGCharacter.generated.h"

struct FInputActionValue;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class SLGAME_API ASLGCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	 USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	 UCameraComponent* FollowCamera;

	 UPROPERTY(EditAnywhere)
	 UInputMappingContext* DefaultMappingContext;

	 UPROPERTY(EditAnywhere)
	 UInputAction* MoveAction;

	 UPROPERTY(EditAnywhere)
	 UInputAction* LookAction;



public:
	// Sets default values for this character's properties
	ASLGCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called when the controller is changed
	virtual void NotifyControllerChanged() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UFUNCTION()
	void Move(const  FInputActionValue& Value);
	UFUNCTION()
	void Look(const  FInputActionValue& Value);

};
