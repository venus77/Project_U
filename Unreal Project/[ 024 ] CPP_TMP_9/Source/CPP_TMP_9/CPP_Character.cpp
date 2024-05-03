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
	
	// 총을 생성해서 캐릭터에게 붙여주기 : 필요한 건 스폰 액터
	// GetWorld()->SpawnActor() <- 기본형. 레벨 세계에서 액터 생성 기능 호출

	// 스폰 액터에는 추가로 매개변수들이 필요하다
	// 1. 무엇을 만들 건가 2. 어디에 만들어질 건가
	// 3. 만들 때 어떤 규칙을 적용할 것인가 (스폰 중 규칙, 혹은 스폰 대상의 추가 변수)

	// 스폰 액터에 앞서 대상 액터의 변수부터 미리 규정
	FActorSpawnParameters gunParam;
	gunParam.Owner = this; // Owner : 생성을 수행하는 주체.
	                       // 혹시 부모자식 관계를 설정한다면 1순위로 간주될 후보
	gunParam.Instigator = GetInstigator(); // intigator : 게임에서 추적의 대상하는 대상인지 판별하는 기준자료
	                                       // 여기서는 기본 설정값을 사용한다
	// 따라서 이 코드의 뜻은 "지금 생성하는 액터인 총은 내 물건이고, 게임에 사용되는 아이템이다"

	//총의 원본 클래스에서 총을 만든 후, 헤더에 있던 변수에 할당
	gun = GetWorld()->SpawnActor<ACPP_Gun>(
		gunOrigin,
		gunLocation,
		//GetActorRotation // 액터의 회전 정보 똑같이 주기
		FRotator(0, 0, 0),
		gunParam);

	// 총을 캐릭터에게 붙이기
	gun->EquipTo(this);

	//--------------------------------------

	if (Cast<APlayerController>(GetController()))
		//1. Cast<APlayerController>(GetController()) : GetController의 반환 데이터를 PlayerController 자료형으로 형변환
		// -> (APlayerController)GetController() 이 코드와 뜻이 똑같다. = 다운캐스팅(범용 컨트롤러를 플레이어용으로)
		// -> 다만 Cast를 한 번 붙이면 형변환이 무조건 이루어지지 않고, "가능한 경우"라고 엔진이 판단한 경우만 형변환을 시켜준다
		//2. 이게 조건문이라는 이야기는 결국 "컨트롤러는 있는가?" + "플레이어에게 앱 컨트롤 권한이 있는가?"를 묻는 것
		//  -> GetController의 결과가 없거나, Cast에 의한 형변환이 이루어지지 않으면 이 조건문은 false가 된다
		//1+2. 이 조건문의 목적 : 조작권이 없으면 그냥 설정을 안 하겠단 뜻 (블루프린트에서 IsValid 쓰는 것과 똑같다)
	{
		//그래서 이 실행 범위 안으로 들어왔단 이야기 = 플레이어에게 조작 설정을 붙여줄 수가 있다는 이야기

		// 플레이어 컨트롤러는 다운캐스팅한 현재의 컨트롤러
		APlayerController* playerController =
			Cast<APlayerController>(GetController());

		//해당 컨트롤러의, 향상된 입력과 중계된, 서브시스템에 접근
		UEnhancedInputLocalPlayerSubsystem* subsystem =
			ULocalPlayer::GetSubsystem
			<UEnhancedInputLocalPlayerSubsystem>
			(playerController->GetLocalPlayer());
		//-> 블루프린트의 서브시스템 찾기와 똑같은 과정, 똑같은 결과

		//찾아낸 서브시스템에 키 설정을 추가해주면 된다 (블루프린트와 똑같다)
		subsystem->AddMappingContext(MappingContext, 0);
	}
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

	//PlayerInputComponent->BindAxis
	//("Legacy_MoveForward", this, &ACPP_Character::MoveForward);
	//PlayerInputComponent->BindAxis
	//("Legacy_MoveRight", this, &ACPP_Character::MoveRight);
	//
	//PlayerInputComponent->BindAxis
	//("Legacy_LookUp", this, &ACPP_Character::LookUp);
	//PlayerInputComponent->BindAxis
	//("Legacy_LookRight", this, &ACPP_Character::LookRight);

	// BindAction : 누르고 떼는 입력에 함수를 할당하는 함수
	// 매개변수 두 번째 IE_Pressed : 키를 눌렀을 때 동작한다는 뜻
	//                 IE_Released : 키를 놓으면 동작한다

	//PlayerInputComponent->BindAction
	//("Legacy_Jump", IE_Pressed, this, &ACPP_Character::JumpAction);
	//PlayerInputComponent->BindAction
	//("Legacy_Shoot", IE_Pressed, this, &ACPP_Character::ShootAction);

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (Input != nullptr) // 포인터에 대한 IsValid 노드와 같다
	{
		//향상된 입력에 함수를 바인딩
		Input->BindAction(Input_Move, ETriggerEvent::Triggered, this, &ACPP_Character::EI_Move);
		// 매개변수 : 배정할 입력 액션, 입력을 받을 때의 상황, 함수 실행 주체와 함수의 포인터

		Input->BindAction(Input_Look, ETriggerEvent::Triggered, this, &ACPP_Character::EI_Look);
		Input->BindAction(Input_Shoot, ETriggerEvent::Started, this, &ACPP_Character::EI_Shoot);

		Input->BindAction(Input_Jump, ETriggerEvent::Started, this, &ACharacter::Jump);
		Input->BindAction(Input_Jump, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	}
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
	gun->Fire(bullet);
}

void ACPP_Character::EI_Move(const FInputActionValue& value)
{
	//Get 템플릿 함수를 사용해서 원하는 자료형 추출하기
	FVector2D movementVector = value.Get<FVector2D>();

	if (Controller != nullptr) // IsValid
	{
		//회전 정보
		FRotator rotation = Controller->GetControlRotation(); // 블루프린트의 시야(조작) 회전 받기

		//위에서 받은 회전 정보를 분해해서 요(yaw, 좌우회전) 값만 받기 (블루프린트에서는 우클릭 분해로 진행)
		FRotator yawRotation(0, rotation.Yaw, 0); //x, z 회전정보 0에 요 값만 넣어서 회전벡터 생성

		//FVector forwardDirection = FRotationMatrix(yawRotation).GetScaledAxis(EAxis::X); //입력 감쇠값에 따른 가감속 조절 수치
		FVector forwardDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X); // 0,1만 있는 절대축값 (단위벡터)
		FVector rightDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(forwardDirection, movementVector.Y);
		// 왜 방향은 X고 입력은 Y냐? : 방향이 X인 건 트랜스폼 계산이 그래서. 입력이 Y인 건 우리가 그렇게 설정할 거라서.

		AddMovementInput(rightDirection, movementVector.X);
	}
}

void ACPP_Character::EI_Look(const FInputActionValue& value)
{
	//시야 벡터 추출
	FVector2D lookVector = value.Get<FVector2D>();

	if (Controller != nullptr) // IsValid
	{
		AddControllerPitchInput(lookVector.Y);
		AddControllerYawInput(lookVector.X);
	}
}

void ACPP_Character::EI_Shoot(const FInputActionValue& value)
{
	//매개변수와 무관하게 그대로 총에서 총알 발사
	gun->Fire(bullet);
}

