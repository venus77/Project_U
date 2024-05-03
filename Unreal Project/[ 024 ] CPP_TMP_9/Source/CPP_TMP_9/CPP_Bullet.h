// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Engine.h" // <- 전체 엔진 총괄 헤더. 더는 쓰지 않는다 (쓰면 에디터가 억까를 한다)
//#include "Engine/Engine.h" //<-위와는 다른 에디터 내부 명령어 헤더. 역시 더는 쓰지 않는다
							 // (당장은 문제가 없지만, 역시 쓸수록 문제가 생긴다)

// 버전 4.25 이후부터 위 헤더들을 쓰지 못하게 방해하는 이유
// 1. 데이터 보안 문제 (쓰지도 않을 건데 너무 많은 접근권을 가져가는 걸 언리얼 개발자들이 싫어한다)
// 2. 컴파일 시간의 문제 (오래 걸린다)
// 3. 실행 시간의 문제 (정도의 차이는 있지만, 어쨌든 오래 걸린다)
// -> 현재의 지침은 딱 자기가 쓰려는 클래스에 해당하는 헤더만 인클루드하라고 한다 (IWYU)
// -> 복습이나 중도 개발이라면 Engine/Engine.h까지는 아마 써도 괜찮겠지만...
//    결국 빌드를 목적으로 하는 개발이라면 이것조차 마지막엔 다 빼줘야 오류 확률을 낮출 수 있다

// 위의 지침을 지켜서 본 클래스에서 언리얼의 추가 기능을 사용하려면?
// -> 레퍼런스 페이지, 혹은 클래스 검색

#include "GameFramework/ProjectileMovementComponent.h" // 발사체 이동 컴포넌트
#include "Components/SphereComponent.h" // 구체 모양 컴포넌트

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_Bullet.generated.h"

UCLASS()
class CPP_TMP_9_API ACPP_Bullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_Bullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 움직임과 관련 함수

	UFUNCTION()
		void Fire(FVector direction);

	UFUNCTION()
		void OnHit //ON~~~ : 이벤트 발생 시에 처리할 함수라는 의미를 작명에 담는다
		(UPrimitiveComponent* hitComp, //부딪친 부위
			AActor* otherActor, //부딪친 표적
			UPrimitiveComponent* otherComp, // 표적에서 부딪친 부위
			FVector normalImpulse, //히트 시에 발생한 반발 방향(=부딪친 위치의 법선)
			const FHitResult& Hit //기타 부딪친 결과를 기록한 구조체
		);

	// 총알의 움직임
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UProjectileMovementComponent* movement;

	// 총알의 생김새 (충돌 영역)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USphereComponent* collision;
};
