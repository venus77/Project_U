// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CPP_TMPGameModeBase.generated.h"

/**
 * 
 */
UCLASS() //<-UCLASS : 언리얼 연동용 매크로, "이것은 언리얼용 클래스입니다."
		 // () : 언리얼용 매크로의 특징, 매개변수를 추가 설정해서 옵션 확장 가능
class CPP_TMP_API ACPP_TMPGameModeBase : public AGameModeBase
		//클래스 이름 앞에 붙은 A : 언리얼에서 액터의 기능을 받아 만들었다는 의미
{
	GENERATED_BODY() // 언리얼에서 실체가 생성될 수 있음을 나타내는 매크로

	// BeginPlay에 대응하는 코드상의 시작 함수 (두 번째 생성자와 같은)
	virtual void StartPlay() override;
};
