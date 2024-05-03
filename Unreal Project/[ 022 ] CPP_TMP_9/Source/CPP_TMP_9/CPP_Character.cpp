// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Character.h"

// Sets default values
ACPP_Character::ACPP_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; // 틱(업데이트) 사용 여부

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

	//조작 할당(입력 액션에 함수 바인딩)

	//입력 이벤트에 따른 함수 연결 과정을 코딩으로 재현
	//BindAxis : 축 매핑 바인드
	//매개변수 : 이름 - 입력 액션의 이름
	//          this - 함수 수행의 주체. 블루프린트에서 self였던 것이 여기서는 this
	//          함수의 포인터 - 바인딩하려는 함수

	PlayerInputComponent->BindAxis
	("Legacy_MoveForward", this, &ACPP_Character::MoveForward);
	PlayerInputComponent->BindAxis
	("Legacy_MoveRight", this, &ACPP_Character::MoveRight);

	PlayerInputComponent->BindAxis
	("Legacy_LookUp", this, &ACPP_Character::LookUp);
	PlayerInputComponent->BindAxis
	("Legacy_LookRight", this, &ACPP_Character::LookRight);

	// BindAction : 누르고 떼는 입력에 함수를 할당하는 함수
	// 매개변수 두 번째 IE_Pressed : 키를 눌렀을 때 동작한다는 뜻
	//                 IE_Released : 키를 놓으면 동작한다

	PlayerInputComponent->BindAction
	("Legacy_Jump", IE_Pressed, this, &ACPP_Character::JumpAction);
	PlayerInputComponent->BindAction
	("Legacy_Shoot", IE_Pressed, this, &ACPP_Character::ShootAction);
}

void ACPP_Character::MoveForward(float value)
{
	// 전방 벡터를 구하고, 이에 따라 플레이어를 앞으로 보내기
	FVector dir = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	//FVector : DX의 수학 벡터. F는 구성 숫자가 소수라는 의미
	//FRotationMatrix : DX의 수학 행렬. F는 소수란 뜻, Rotation은 콕 집어서 회전정보를 갖고 있다는 표시
	//Controller : 캐릭터가 현재 갖고 있는 조작구조=컨트롤러
	//GetControlRotation : 이 컨트롤러가 갖고 있는 회전 정보(=카메라가 붙었을 경우, 시야)
	//GetScaledAxis : 현재 주어진 회전정보를 바탕으로 축 방향을 분리
	//EAxis::X : Enum으로 만들어진 축 목록 중에서 X축. 캐릭터의 경우, X축이 전후의 역할
	// 따라서... 위 코드를 결론 지으면 : "현재 보고 있는 방향 기준으로 전후 축만 벡터로 구하기" = 전방 벡터
	// 블루프린트의 Get Control Rotation > Get Forward Vector 노드와 똑같은 의미

	// 이동 입력 추가 함수를 호출해서 플레이어를 간단히 이동 가능
	// -> C++ 코드에서는 이 함수의 호출 주체가 (이동 컴포넌트나 컨트롤러가 아니라)
	//    폰이라는 것이 차이
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
	ACharacter::Jump(); //캐릭터 부모 클래스가 가진 점프 그대로 쓰기
}

void ACPP_Character::ShootAction()
{
}

