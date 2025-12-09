import serial, csv, datetime, os

PORT  = 'COM4'
BAUD  = 9600
FNAME = datetime.datetime.now().strftime('%Y%m%d_%H%M%S') + '_ECG_GSR.csv'

with serial.Serial(PORT, BAUD, timeout=1) as ser, \
     open(FNAME, 'w', newline='') as f:
    writer = csv.writer(f)
    #  Arduino 已发表头，这里不用再写
    print(f'Logging to {FNAME}  –  Ctrl-C 停止')
    try:
        while True:
            line = ser.readline().decode(errors='ignore').strip()
            if not line or line.startswith('relMs'):  # 跳过表头
                continue
            writer.writerow(line.split(','))   # 三列原样落地
            f.flush()
    except KeyboardInterrupt:
        print('停止，文件：', FNAME)
