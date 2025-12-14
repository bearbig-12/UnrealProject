// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/SLGAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

USLGAnimInstance::USLGAnimInstance()
{
}

void USLGAnimInstance::NativeInitializeAnimation()
{

	// 부모함수를 호출하여 기본 초기화 작업 수행
	Super::NativeInitializeAnimation();
	Character = Cast<ACharacter>(GetOwningActor());
	if (Character)
	{
		MovementComponent = Character->GetCharacterMovement();
	}
}

void USLGAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if(Character == nullptr)
	{
		return;
	}
	if (MovementComponent == nullptr)
	{
		return;
	}

	Velocity = MovementComponent->Velocity;
	GroundSpeed = Velocity.Size2D();

	bShouldMove = GroundSpeed > 3.f && MovementComponent->GetCurrentAcceleration() != FVector::ZeroVector;	

	bIsFalling = MovementComponent->IsFalling();
}
