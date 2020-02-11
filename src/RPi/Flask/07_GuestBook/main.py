#-*-coding:utf-8-*-

from flask import Flask, render_template, request
# pymysql 다운로드
# 시작 - Anaconda Prompt
# pip install pymysql
import pymysql

app = Flask(__name__)


# 데이터베이스 접속 함수
def get_connection():
    conn = pymysql.connect(host='127.0.0.1', port=3306, user='root', password='P@ssw0rd'
                           , db='guestbook_db', charset='utf8')
    return conn


@app.route("/")
def index():
    # DB 접속 테스트
    conn = get_connection()
    conn.close()

    return render_template('index.html')


@app.route("/write_guest_book")
def write_guest_book():
    return render_template('write_guest_book.html')


@app.route("/write_pro", methods=['post'])
def write_pro():
    # 파라메터 데이터 추출
    guest_name = request.values.get('guest_name')
    guest_text = request.values.get('guest_text')

    # 저장 (mysql 에서는 정수형이더라도 %s 로 해 주어야 한다.)
    # 다른 상용 DB는 문제가 없음
    query = 'insert into guestbook_table (guest_name, guest_text) values (%s, %s)'
    conn = get_connection()
    cursor = conn.cursor()
    cursor.execute(query, (guest_name, guest_text))
    conn.commit()
    conn.close()

    return render_template('write_pro.html')


@app.route('/get_guest_book')
def get_guest_book():
    query = 'select guest_name, guest_text from guestbook_table order by guest_idx desc'
    conn = get_connection()
    cursor = conn.cursor()
    cursor.execute(query)
    # 결과를 가져온다.
    result = cursor.fetchall()      # fetchone(), fetchmany()
    conn.close()

    # DB를 닫은 후에 값이 있으면 그대로 사용하고 아니면 다른 곳에 옮겨 담은 후 사용
    # print(f'{type(result)}')    # 결과: <class 'tuple'>
    # print(f'{result}')          # 결과: (('홍길동', '첫 방명록 작성입니다.'),)

    # return 'get_guest_book'
    return render_template('get_guest_book.html', result=result)


app.run(host='0.0.0.0', port=3000, debug=True)
