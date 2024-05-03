// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
//#include "Engine/Engine.h" // <- 바로 문제 발생 x, 현 세대 지침상 비권장
//#include "Engine.h" // <- 바로 문제 발생
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_Bullet.generated.h"

UCLASS()
class CPP_TMP_API ACPP_Bullet : public AActor
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

	//총알의 움직임과 관련 함수들

	UFUNCTION() // 발사시 전방 이동하기
		void Fire(FVector direction);

	UFUNCTION() // 나중에 사용할 히트시 이벤트 미리 지정
		void OnHit(UPrimitiveComponent* hitComp,
			AActor* otherActor, UPrimitiveComponent* otherComp,
			FVector normalImpulse,
			const FHitResult& Hit);

	// 총알의 움직임
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UProjectileMovementComponent* movement;

	// 총알의 생김새
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USphereComponent* collision;
};
