# Mosquitto Broker 설치

1. 설치 및 확인
   <pre><code>$ sudo apt-get install -y mosquitto</code></pre>

2. 설치 확인
   <pre><code>$ mosquitto -v</code></pre>

3. Self 테스트
   > 테스트를 위해서 2개의 터미널 연결이 필요하다.

   * 터미널 #1
     1. Mosquitto 클라이언트 설치
        <pre><code>$ sudo apt-get install -y mosquitto-clients</code></pre>

     2. Mosquitto 실행
        <pre><code>$ mosquitto -d</code></pre>
     3. Mosquitto 프로세스 확인
        <pre><code>$ ps -ef | grep mosquitto
        <i>mosquit+  1245     1  0 05:32 ?        00:00:00 /usr/sbin/mosquitto -c /etc/mosquitto/mosquitto.conf
        pi        1609  1110  0 05:37 pts/0    00:00:00 grep --color=auto mosquitto</i></code></pre>
     4. 클라이언트로 토픽(Topic) 구독(Subscribe) 실행
        <pre><code>$ mosquitto_sub -d -t testTopic</code></pre>

     5. 터미널 #2에서 보낸 메시지 수신
        <pre><code><i>Client mosqsub|1682-raspberryp received PUBLISH (d0, q0, r0, m0, 'testTopic', ... (22 bytes))
        Hello Mosquitto world!</i></code></pre>
    
     6. 구독 종료시 &lt;CTRL&gt; + &lt;C&gt; 키를 누른다.

   * 터미널 #2
     1. 메시지 전송 (Publish)
        <pre><code>$ mosquitto_pub -d -t testTopic -m "Hello Mosquitto world!"
        <i>Client mosqpub|1728-raspberryp sending CONNECT
        Client mosqpub|1728-raspberryp received CONNACK (0)
        Client mosqpub|1728-raspberryp sending PUBLISH (d0, q0, r0, m1, 'testTopic', ... (22 bytes))
        Client mosqpub|1728-raspberryp sending DISCONNECT</i></code></pre>

     2. 터미널 #2 종료 (&lt;CTRL&gt; + &lt;C&gt; 키) 
