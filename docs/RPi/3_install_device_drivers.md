# 디바이스 드라이버 파일 설치

  ## GPIO 라이브러리 설치
  <pre><code>$ sudo apt-get install rpi.gpio rpi.gpio-common</code></pre>
  
  ## gpiozero
  * gpiozero는 GPIO를 함수화시킨 라이브러리
  1. Raspbian
     <pre><code>$ sudo apt install python3-gpiozero</code></pre>
  2. Non-raspbian
     <pre><code>$ sudo pip3 install gpiozero</code></pre>

  ## BlueDot
  * 안드로이드폰에서 라즈베리파이를 조정하는 패드 역할
    * [BlotDot Site](https://bluedot.readthedocs.io/) : https://bluedot.readthedocs.io/
  1. 라즈베리파이에 파이썬 라이브러리 BlueDot 설치
     <pre><code>$ sudo pip3 install bluedot</code></pre>
  2. 안드로이드 Play 스토어에서 BlueDot 앱 설치
     * [Martin O'Hanlon](https://play.google.com/store/apps/details?id=com.stuffaboutcode.bluedot&hl=ko) : https://play.google.com/store/apps/details?id=com.stuffaboutcode.bluedot&hl=ko

  ## Logitech C270
  1. guvcview webcam viewer 설치
     <pre><code>$ sudo apt-get install guvcview</code></pre>
  2. 퍼미션 설정 및 드라이버 활성화
     <pre><code>$ sudo usermod -a -G video pi
     $ sudo modprobe uvcvideo</code></pre>
  3. Reboot
     <pre><code>$ sudo reboot</code></pre>
  4. WebCam 작동전 고려 사항
     1. WebCam을 파워온시 연결해 놓은 경우
        - 별도의 작업 필요하지 않음
     2. 라즈베리파이 전원을 On 시킨 이후에 WebCam을 연결한 경우에는 아래 스크립트를 먼저 실행해 주어야 한다.
        <pre><code>$ sudo rmmod uvcvideo
        $ sudo modprobe uvcvideo</code></pre>
  5. WebCam 실행
     * 라즈베리파이 아이콘 &gt; Sound &amp; Video &gt; guvcview

  ## 자이로 및 가속도 센서
  * https://kingtidesailing.blogspot.com/2016/02/how-to-setup-mpu-9250-on-raspberry-pi_25.html

  1. 센서 설정
     
     1. i2c 활성화
        <pre><code>$ sudo raspi-config
        <b><i><u>5 Interfacing Options</u></i></b> &gt; <b><i><u>P5 I2C</u></i></b> &gt; <b><i><u>Yes</u></i></b> &gt; <b><i><u>Ok</u></i></b> &gt; <b><i><u>Finish</u></i></b></code></pre>
        > 필요시 재부팅
     
     2. 다운로드와 설치
        1. i2c
           <pre><code>$ sudo apt-get install i2c-tools
           $ sudo i2cdetect -y 1
           0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
           00:          -- -- -- -- -- -- -- -- -- -- -- -- -- 
           10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
           20: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
           30: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
           40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
           50: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
           60: -- -- -- -- -- -- -- -- 68 -- -- -- -- -- -- -- 
           70: -- -- -- -- -- -- -- --
           </code></pre>
           > <b><i><u>68</u></i></b>은 센서의 기본 주소이다.
       
        3. Ellipsoid Fit Calibration
           <pre><code>$ sudo apt-get install octave
           ...
           계속 하시겠습니까? [Y/n] &lt;Enter&gt;
           ...
           $ </code></pre>
       
        4. RTIMULib library
           <pre><code>$ cd ~
           $ mkdir kts
           $ cd kts
           $ git clone https://github.com/richards-tech/RTIMULib2.git
           $ cd RTIMULib2/Linux/RTIMULibCal
           $ make -j4
           $ sudo make install
           $ cd ~
           $ ln -s ~/kts/RTIMULib2/RTEllipsoidFit ~/kts/RTEllipsoidFit
           $ cd ~/kts/RTEllipsoidFit
           $ </code></pre>
       
        6. 설정
           1. /etc/modules 에 아래 내용 추가 (없을 경우에 한함)
              <pre><code><b><i><u>i2c-dev
              i2c-bcm2708</u></i></b></code></pre>
        
           2. /etc/udev/rules.d/90-i2c.rules 에 아래 내용 추가
              <pre><code><b><i><u>KERNEL=="i2c-[0-7]",MODE="0666"</u></i></b></code></pre>
     
           3. /boot/config.txt 에 아래 내용 추가
              <pre><code><b><i><u>dtparam=i2c1_baudrate=400000</u></i></b></code></pre>
           
           4. 재부팅
              <pre><code>$ sudo reboot</code></pre>
     
     3. Calibrating the MPU-9250
        1. RTIMULibCal 실행
           <pre><code>$ cd ~/kts/RTEllipsoidFit
           $ RTIMULibCal</code></pre>
           1. 'm' 키를 누른후 값이 안정되면 's' 키를 누른다.
           2. 'e' 키를 눌러서 타원체를 교정한다. 많은 숫자가 몇 분에 걸쳐서 표시되다가 자동으로 중단된다.
           3. 'a' 키를 눌러서 가속도계를 교정한다.
              1. (*중요*)... 내용 확인 필요함!!!
              2. x 축 센서 가속도계 보정, 'e'를 눌러 활성화, 'd'를 눌러 비활성화
              3. 'x'를 눌러서 종료
     
         2. 'RTIMULib.ini' 파일을 작업 디렉토리에 복사해야 한다.
     
  2. 테스트

  # 적외선 거리측정 (PDS)
  1. Sharp 2Y0A21
     * 참조 사이트
       * [Infrared Distance Measurement with the Raspberry Pi (Sharp GP2Y0A02YK0F)](https://tutorials-raspberrypi.com/infrared-distance-measurement-with-the-raspberry-pi-sharp-gp2y0a02yk0f/)
       * [블로그: 적외선 거리측정센서 (sharp 2Y0A21)사용 예제](https://m.blog.naver.com/PostView.nhn?blogId=boilmint7&logNo=220927816896&proxyReferer=https%3A%2F%2Fwww.google.com%2F)
       * [PDF: Datasheet GP2Y0A02YK0F](https://global.sharp/products/device/lineup/data/pdf/datasheet/gp2y0a21yk_e.pdf)
  2. 사전 작업
     1. SPI 활성화
        <pre><code>$ sudo raspi-config
        <b><i><u>Menu &gt; 5 Interfacing Options &gt; P4 SPI &gt; Yes &gt; Ok &gt; Finish</u></i></b></code></pre>
     2. /etc/modules 의 마지막 라인에 'spi-bcm2807' 추가
        <pre><code>$ sudo vi /etc/modules
        <b><i><u>spi-bcm2807</u></i></b></code></pre>
     3. spidev 라이브러리 설치
        <pre><code>$ git clone git://github.com/doceme/py-spidev
        $ cd py-spidev
        $ sudo python3 setup.py install</code></pre>

