#-*-coding:utf-8-*-

import paho.mqtt.client as mqtt                     #Paho-MQTT 패키지 불러오기
from flask import Flask, render_template, request   #Flask 패키지 불러오기 
app = Flask(__name__)                               #Flask 모듈 불러오기

myuserid = "sprach"


# 데이터베이스 접속 함수
def get_connection():
    conn = pymysql.connect(host='127.0.0.1', port=3306, user='root', password='P@ssw0rd'
                           , db='guestbook_db', charset='utf8')
    return conn


# MQTT 클라이언트 연결
mqttc=mqtt.Client()
mqttc.connect("localhost",1883, 60)
mqttc.loop_start()

# 'name'과 'state'로 LED Dictionary 정의
led = {'name' : 'LED pin', 'state' : 'ON'}

# 웹서버의 URL 주소로 접근하면 아래의 main() 함수를 실행
@app.route("/")
def main():
   # LED Dictionary를 templateData에 저장 
   templateData = {
      'led' : led
   }
   return render_template('mainMqtt.html', **templateData)

# <action>에 따른 동작
@app.route("/LED/<action>")
def action(action):

   # action이 on이면 mqtt inTopic에 1을 보낸다.
   if action == "on":
      mqttc.publish("inTopic","1")
      led['state'] = "ON"
      message = "LED on."
   # action이 off이면 mqtt inTopic에 0을 보낸다.
   if action == "off":
      mqttc.publish("inTopic","0")
      led['state'] = "OFF"
      message = "LED off."

   templateData = {
      'message' : message,
      'led' : led
   }

   # 저장 (mysql 에서는 정수형이더라도 %s 로 해 주어야 한다.)
   # 다른 상용 DB는 문제가 없음
   // 컬럼 순서: mqtt_dt, mqtt_owner, msg_typ, mqtt_msg
   query = "insert into tbl_mqtt_log values (now(), %s, %s, %s);"
   conn = get_connection()
   cursor = conn.cursor()
   cursor.execute(query, (myuserid, 'L', led['state']))
   conn.commit()
   conn.close()

   return render_template('mainMqtt.html', **templateData)

# Flask 웹 실행
if __name__ == "__main__":
   app.run(host='0.0.0.0', debug=False)
