// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Bullet.h"

// Sets default values
ACPP_Bullet::ACPP_Bullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 생성과 동시에 충돌 영역을 지정

	collision = CreateDefaultSubobject<USphereComponent>(TEXT("Bullet Collision"));
	//CreateDefaultSubobject : 컴포넌트를 생성해서 아래로 붙이기
	//                         중간의 디폴트는 "이 컴포넌트를 디폴트(루트) 밑으로 붙이되,
	//                         루트가 없었던 경우는 이게 루트다"라는 뜻이다
	//                         더불어서 모든 컴포넌트는 만들어질 때 이름이 필요하다 (TEXT)

	collision->InitSphereRadius(10.0f); // 구체의 반지름 지정하기

	//지금 만든 충돌 영역을 아예 루트로 확정하려면
	RootComponent = collision; // 계층구조 내의 루트를 직접 지정

	// 움직임 설정

	movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Bullet Movement"));

	movement->SetUpdatedComponent(collision); // *예외주의 : 블루프린트에는 없었음*
										      // 발사체 이동 기능이 충돌과 업데이트를 동기화하게 하는 기능

	//발사체 이동 옵션 (블루프린트 때와 동일)
	movement->InitialSpeed = 3000.0f;
	movement->MaxSpeed = 3000.0f;
	movement->bRotationFollowsVelocity = true; // 이동 방향에 물체 회전이 따라가게
	movement->bShouldBounce = true; // 히트 발생 시 튀어나오는가?
	movement->Bounciness = 3.0; // 통통 튀게

	//충돌에 의한 히트 이벤트 발생시, 클래스에 있는 OnHit 함수를 바인딩
	collision->OnComponentHit.AddDynamic(this, &ACPP_Bullet::OnHit);
}

// Called when the game starts or when spawned
void ACPP_Bullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_Bullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_Bullet::Fire(FVector direction)
{
	//발사체 이동 컴포넌트에 매개변수로 받은 방향을 속도화해서 전해주면 된다
	movement->Velocity = direction * (movement->InitialSpeed);
	//-> 매개변수의 벡터 변화(방향) x 속력 = 속도
}

void ACPP_Bullet::OnHit(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& Hit)
{
}

