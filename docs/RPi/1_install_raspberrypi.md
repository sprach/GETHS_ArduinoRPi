# MicroSD 사전 설정
  > HDMI와 같이 디스플레이를 연결할 수 없을 때의 작업
  1. ssh 사용을 위한 빈 'ssh' 파일 복사 또는 만들어 넣기
  2. WiFi 접속을 위한 'wpa_supplicant.conf' 파일 복사해 넣기
     <pre><code>country=GB
     ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
     update_config=1

     network={
       ssid="&lt;ssid-name&gt;"
       psk="&lt;password&gt;"
     }</code></pre>
  3. USB Serial 접속을 위한 Serial 활성화 Key 삽입
     <pre><code>...
     enable_uart=1</code></pre>

# Raspberry Pi Config
  * 'ssh'와 'wpa_supplicant.conf' 파일 복사를 해 넣지 않은 경우
     1. Raspberry Pi config
        <pre><code>$ sudo raspi-config</code></pre>
     2. WiFi
        <pre><code>2 Network Options
        N2 Wi-fi
        Please enter SSID <i>&lt;ssid-name&gt;</i>
        Please enter passphrase. Leave it empty if none. <i>&lt;password&gt;</i></code></pre>
     3. Enable ssh
        <pre><code>5 Interfacing Options
        P2 SSH
        Would you like the SSH server to be enabled? <i>&lt;Yes&gt;</i>
        The SSH server is enabled <i>&lt;Ok&gt;</i></code></pre>
     4. Finish the Raspberry Pi config
        <pre><code>&lt;Finish&gt;</code></pre>

  * 파일 시스템 확장
    <pre><code>$ sudo raspi-config
    7 Advanced Options
    A1 Expand Filesystem
    Root partition has been resized.
    The filesystem will be enlarged upon the next reboot <i>&lt;Ok&gt;</i>
    <i>&lt;Finish&gt;</i>
    Would you like to reboot now? <i>&lt;Yes&gt;</i>
    * 재부팅 진행</code></pre>

  * 재부팅후 용량 확인
    <pre><code>$ df -k
    Filesystem     1K-blocks    Used Available Use% Mounted on
    /dev/root       30351740 6631700  22405272  23% /
    devtmpfs          469544       0    469544   0% /dev
    tmpfs             474152       0    474152   0% /dev/shm
    tmpfs             474152   12304    461848   3% /run
    tmpfs               5120       4      5116   1% /run/lock
    tmpfs             474152       0    474152   0% /sys/fs/cgroup
    /dev/mmcblk0p1    258095   55083    203013  22% /boot
    tmpfs              94828       0     94828   0% /run/user/1000</code></pre>

# Raspberry Pi의 IP 주소
  <pre><code> $ ifconfig</code></pre>
  <pre><code>eth0: flags=4099<UP,BROADCAST,MULTICAST>  mtu 1500
        ether b8:27:eb:0a:0d:86  txqueuelen 1000  (Ethernet)
        RX packets 0  bytes 0 (0.0 B)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 0  bytes 0 (0.0 B)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

  lo: flags=73<UP,LOOPBACK,RUNNING>  mtu 65536
        inet 127.0.0.1  netmask 255.0.0.0
        inet6 ::1  prefixlen 128  scopeid 0x10<host>
        loop  txqueuelen 1000  (Local Loopback)
        RX packets 0  bytes 0 (0.0 B)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 0  bytes 0 (0.0 B)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

  <b><i><u>wlan0</u></i></b>: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet <b><i><u>192.168.100.80</u></i></b>  netmask 255.255.255.0  broadcast 192.168.100.255
        inet6 fe80::a1c:e5d6:efac:b041  prefixlen 64  scopeid 0x20<link>
        ether b8:27:eb:5f:58:d3  txqueuelen 1000  (Ethernet)
        RX packets 15  bytes 1648 (1.6 KiB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 37  bytes 5409 (5.2 KiB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0</code></pre>

# Raspbian Update and Upgrade
  * Upgrade시 소요시간이 제법 길기 때문에 교육시에는 실행하지 말 것
    <pre><code>$ sudo apt-get update
    $ sudo apt-get upgrade
    $ sudo rpi-update -y</code></pre>

# 라즈베리파이 한글 폰트 설치
  1. 라즈베리파이에서 한글 보기용 폰트 설치
     <pre><code>$ sudo apt-get install fonts-unfonts-core fonts-nanum fonts-nanum-extra</code></pre>

# 라즈베리파이 원격접속 설정
  > Windows 원격데스크톱용
  1. 기존 VNC Server 제거
     <pre><code>$ sudo apt-get purge -y realvnc-vnc-server</code></pre>
  2. 새 VNC Server 설치
     <pre><code>$ sudo apt-get install -y tightvncserver</code></pre>
  3. XRDP 설치
     <pre><code>$ sudo apt-get install -y xrdp</code></pre>
  4. Windows 원격데스크톱으로 라즈베리파이에 연결
