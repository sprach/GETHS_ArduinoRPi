#-*-coding:utf-8-*-

from flask import Flask
from flask import render_template

# Flask 객체 생성
# app = Flask(__name__, template_folder='view')
# template_folder 인수를 사용하지 않을 경우에는 templates 라는 디렉토리 만들고
# 그 아래에 html 파일을 넣으면 된다.
app = Flask(__name__)


@app.route("/")
def index():
    # html 파일로부터 html 을 읽어온다.
    html_txt = render_template('index.html')
    return html_txt


# default port: 5000
app.run(host='0.0.0.0', port=3000, debug=True)
