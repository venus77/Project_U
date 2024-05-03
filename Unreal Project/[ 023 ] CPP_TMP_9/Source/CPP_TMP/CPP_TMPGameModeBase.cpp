// Copyright Epic Games, Inc. All Rights Reserved.


#include "CPP_TMPGameModeBase.h"

void ACPP_TMPGameModeBase::StartPlay()
{
    //BeginPlay 시작

    //부모 클래스로서 게임(을 규칙에 따라) 실행하기
    Super::StartPlay();

    //에디터에 의한 강제실행이 아니라 코딩에 의해 의도된 실행임을 확인하기 위한 로그
    
    if (GEngine) // <-에디터 혹은 빌드가 실행 중이면
    {
        UE_LOG(LogTemp, Log, TEXT("Hello, world!"));
        // UE_LOG : 기본적인 언리얼 로그 함수 매크로
        // 매개변수 : LogTemp - 이유 없는 임시 로그란 뜻.
        //           이 외에 에러 메시지, 각 용도에 따른 메시지 설정이 있다
        //           Log - 메시지의 유형 분류
        //           TEXT - 실제 메시지

        GEngine->AddOnScreenDebugMessage
            (-1, 5.0f, FColor::Purple, TEXT("This is a Game!"));
        // GEngine->AddOnScreenDebugMessage : 에디터 개발자용 기능으로 디버그 메시지 띄우기
        // ...사실상 로그와 비슷하다고 보면 된다 (용도 구분보다는 색깔 구분으로 가시성이 높다)
        // 매개변수 : 첫 번째 숫자 - 메시지의 키 (구분)
        //           두 번째 숫자 - 메시지 출력 시간
        //           색깔 enum - 메시지 색깔
        //           TEXT() - 실제 메시지
    }
}