# Windows 8 이하 USB Serial 드라이버 설치
> 예시는 <i><b>PL2303HX</b></i> 기준이며 테스트 진행을 하지 않아 정상 동작은 보장 못함

1. USB Serial Device를 Windows USB 포트에 삽입
   1. '시작'(윈도 심볼)을 우마우스 클릭 &gt; '장치 관리자' 선택
   2. '포트(COM && LPT)' 클릭하여 확장
   3. COM Port 확인
      * 포트명 앞에 경고 아이콘이 있을 경우 기존 드라이버 제거(단계 2) 및 새 드라이버 설치(단계 3) 작업이 필요함

2. USB Serial 드라이버 제거
   1. 장치 관리자 &gt; 포트(COM && LPT)의 COM 포트를 우마우스 클릭하여 '디바이스 제거' 선택
   2. '이 장치의 드라이버 소프트웨어를 삭제합니다.' 선택
   3. '제거' 버튼 클릭
   4. 단계 3.로 가서 드라이버 프로그램 설치

3. USB Serial 드라이버 다운로드후 설치
   1. USB Serial Device를 USB 포트에서 제거
   2. 드라이버 설치
      1. 자동 업데이터
         1. <i><b>장치 관리자</b></i> &gt; <i><b>기타 장치</b></i> &gt; <i><b>USB-Serial Controller</b></i> 확인
         2. <i><b>USB-Serial Controller</b></i>에서 우마우스 클릭 &gt; <i><b>드라이버 업데이트</b></i> &gt; <i><b>업데이트된 드라이버 소프트웨어 자동 검색</b></i> 선택으로 설치
         3. '닫기' 버튼 클릭
      2. 수동 업데이트
         1. [PL2303HX 다운로드 사이트](https://plugable.com/drivers/prolific/)(https://plugable.com/drivers/prolific/)에서 드라이버 다운로드
         2. 다운로드 받은 파일(<i><b>PL2303-Prolific_DriverInstaller_v&lt;<i>nnnn</i>&gt;.exe</b></i>)을 실행하여 설치
   3. 단계 1로 이동하여 COM 포트 확인
