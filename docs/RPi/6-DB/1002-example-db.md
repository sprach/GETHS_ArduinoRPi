# MQTT를 위한 예시용 Database

1. 새 데이터베이스 생성
   <pre><code><i>MariaDB [(none)]></i> create database raspi_mqtt_db;
   <i>MariaDB [(none)]></i> use raspi_mqtt_db;</code></pre>

2. 새 사용자 등록 및 권한 부여
   <pre><code><i>MariaDB [(raspi_mqtt_db)]></i> CREATE USER 'usermqtt'@'localhost' IDENTIFIED BY 'a!23456789';
   <i>MariaDB [(raspi_mqtt_db)]></i> GRANT ALL PRIVILEGES ON raspi_mqtt_db.* TO 'usermqtt'@'localhost';</code></pre>

3. 새 테이블 등록
   > 아래부터는 프롬프트(MariaDB [(raspi_mqtt_db)]>) 표시는 제외
   <pre><code>create table if not exists tbl_mqtt_log (
        mqtt_dt      datetime       not null,
        mqtt_owner   varchar(10)    not null,
        msg_typ      char(1)        not null,  -- 'M': message, 'L':led
        mqtt_msg     varchar(100)   not null
   );</code></pre>

4. 테스트 데이터 등록
   > 'mqtt_owner'는 임의로 정함 (여기서는 'jupiter'로 함)
   <pre><code>insert into tbl_mqtt_log (mqtt_dt, mqtt_owner, msg_typ, mqtt_msg)
        values (now(), 'jupiter', 'M', 'hello sprach!');
   insert into tbl_mqtt_log (mqtt_dt, mqtt_owner, msg_typ, mqtt_msg)
        values (now(), 'jupiter', 'L', '1');
   insert into tbl_mqtt_log (mqtt_dt, mqtt_owner, msg_typ, mqtt_msg)
        values (now(), 'jupiter', 'M', 'hello second!');
   insert into tbl_mqtt_log (mqtt_dt, mqtt_owner, msg_typ, mqtt_msg)
        values (now(), 'jupiter', 'L', '0');
   </code></pre>

5. 등록한 데이터 조회
   <pre><code>select *
     from tbl_mqtt_log;</code></pre>

6. 메시지 타입별로 조회
   1. 'M' 데이터를 최근 순(역순)으로 조회
      <pre><code>select *
        from tbl_mqtt_log
       where msg_typ = 'M'
       order by mqtt_dt desc;</code></pre>

   2. 'L' 데이터를 오래된 순으로 조회
      <pre><code>select *
        from tbl_mqtt_log
       where msg_typ = 'L';</code></pre>
