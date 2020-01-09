# 'ssh'와 'WiFi' 설정
  1. PC와 USB Serial을 이용한 설정
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
