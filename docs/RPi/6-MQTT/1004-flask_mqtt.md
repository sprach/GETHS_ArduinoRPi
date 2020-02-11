# Flask로 MQTT 테스트

## 파이썬용 MQTT 라이브러리 설치
<pre><code>$ sudo pip3 install paho-mqtt</code></pre>

## 웹페이지
1. Flask 웹 폴더 생성
   <pre><code>$ cd ~
   $ mkdir webapp_mqtt
   $ cd webapp_mqtt
   $ mkdir templates</code></pre>

2. 소스 작성
   <pre><code>$ cd ~/webapp_mqtt</code></pre>
   [소스 보기: mainMqtt.py](../../../src/Rpi/FlaskMQTT/NodeMCU/mainMqtt.py)<br/>
   [소스 보기: templates/mainMqtt.html](../../../src/Rpi/FlaskMQTT/NodeMCU/templates/mainMqtt.html)

3. 실행
   <pre><code>$ cd ~/webapp_mqtt
   $ python3 mainMqtt.py</code></pre>

4. 테스트
   1. PC에서 웹 브라우저를 실행한다.
   2. 주소 칸에 '&lt;라즈베리파이 IP 주소&gt;:5000'을 입력한다.
