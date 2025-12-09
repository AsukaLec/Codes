from flask import Flask, request, Response
import pandas as pd
import socket, threading, time, webbrowser, os
from flask import send_from_directory   # 顶部加
from flask import Flask, request, Response, send_from_directory   # 保持一样


app = Flask(__name__)

@app.route('/<path:filename>')
def static_file(filename):
    return send_from_directory('.', filename)

@app.route('/upload', methods=['POST'])
def upload():
    file = request.files['file']
    top5 = pd.read_csv(request.files['file'].stream).head(5).to_string(index=False)
    return Response(top5, mimetype='text/plain')


@app.route('/')                 # ← 新增
def index():
    return send_from_directory('.', 'index.html')   # 返回同级目录的 index.html


if __name__ == '__main__':
    with socket.socket() as s:
        s.bind(('', 0))
        port = s.getsockname()[1]
    threading.Thread(target=lambda: app.run(port=port, debug=False), daemon=True).start()
    time.sleep(0.5)
    webbrowser.open(f'http://localhost:{port}')
    while True:
        time.sleep(1)
