**# ********************Face recognition with LBP descriptors.
# See Timo Ahonen's "Face Recognition with Local Binary Patterns".
#
# Before running the example:
# 1) Download the AT&T faces database http://www.cl.cam.ac.uk/Research/DTG/attarchive/pub/data/att_faces.zip
# 2) Exract and copy the orl_faces directory to the SD card root.


import sensor, time, image, pyb

sensor.reset() # Initialize the camera sensor.
sensor.set_pixformat(sensor.GRAYSCALE) # or sensor.GRAYSCALE
sensor.set_framesize(sensor.B128X128) # or sensor.QQVGA (or others)
sensor.set_windowing((92,112))
sensor.skip_frames(10) # Let new settings take affect.
sensor.skip_frames(time = 3000) #等待5s,等帧率、图像稳定以后再开始上传



#SUB = "s1"
NUM_SUBJECTS_flash=3       #图像库中不同人数，一共NUM_SUBJECTS_flash人
NUM_SUBJECTS_IMGS_flash=10  #每人有10张样本图片

NUM_SUBJECTS =NUM_SUBJECTS_flash #图像库中不同人数，一共NUM_SUBJECTS_flash人
NUM_SUBJECTS_IMGS = NUM_SUBJECTS_IMGS_flash#每人有10张样本图片

def min(pmin, a, s):#用来给特征值比较大小的函数
    global num # golbal将num变量变为全局变量
    if a<pmin:
        pmin=a
        num=s
    return pmin

def max(dict):
    x=0
    num1=0
    for i in dict:
        if dict[i]>x:
            x=dict[i]
            num1=i
    return num1

num_list={1:0,2:0,3:0}      # 预处理结果计数容器
num_Pre=0    # 结果输出前预处理结果统计次数
infor={2:'王正礼',1:'张登山',3:'缪楠'}      # 身份信息字典
t=0
while(True):
    img = sensor.snapshot()     # 拍摄当前人脸。
    #img = image.Image("singtown/%s/1.pgm"%(SUB))
    d0 = img.find_lbp((0, 0, img.width(), img.height()))     #d0为当前人脸的lbp特征
    #print(d0)
    img = None
    pmin = 9999999
    num=0
    #人脸特征匹配
    for s in range(1, NUM_SUBJECTS+1):
        dist = 0
        for i in range(1, NUM_SUBJECTS_IMGS+1):
            #print("singtown/s%d/%d.bmp"%(s, i))
            img = image.Image("singtown/s%d/%d.bmp"%(s, i))
            d1 = img.find_lbp((0, 0, img.width(), img.height()))     # d1为第s文件夹中的第i张图片的lbp特征
            dist += image.match_descriptor(d0, d1)       #计算d0、d1即样本图像与被检测人脸的特征差异度。
        # print("Average dist for subject %d: %d"%(s, dist/NUM_SUBJECTS_IMGS))
        pmin = min(pmin, dist/NUM_SUBJECTS_IMGS, s)      #特征差异度越小， 被检测人脸与此样本更相似更匹配。 dist/NUM_SUBJECTS_IMGS为单张图片的差异值
        #print(pmin)
    #print("识别身份为："+infor[num])
    if num_Pre<10:
        num_Pre=num_Pre+1
        print('识别进度：10-%d\n'%num_Pre)
        for x in num_list:
            if x==num:
                num_list[x]=num_list[x]+1
                #print(num_list[x])
    else:
        num_Pre=0
        print("识别身份为："+infor[max(num_list)])
        for x in num_list:
            num_list[x]=0


