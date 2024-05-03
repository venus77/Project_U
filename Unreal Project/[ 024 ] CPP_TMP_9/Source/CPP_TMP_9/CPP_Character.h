// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//플레이어 캐릭터에게 향상된 입력을 부여
#include "EnhancedInputComponent.h" // 향상된 입력을 적용하는 컴포넌트 헤더
#include "EnhancedInputSubsystems.h" //향상된 입력을 컨트롤러 사이에서 중계하는 서브시스템
#include "InputActionValue.h"       // 입력에 따른 값들을 모두 받고 호출시켜주는 관리 헤더

//총과 총알
#include "CPP_Gun.h"
#include "CPP_Bullet.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPP_Character.generated.h"

UCLASS()
class CPP_TMP_9_API ACPP_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACPP_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 언리얼에서 코드로 조작을 부여하는 2가지 관행
	// 1. 이벤트가 벌어졌을 때 (On~~~ 코드가 들어오면 조작에 의한 결과를 부여한다) : 비효율적 (언리얼에서도 지침이 아님)
	// 2. 각 조작에 대한 행동을 함수로 미리 정해두고, 입력 액션에 바인딩한다 (이벤트에 함수 포인터 할당) : 효율적 (언리얼 개발 지침)
	//    위에 있는 SetupPlayerInputComponent 함수는 이 2번 관행을 쉽게 하기 위해서 만들어진 것.

	// -> 따라서 여기서도 행동 함수를 만들고 입력 액션에 바인딩

	// 이동 함수
	UFUNCTION() // 언리얼용 함수라는 의미의 (+부가 옵션 설정 가능한) 매크로
				// 꼭 필요하진 않지만, 원칙적으론 앞에 붙여주는 것이 지침이라고 한다
				// 변수의 경우, UPROPERTY()라는 매크로 사용
	void MoveForward(float value);
	//UFUNCTION() void MoveRight(float value); // <- 이렇게 해도 되는데 가시성이 별로
	UFUNCTION()
	void MoveRight(float value);

	// 시야 함수
	UFUNCTION()
	void LookUp(float value);
	UFUNCTION()
	void LookRight(float value);

	// 액션 맵핑 함수
	UFUNCTION()
	void JumpAction(); // <- 캐릭터에 Jump라는 함수가 원래 있고, 오버라이드 불가 = 다른 이름 필요
	UFUNCTION()
	void ShootAction();

	//발사를 위해 필요한 변수

	// 1.총알
	// 2.총알이 나갈 위치
	// 3. (옵션) 총을 쏘는 주체 (자신이어도 상관없지만, 액션 전담 클래스가 있으면 더 좋고)


	//총알
	//UPROPERTY() // UPROPERTY : 데이터가 언리얼에서 사용되는 용도임을 표시
	UPROPERTY(EditAnywhere, Category = Gun, BlueprintReadWrite)
	TSubclassOf<ACPP_Bullet> bullet; // 총알의 원본 클래스 (파생형 포함)
	
	// UPROPERTY 옵션
	//EditAnywhere : 인터페이스 접근 가능시, 언제 어디서든 이 데이터를 수정할 수 있다는 뜻
	//Category : 이 변수가 에디터에서 어떤 분류명으로 구분되는지를 지정하는 것
	//           여기에 이름을 주면 에디터가 이 변수를 해당 그룹으로 관리를 해주고
	//           또한 블루프린트에서 노출시에는 변수를 해당 그룹에서 표시해준다
	//           카테고리 이름은 있는 분류명을 쓰거나, 새로 만들 수 있다
	//           * 있는 이름을 쓰면 본래 분류명에 통합. 지정된 이름이 원래 없었으면 새로 만든다
	//           ** 혹시 분류명을 에디터가 인지하지 못하면, Gameplay로 카테고리 설정할 것
	//BlueprintReadWrite : 이 변수를 블루프린트에서 노출시키고,
	//                     블루프린트 창 안에서 수정 가능하게 만들라는 뜻

	//총
	UPROPERTY(EditAnywhere, Category = Gun, BlueprintReadWrite)
	TSubclassOf<ACPP_Gun> gunOrigin; //총의 원본

	UPROPERTY() // 불필요한 옵션 배제로 최적화
	ACPP_Gun* gun; // 원본을 통해 만들어진 진짜 총

	//총 생성 시 적용할 위치 보정 (구체적인 값은 에디터에서 줄 거지만)
	UPROPERTY(EditAnywhere, Category = Gun, BlueprintReadWrite)
	FVector gunLocation;
	//FVector : 벡터를 소수로 표현했다는 언리얼식 표현 (F 접두사 = float)
	// -> 언리얼에서는 클래스명, 함수명, 변수명 앞에 이렇게 필요에 따라
	//    형식이나 용도를 지정하는 접두사를 붙이곤 한다 (적응합시다!)


	//-----향상된 입력과 IMC 적용-----

	// 입력 액션 데이터를 받아내기 위한 변수 저장
	// (실제 데이터는 에디터에서 만들기 -블루프린트로...-)

	//->변수를 블루프린트로 받아야 하므로 변경 가능한 형태로

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
		UInputMappingContext* MappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
		UInputAction* Input_Move;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
		UInputAction* Input_Look;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
		UInputAction* Input_Jump;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
		UInputAction* Input_Shoot;


	// 입력을 받으면 실행해줄 결과 함수 (쓰든 말든 입력에서 오는 값을 다 받도록)

	UFUNCTION()
		void EI_Move(const FInputActionValue& value);
	// * const FInputActionValue& : FInputActionValue는 입력에서 발행하는 모든 정보를 담은 구조체
	//                              향상된 입력 인터페이스에서는 이 값을 상수로 받아서 처리하도록 지정

	UFUNCTION()
		void EI_Look(const FInputActionValue& value);

	UFUNCTION()
		void EI_Shoot(const FInputActionValue& value);

	// 점프는.... 그냥 캐릭터 점프 쓰려고 합니다....
};
