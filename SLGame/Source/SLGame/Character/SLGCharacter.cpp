// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SLGCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
ASLGCharacter::ASLGCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; // Character가 이동 방향으로 회전하도록 설정
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f); // Character의 회전 속도 설정

	//CreateDefaultSubobject 는 생성자에서만 사용할 수 있는 함수 new와 비슷한 역할을 한다. 뒤에있는 이름은 컴포넌트의 이름이다.
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	//SprigArmComponent를 RootComponent에 붙인다.
	CameraBoom->SetupAttachment(RootComponent);
	// SpringArmComponent의 길이를 설정한다.
	CameraBoom->TargetArmLength = 400.0f;
	// SpringArmComponent가 캐릭터의 회전에 따라 회전하도록 설정한다. 순서는 Pitch, Yaw, Roll pitch는 상하(x), yaw는 좌우(z), roll은 기울기(x)
	CameraBoom->SetRelativeRotation(FRotator(-30.f, 0.f, 0.f));
	CameraBoom->bUsePawnControlRotation = true;


	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->bUsePawnControlRotation = false;

}

// Called when the game starts or when spawned
void ASLGCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASLGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASLGCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	if(APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}



// Called to bind functionality to input
void ASLGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASLGCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASLGCharacter::Look);
	}

}

void ASLGCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if(Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// 주어진 월드 방향 벡터를 따라 'ScaleValue' 크기만큼 이동을 추가합니다.
		// ScaleValue는 일반적으로 -1.0에서 1.0 사이의 값으로, 0보다 작으면 반대 방향으로 이동. 추가로 SclaeValue는 아날로그 입력 장치의 입력 강도를 나타낼 수도 있습니다.
		// 예를들어 0.5값은 정상값의 절반 속도로 이동하고 -1.0값은 반대 방향으로 전체 속도로 이동합니다.
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ASLGCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookDirection = Value.Get<FVector2D>();

	if(Controller != nullptr)
	{
		// yaw = 좌우 회전 (Z축)
		AddControllerYawInput(LookDirection.X);
		// pitch = 상하 회전 (X축)
		AddControllerPitchInput(LookDirection.Y);
	}

}

