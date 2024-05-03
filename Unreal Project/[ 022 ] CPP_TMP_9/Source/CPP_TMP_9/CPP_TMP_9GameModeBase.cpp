// Copyright Epic Games, Inc. All Rights Reserved.


#include "CPP_TMP_9GameModeBase.h"

void ACPP_TMP_9GameModeBase::StartPlay()
{
    // 사용자 정의된 게임 시작 함수
    // 만약 이 코드가 직접 호출된다면 (게임을 개발자가 수동한 시작했다면)
    // ....아래 코드가 수행될 것

    //1. 본래의 게임 시작 절차를 (문제 없도록) 수행
    Super::StartPlay();
    // Super : 부모 클래스를 의미
    // 부모의 동명 함수를 수행 = 오버라이드된 상태에서 함수를 다시 정의하는 데 따른 책임

    //2. 로그 찍어보기

    if (GEngine) // GEngine : 게임 실행 엔진. 조건문의 뜻은 "게임 정상 실행 중인가?"
    {
        // 언리얼 기본 로그
        UE_LOG(LogTemp, Log, TEXT("Hello, world!"));
        //UE_LOG : 엔진에 출력 로그를 띄우는 기본적인 텍스트 출력 매크로 함수
        //매개변수 : LogTemp - 로그의 분류명 (설정된 것을 쓰거나 임의설정 가능)
        //          Log - 로그의 용도분류 (에디터 인식용)
        //          TEXT - 실제 텍스트 내용. 문자열

        // 화면 출력용 (개발자 확인용) 로그 - 블루프린트의 Print~~~와 같다
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("Game Started!"));
        //AddOnScreenDebugMessage : 화면에 로그를 띄운다. 가시성 확실, 휘발성이 높다
        //매개변수 : 첫 숫자 - 해당 메시지에 부여한 키(키에 따라 분류 관리 가능, -1은 "키 없음")
        //          다음 숫자 - 메시지가 출력되는 시간
        //          FColor - 메시지 색깔. 앞에 붙은 F는 소수의 F(float)
        //          TEXT - 실제 텍스트 내용. 코드에서 사용하면 문자열
    }
}
