// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CPP_Gun.h"
#include "CPP_Bullet.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPP_Character.generated.h"

UCLASS()
class CPP_TMP_API ACPP_Character : public ACharacter
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

	// 위 함수가 시작시 조작을 할당할 설정 함수
	// 그리고 아래쪽은 해당 조작 할당에 사용할 실제 행동 함수

	// 이동

	UFUNCTION() // 에디터에서도 사용하는 언리얼 함수임을 표시 (+원하면 추가 옵션도)
	void MoveForward(float value);
	
	UFUNCTION()
	void MoveRight(float value);
	
	UFUNCTION()
	void LookUp(float value);
	
	UFUNCTION()
	void LookRight(float value);

	// 점프와 발사

	UFUNCTION()
	void JumpAction();

	UFUNCTION()
	void ShootAction();

	// 쏘기에 사용하기 위한 부가 데이터 (총알과 총 쏘기 액션 클래스)
	//UPROPERTY() //언리얼에서 쓰는 데이터임을 나타내는 매크로 + 부가 옵션 설정
	UPROPERTY(EditAnywhere, Category = Gun, BlueprintReadWrite)
	FVector gunLocation; // FVector : 언리얼 라이브러리 내 벡터 표시

	//ACPP_Bullet bullet; // C++ 안에서 클래스 안에만 접근 가능한 선언
					      // 언리얼에선 클래스를 재참조 대상으로 한번 더 가공해줘야
	UPROPERTY(EditAnywhere, Category = Projectile, BlueprintReadWrite)
	TSubclassOf<class ACPP_Bullet> bullet;
	// 단순 클래스가 아니라 클래스를 참조하는 데이터 및 상속된 클래스까지 대상으로 지칭

	// * 위 UPROPERTY에서 사용한 매크로 내 부가 옵션
	//   -> 해당 데이터가 블루프린트화되었을 때 어떻게 취급될지를 규정한 것

	// EditAnyWhere : 언제 어디서든 (보이면) 편집할 수 있다는 뜻
	// BlueprintReadWrite : 블루프린트 환경 내에서 이 데이터가 노출되고,
	//                      따라서 수정할 수 있다는 뜻
	// Category = 블루프린트 환경에서 데이터가 어느 분류칸에 나올지를 정하는 것
	//            에디터에 주어진 분류명을 쓰거나, 임의로 새로운 분류를 만들 수 있다
	//            혹시 안 나오는 분류명이 있으면, Gameplay로 카테고리를 정하면 된다
};
