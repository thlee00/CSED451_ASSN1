# CSED451 Computer Graphics Assignment1
## 팀 소개
### Team name: 주단태
### Team member
- 이태희, 20190829, 컴퓨터공학과, thlee00
- 주의손, 20190879, 컴퓨터공학과, uison1229

## 프로그램 기능 개요
- 모바일 게임 ‘Wind Runner’와 유사한 달리기 게임을 만든다.
- 캐릭터는 자동으로 앞으로 달려나가며, 유저는 오직 점프 조작만 할 수 있다.
- 바닥의 구멍을 점프로 회피하지 못하면 게임은 종료된다.
- 전방에서 날아오는 파이어볼을 회피하지 못하면 게임은 종료된다.
- 랜덤한 높이에 생성되는 코인을 획득하면 스코어가 증가한다.

## 프로그래밍 환경
- Visual Studio 2019
- C++
- GLUT 3.7.6 (http://user.xmission.com/~nate/glut.html)

## 프로그램 디렉토리 파일
``` 
|--assn1
  |--include
  | `--GL
  |   `--glut.h
  |
  |--lib
  | `--glut32.lib
  |
  |--glut32.dll
  |--main.cpp
  |--map.cpp
  |--map.h
  |--obj.cpp
  `--obj.h
```

- include/GL/glut.h, lib/glut32.lib glut32.dll: GLUT (3.7.6 ver)
- main.cpp: 프로그램 메인 구동이 담긴 코드
- map.h, map.cpp: 맵 구성과 캐릭터 이동, 오브젝트 생성 알고리즘이 담긴 코드
- obj.h, obj.cp: 지표면 블록, 파이어볼, 코인, 캐릭터 등의 오브젝트 클래스를 정의하고 상속하는 코드

## 실행 방법
1. repository clone
2. Visual Studio 2019 solution 파일 (assn1.sln) 실행
3. F5 키로 code complie
4. 콘솔에서 게임 시작
5. 코인 획득 시 점수 상승
6. 구덩이나 파이어볼을 피하지 못하면 프로그램 종료