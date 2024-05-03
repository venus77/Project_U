// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Bullet.h"

// Sets default values
ACPP_Bullet::ACPP_Bullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 생성과 동시에 형태 잡기

	collision = CreateDefaultSubobject<USphereComponent>(TEXT("Bullet Mesh"));
	// CreateDefaultSubobject : 컴포넌트 계층구조에 디폴트 밑으로 하위 컴포넌트 만들기
	//                          (디폴트가 없었으면 처음 호출된 대상이 디폴트가 된다)
	//                          * 모든 엔진은 컴포넌트가 만들어질 때 이름이 필요하다

	collision->InitSphereRadius(10.0f); // 구체의 반지름을 지정하는 함수

	RootComponent = collision; // 계층구조의 루트 컴포넌트를 (구체로) 지정

	// 움직임 설정

	movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Bullet Movement"));

	movement->SetUpdatedComponent(collision); // 업데이트 계층 지정 가능 (실제 모양에 움직임이 따라가게)

	movement->InitialSpeed = 3000.0f;
	movement->MaxSpeed = 3000.0;
	movement->bRotationFollowsVelocity = true; //이동 방향에 물체의 회전정보가 맞춰지게
	movement->bShouldBounce = true; // 부딪치면 튀어나올 것인가?
	movement->Bounciness = 3.0;

	// 맞았을 때 이벤트 바인딩
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
	movement->Velocity = direction * (movement->InitialSpeed);

}

void ACPP_Bullet::OnHit(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& Hit)
{
}

