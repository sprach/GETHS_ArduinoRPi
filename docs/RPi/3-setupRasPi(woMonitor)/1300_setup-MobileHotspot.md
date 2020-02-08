# 모바일 Hotspot 이용
1. 스마트폰의 Hotspot(모바일 핫스팟) 켜기
2. [Windows Tera Term 설치](./1121_install-Win-TeraTerm.md)
3. WiFi 접속을 위한 <i><b>wpa_supplicant.conf</b></i> 파일을 MicroSD의 boot에 복사해 넣기
4. 접속할 WiFi AP의 <i><b>ssid</b></i>와 <i><b>비밀번호</b></i>를 입력하고 저장
    <pre><code>country=GB
    ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
    update_config=1

    network={
        ssid="&lt;ssid-name&gt;"
        psk="&lt;password&gt;"
    }</code></pre>
5. MicroSD를 라즈베리파이에 삽입후 라즈베리파이 전원 연결
