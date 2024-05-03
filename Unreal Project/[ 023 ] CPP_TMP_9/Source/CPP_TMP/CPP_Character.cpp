// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Character.h"

// Sets default values
ACPP_Character::ACPP_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//캐릭터가 만들어졌는지 확인 (프린트 스트링 = 스크린 메시지)
	if (GEngine) // 사실 없어도 되지만 안전장치로
		GEngine->AddOnScreenDebugMessage
		(-1, 10.0f, FColor::Red, TEXT("Character Spawned!"));

}

// Called when the game starts or when spawned
void ACPP_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACPP_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//조작을 할당 : 이벤트에 함수를 바인딩하듯이 하면 된다

	//이동
	PlayerInputComponent->BindAxis("Legacy_MoveForward", this, &ACPP_Character::MoveForward);
	PlayerInputComponent->BindAxis("Legacy_MoveRight", this, &ACPP_Character::MoveRight);

	//시야
	PlayerInputComponent->BindAxis("Legacy_LookUp", this, &ACPP_Character::LookUp);
	PlayerInputComponent->BindAxis("Legacy_LookRight", this, &ACPP_Character::LookRight);

	//액션(점프와 발사)
	PlayerInputComponent->BindAction("Legacy_Jump", IE_Pressed, this, &ACPP_Character::JumpAction);
	PlayerInputComponent->BindAction("Legacy_Shoot", IE_Pressed, this, &ACPP_Character::ShootAction);
}

void ACPP_Character::MoveForward(float value)
{
	FVector dir = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	APawn::AddMovementInput(dir, value);
}

void ACPP_Character::MoveRight(float value)
{
	FVector dir = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	APawn::AddMovementInput(dir, value);
}

void ACPP_Character::LookUp(float value)
{
	APawn::AddControllerPitchInput(value);
}

void ACPP_Character::LookRight(float value)
{
	APawn::AddControllerYawInput(value);
}

void ACPP_Character::JumpAction()
{
	// 점프는 그냥 캐릭터 기능 그대로 써보기로
	ACharacter::Jump();
}

void ACPP_Character::ShootAction()
{
	// 총 쏘기

	if (bullet)
		// <- 단순히 있는가가 아니라, 언리얼에선 해당 변수에 실제 데이터가 있는지 본다
	{

		// 총알 발사 지점 만들기 (총의 위치를 같이 사용해서)

		// 내 위치 찾기

		FVector location = GetActorLocation();
		FRotator rotation = GetActorRotation();
		
		// (옵션) 또 다른 기준 위치 : 1인칭일 때 사용
		FVector FPLocation;
		FRotator FPRotation;

		GetActorEyesViewPoint(FPLocation, FPRotation);
		// 액터를 조작 중인 컨트롤러,
		// 혹은 카메라가 있으면 해당 카메라의 뷰포트 위치와 회전을 매개변수에 저장하는 함수

		// 위에서 찾은 내 위치 혹은 시야 위치를 기준으로 다시 발사 위치와 각도를 계산

		// 기준 위치, 기준 방향을 원점으로, 총의 벡터만큼 상대 이동을 한 위치
		FVector shootLocation = FPLocation + FTransform(rotation).TransformVector(gunLocation);
		FRotator shootRotation = FPRotation; // 발사 각도는 기준 각도를 그대로 전달 (지금은 기준이 2개라서)

		// 총알 만들기
		// GetWorld()->SpawnActor() : 기본형

		UWorld* world = GetWorld(); // 월드를 미리 포인터로 받기
		if (world) // isValid 원칙상 수행해보기 (어차피 조건문이 실행되는 시점에서 레벨과 액터는 존재할 수밖에 없지만...)
		{
			//액터가 소환될 때 필요한 것들상
			//-클래스 원본
			//-위치와 회전
			//-다음 둘 중 하나 : 스폰 규칙, 혹은 액터의 부가변수(패러미터)

			//총알에게 부가변수 만들어주기
			FActorSpawnParameters spawnParam;
			spawnParam.Owner = this; // 오너 : 생성의 주체, 계층구조 발생시 부모가 될 후보
			spawnParam.Instigator = GetInstigator(); // 추적대상인가? (*추적대상 : 언리얼에서 피해 등 추적 가능한 데이터를 갖춘 대상)
			                                         //GetInstigator : 정해진 기본값
			// 오너와 추적대상 설정 외, 나머지는 변수 생성시 기본값이 정해져 있다 (그리고 보통은 그대로 써도 된다)

			ACPP_Bullet* bulletSpawned = world->SpawnActor<ACPP_Bullet>(
				bullet,
				shootLocation,
				shootRotation,
				spawnParam);

			//생성된 총알을 조작한다면 이제 이 아래서 호출하면 된다
			if (bulletSpawned) // 생성된 총알에 다른 문제가 없다면
			{
				FVector moveDirection = shootRotation.Vector(); // 회전정보의 벡터화
				bulletSpawned->Fire(moveDirection); // C++은 형변환 필요없이 직접 참조호출 가능
			}
		}
	}
}

