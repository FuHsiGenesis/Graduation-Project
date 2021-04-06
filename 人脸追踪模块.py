
import sensor, time, image, pyb

from pyb import Servo
from pid import PID

#Servo init
pan_servo=Servo(1) # P7  X轴
tilt_servo=Servo(2) # P8  Y轴
#pan_servo.speed(20)  # 舵机速度初始化
#tilt_servo.speed(20)
#pan_servo.calibration(500,2500,500) # 设定允许的最小脉宽、最大脉宽、中间值脉宽
#tilt_servo.calibration(500,2500,500)
pan_servo.angle(0)
tilt_servo.angle(0)
#pan_pid = PID(p=0.07, i=0, imax=90) #脱机运行或者禁用图像传输，使用这个PID
#tilt_pid = PID(p=0.05, i=0, imax=90) #脱机运行或者禁用图像传输，使用这个PID
pan_pid = PID(p=0.1, i=0.1, imax=90)#在线调试使用这个PID
tilt_pid = PID(p=0.1, i=0.1, imax=90)#在线调试使用这个PID


# Reset sensor
sensor.reset()
sensor.set_contrast(3)# 设置相机图像对比度。-3至+3。
sensor.set_gainceiling(16) # 设置相机图像增益上限。2, 4, 8, 16, 32, 64, 128。
sensor.set_framesize(sensor.B128X128) # 设置图像每一帧的尺寸
sensor.set_windowing((92,112)) # 将相机的分辨率设置为当前分辨率的子分辨率。
sensor.set_pixformat(sensor.GRAYSCALE) # 设置相机模块的像素模式。
sensor.skip_frames(time = 2000) # 跳过几帧，让感光元件稳定下来，使设置生效
clock = time.clock() # Tracks FPS.


# 加载Haar算子
# 默认情况下，这将使用所有阶段，较低的阶段更快但不太准确。
face_cascade = image.HaarCascade("frontalface", stages=25)
#print(face_cascade)


# 寻找图片中的最大色块：当一帧图片中出现多个人脸时，筛选出面积最大的人脸进行处理；
def find_max(blobs):
    max_size=0
    for blob in blobs:
        if blob[2]*blob[3] > max_size:
            max_blob=blob
            max_size = blob[2]*blob[3]
    return max_blob


while True:
    clock.tick() # Track elapsed milliseconds between snapshots().
    img = sensor.snapshot() #获取一张图片
    img.draw_string(0, 0, "Looking for a face...")#在图片左上角打出“Looking for a face...”
    #这个方法搜索与Haar Cascade匹配的所有区域的图像，并返回一个关于这些特征的边界框矩形元组(x，y，w，h)的列表。若未发现任何特征，则返回一个空白列表。
    faces = img.find_features(face_cascade, threshold=0.5, scale=1.25)#利用Haar算子获取一张人脸
    if faces:
        face = find_max(faces) # 图像单色块筛选
        cx = int(face[0]+face[2]/2)
        cy = int(face[1]+face[3]/2)
        pan_error = cx-img.width()/2
        tilt_error = cy-img.height()/2

        #print("pan_error: ", pan_error)
        #print('tilt_error：',tilt_error)

        img.draw_rectangle(face) # rect
        img.draw_cross(cx, cy) # cx, cy

        pan_output=pan_pid.get_pid(pan_error,1)
        tilt_output=tilt_pid.get_pid(tilt_error,1)

        #print("pan_output",pan_output)
        #print("tilt_output",tilt_output)

        pan_servo.angle(pan_servo.angle()-pan_output) #pan_servo.angle()：为上次输出的角度
        #print('all_output',pan_servo.angle()+pan_output)
        tilt_servo.angle(tilt_servo.angle()+tilt_output)
        #print('all_output',tilt_servo.angle()+tilt_output)






