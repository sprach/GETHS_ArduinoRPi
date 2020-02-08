# Windows 10용 USB Serial 드라이버 설치
> 예시는 <i><b>PL2303HX</b></i> 기준임

1. USB Serial Device를 Windows USB 포트에 삽입
   1. '시작'(윈도 심볼)을 우마우스 클릭 &gt; '장치 관리자' 선택
   2. '포트(COM && LPT)' 클릭하여 확장
   3. COM Port 확인
      * 'PL2303HXA PHASED OUT SINCE 2012. PLEASE CONTACT YOUR SUPPLIER.' 나올시 기존 드라이버 제거(단계 2) 및 새 드라이버 설치(단계 3) 작업이 필요함
      * 포트명 앞에 경고 아이콘이 있을 경우에도 단계 2와 3의 작업이 필요함

2. USB Serial 드라이버 제거
   1. 장치 관리자 &gt; 포트(COM && LPT)의 COM 포트를 우마우스 클릭하여 '디바이스 제거' 선택
   2. '이 장치의 드라이버 소프트웨어를 삭제합니다.' 선택
   3. '제거' 버튼 클릭
   4. 단계 3.로 가서 드라이버 프로그램 설치

3. USB Serial 드라이버 다운로드후 설치
   1. USB Serial Device를 USB 포트에서 제거
   2. https://kitschool.tistory.com/130 에서 드라이버 다운로드 및 드라이버 프로그램 설치
   3. 단계 1.로 이동하여 COM 포트 확인
