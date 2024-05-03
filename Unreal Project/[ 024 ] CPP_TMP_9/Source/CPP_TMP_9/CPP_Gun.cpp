// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Gun.h"
#include "CPP_Bullet.h" // 여기서 총알 클래스 읽기 (헤더에서 인클루드하지 않은 건 여기서 하면 된다)

// Sets default values
ACPP_Gun::ACPP_Gun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPP_Gun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_Gun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_Gun::Fire(TSubclassOf<ACPP_Bullet> bulletOrigin)
{
	// 총알을 발사한다 = 총알 액터를 스폰한다
	// (나가는 건 총알이 지 혼자 알아서 날아가면 된다)

	// 스폰에 필요한 건 : 1. 원본. 2. 트랜스폼(을 구성하는 위치와 회전) 3. 규칙
	// 원본은 매개변수로 받은 상황

	// 위치와 회전 = 총은 이미 만들어졌으니 그 총의 위치와 회전을 그대로 주면 된다
	FVector shootLocation = GetActorLocation();
	FRotator shootRotation = GetActorRotation();

	//스폰 (대상) 규칙
	FActorSpawnParameters spawnParam; // 총에서 스폰할 액터는 총알뿐이라...
	spawnParam.Owner = this;
	spawnParam.Instigator = GetInstigator();

	// 조금 더 안전성 지침에 맞게 (블루프린트로 치자면 IsValid 사용)
	// 레벨 접근 후 스폰 액터를 사용

	UWorld* world = GetWorld();

	if (world) // 레벨이 정상 로딩 중이라면
	{
		//총알 만들기
		ACPP_Bullet* bulletSpawned = world->SpawnActor<ACPP_Bullet>(
			bulletOrigin,
			shootLocation,
			shootRotation,
			spawnParam);

		//총알이 정상적으로 만들어졌다면 (총알에 IsValid 쓰는 상황)
		if (bulletSpawned)
		{
			FVector moveDirection = shootRotation.Vector(); //로테이터 안에 벡터 변환 함수 있음
			bulletSpawned->Fire(moveDirection);
			// 생성과 진행 코딩이 끝난 총알에, 발사 함수를 호출 후 방향 전달하면 끝
		}
	}
}

void ACPP_Gun::EquipTo(AActor* parent)
{
	AttachToActor(
		parent, // 부모 트랜스폼
		FAttachmentTransformRules::KeepRelativeTransform); // 상대 트랜스폼 유지
}

