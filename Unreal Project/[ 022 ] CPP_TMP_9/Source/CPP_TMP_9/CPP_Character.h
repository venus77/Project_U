// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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

};
