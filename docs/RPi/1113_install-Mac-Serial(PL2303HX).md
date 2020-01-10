# MacOS용 USB Serial 드라이버 설치
> 예시는 <i><b>PL2303HX</b></i> 기준임

1. USB Serial 드라이버 다운로드후 설치
   1. [PL2303HX 다운로드 사이트](https://plugable.com/drivers/prolific/)(https://plugable.com/drivers/prolific/)에서 Mac OS 버전에 맞는 드라이버 다운로드하여 설치
   2. USB Serial 디바이스를 MAC USB 포트에 삽입
   3. Mac 재부팅

2. USB Serial Controller 정상 확인
   1. 'Apple' 심볼 > '이 Mac에 관하여' > '시스템 리포트' 버튼 클릭
   2. '하드웨어' > 'USB' > 'USB 기기 트리'에서 'USB 버스' > 'USB-Serial Controller' 선택후 '제조업체' 확인
      * 'PL2303HX'인 경우 'Prolific Technology Inc.'로 나옴
      * 'USB-Serial Controller'가 안 나오는 경우는 USB Serial Device를 꽂지 않고 부팅했거나 드라이버가 안 맞는 경우임
   3. '유틸리티' > '터미널' 실행후 tty 확인 
      <pre><code>$ <b><u><i>ls /dev/tty.*</i></u></b>&lt;Enter&gt;
      /dev/tty.Bluetooth-Incoming-Port	<b>/dev/tty.usbserial</b></code></pre>
      * '/dev/tty.usbserial'이 나오지 않을 경우
        1. '시스템 환경설정' > '보안 및 개인 정보 보호' 선택
           * Lock이 걸려 있으면 Lock 해제
        2. '"Prolific ..." was blocked from loading.'에 있는 '승인' 버튼 클릭
           * Lock이 해제되어 있으며 Lock 처리
