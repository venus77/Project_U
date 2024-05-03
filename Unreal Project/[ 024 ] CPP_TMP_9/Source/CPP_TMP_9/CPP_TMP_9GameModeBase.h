// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CPP_TMP_9GameModeBase.generated.h"

/**
 * 
 */
UCLASS() // 언리얼의 라이브러리 매크로. 이 코드가 언리얼에서 쓰이는 용도임을 확인시키는 매크로
		 // 더불어 () 안에 미리 정해진 키워드를 입력하면 부가 옵션을 설정할 수 있다
class CPP_TMP_9_API ACPP_TMP_9GameModeBase : public AGameModeBase
		 // 클래스 이름 앞의 A : 언리얼의 코딩 문법. 이 클래스가 어떤 형태로 구분되는지 에디터에 알려준다
		 // 구분용 대문자를 앞에 적어줘야 에디터가 인식을 할 수 있다. 코드 에디터에서 파일을 만들 경우 주의
{
	GENERATED_BODY() // 언리얼용 매크로. 레벨 내에서 생성될 수 있는 대상임을 나타낸다

	//이 프로젝트에서 코딩이 가능함을 확인하기 위한 실제 게임 규칙 사용
	//->수동으로 게임을 시작해보기 (=게임 시작 함수를 내 손으로 호출)

	virtual void StartPlay() override; // 게임 시작 함수
};
