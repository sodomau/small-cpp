---
title: 데이터와 기능 함께 묶기
part: types
part-title: Part V — 나만의 자료형 만들기
goal: 데이터와 기능 함께 묶기
related-example: programs/bouncing_ball
---

## 이번에 배울 것

**class**는 데이터와 그 데이터를 다루는 기능을 묶는 타입입니다. **객체**는 그 타입으로 만든 실제 대상입니다. 이런 도구도 직접 만들 수 있다는 정도로 살펴봅니다.

## 실행해 보기

@code example1.cpp

Counter 객체는 자신이 센 값 value를 가집니다. AddOne을 두 번 호출하고 Value를 읽으면 2입니다.

public은 사용하는 쪽에 공개한 부분, private은 바깥에서 직접 접근하지 못하게 한 부분입니다. String이나 Window도 데이터와 관련 기능을 가진 객체로 사용해 왔습니다. 이번에는 생성자나 상속까지 배우지 않습니다.

## Exercise — Counter에 Reset 추가

Counter class에 값을 0으로 만드는 public `Reset()`을 추가하고 동작을 확인하세요.

@exercise exercise1_starter.cpp

### Hint

Reset 안에서 private value에 0을 대입하세요.

@solution exercise1_solution.cpp

