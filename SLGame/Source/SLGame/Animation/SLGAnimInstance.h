// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SLGAnimInstance.generated.h"

class UCharacterMovementComponent;
class ACharacter;


/**
 * 
 */
UCLASS()
class SLGAME_API USLGAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	ACharacter* Character;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	UCharacterMovementComponent* MovementComponent;

protected:
	// 캐릭터의 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Data")
	FVector Velocity;

	// 캐릭터의 지면 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Data")
	float GroundSpeed;

	// 캐릭터가 달리고 있는지 여부
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Data")
	bool bShouldMove;

	// 캐릭터가 공중에 떠 있는지 여부
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Data")
	bool bIsFalling;


public:
	USLGAnimInstance();

	// Animistance가 초기화 될 때 한번 호출되는 함수
	virtual void NativeInitializeAnimation() override;
	// 매 프레임마다 호출되는 함수(Tick이랑 비슷한 개념)
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
};
