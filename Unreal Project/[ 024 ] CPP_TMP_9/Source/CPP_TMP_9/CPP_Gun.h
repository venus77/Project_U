// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_Gun.generated.h"

UCLASS()
class CPP_TMP_9_API ACPP_Gun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_Gun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void Fire(class TSubclassOf<ACPP_Bullet> bulletOrigin);

	//아래 함수는 캐릭터 생성시 딱 한번만 쓰고, 게임에서 안 쓰고 싶어서 그냥 U함수 아님
	//=재사용 필요성이 생기면 U함수로 만들어야 한다
	void EquipTo(AActor* parent);
};
