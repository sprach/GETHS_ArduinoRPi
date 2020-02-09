# APM 설치
  > Apache + PHP + MySQL

## Apache Web Server 설치

1. 설치
   > 아파치 설치후 웹 문서 루트: /var/www/html
   <pre><code>$ sudo apt-get install -y apache2</code></pre>

2. 소유 권한 변경
   <pre><code>$ sudo chown pi -R /var/www/html</code></pre>

3. 부팅시 웹서버 자동 실행
   <pre><code>$ sudo update-rc.d apache2 defaults</code></pre>

4. PC에서 웹 접속 테스트
   1. 라즈베리파이의 IP 주소 확인
      <pre><code>$ ifconfig</code></pre>
   2. PC에서 웹 브라우저 실행
   3. 웹 브라우저 주소창에 라즈베리파이 IP 주소 입력

## MySQL 설치 (MariaDB)
1. 설치
   <pre><code>$ sudo apt-get install -y mariadb-server mariadb-client libmariadb-dev</code></pre>

   * 아래 삭제
   * 설치 진행중 <b><i><u>'root' 유저에 대한 암호 설정 입력</u></i></b> 화면이 뜬다.<br/>이 때 입력한 root 암호는 잊어버리지 말고 기억해야 한다!<br/>테스트용인 경우에는 'P@ssw0rd'와 같이 입력한다.

2. 외부에서 접속할 수 있도록 /etc/mysql/my.cnf 수정
   1. MySQL Config 파일을 연다.
      <pre><code>$ sudo vi /etc/mysql/my.cnf</code></pre>
   2. 'bind-adress'를 찾는다.
      <pre><code>/bind-address&lt;Enter&gt;</code></pre>
   3. 'bind-address'에서 '$' 키 입력하여 커서 첫 칸으로 이동후 삽입 상태에서 '#' 입력한 뒤에 &lt;ESC&gt; 키를 누른다.
      <pre><code>#bind-address = 127.0.0.1</code></pre>
   4. ':wq!'로 파일을 강제 저장하고 빠져 나온다.
      <pre><code>:wq!</code></pre>

3. 설치 확인
   <pre><code>$ mysql --version</code></pre>

## PHP 설치

1. 설치
   <pre><code>$ sudo apt-get install -y php5</code></pre>

2. 설치 버전 확인
   <pre><code>$ php -version</code></pre>

3. PHP 파일 생성
   1. 'phpinfo.php' 파일을 만든다.
      <pre><code>$ sudo vi /var/www/html/phpinfo.php</code></pre>
   2. 'a' 키를 눌러서 아래 스크립트를 입력한다.
      <pre><code>&lt;? phpinfo(); ?&gt;</code></pre>
   3. &lt;ESC&gt; 키를 누른 뒤에 ':wq!'로 파일을 강제 저장하고 빠져 나온다.
      <pre><code>&lt;ESC&gt;:wq!</code></pre>

4. PHP 웹 테스트
   1. PC에서 웹 브라우저를 실행한다.
   2. 주소 칸에 '&lt;라즈베리파이 IP 주소&gt;/phpinfo.php'를 입력하여 PHP 정보가 나오는지 확인한다.
   > 만약 PHP 정보가 나오지 않으면 앞서의 'phpinfo.php' 파일 내용을 아래와 같이 변경해서 저장후 다시 테스트해 본다.
     <pre><code>&lt;?php phpinfo(); ?&gt;</code></pre>

## 웹으로 DB 관리툴 설치 (phpmyadmin)

1. 설치
   <pre><code>$ sudo apt-get install -y phpmyadmin</code></pre>
   * 설치시 웹서버 선택창이 뜨면 '<b><i><u>apache2</u></i></b>'를 선택한다.
   * 설치 중간에 관리자 암호는 앞서 입력한 'root' 암호를 입력한다.<br/>

2. Apache Config에 'phpmyadmin' 등록하기
   1. 'apache2.conf' 파일을 연다.
      <pre><code>$ sudo vi /etc/apache2/apache2.conf</code></pre>
   2. 맨 마지막으로 커서를 이동한다.
   3. 'a' 키로 삽입 모드를 만든 뒤에 아래와 같이 입력한다.
      <pre><code>Include /etc/phpmyadmin/apache.conf</code></pre>
   4. &lt;ESC&gt; 키를 누른 뒤에 ':wq!'로 파일을 강제 저장하고 빠져 나온다.
      <pre><code>&lt;ESC&gt;:wq!</code></pre>
   5. 아파치를 재가동한다.
      <pre><code>$ sudo service apache2 restart</code></pre>

3. phpmyadmin 테스트
   1. PC에서 웹 브라우저를 실행한다.
   2. 주소 칸에 '&lt;라즈베리파이 IP 주소&gt;/phpmyadmin'를 입력한다.
   3. 'Username'에는 'root'를, 'Password'에는 앞서 지정한 암호를 입력한다.
