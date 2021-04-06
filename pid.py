from pyb import millis
#返回代码执行到当前的时间

from math import pi, isnan
#pi-->Π，isnan-->用于检查给定数字是否为“ NaN” (不是数字)，它接受一个数字，如果给定数字为“ NaN” ，则返回True ，否则返回False 。



class PID:
#PID(proportion integration differentiation)
#     比例		   积分		微分
    _kp = _ki = _kd = _integrator = _imax = 0
    #初始化三个系数，积分，？？？为0  

    _last_error = _last_derivative = _last_t = 0
#     最新差值          最新导数	上个轮回的时间
    _RC = 1/(2 * pi * 20)
#？？？
    def __init__(self, p=0, i=0, d=0, imax=0):

        self._kp = float(p)

        self._ki = float(i)

        self._kd = float(d)

        self._imax = abs(imax)

        self._last_derivative = float('nan')
		#设置微分为nan


    def get_pid(self, error, scaler):
#根据差值，K获取pid
        tnow = millis()
		#现在的时间
        dt = tnow - self._last_t
		#和上次的时间差
        output = 0
		#总输出（你调节的量）
        if self._last_t == 0 or dt > 1000:
		#如果是第一个轮回（初始值为0）或时间差>1s（大于可微积分的阈值）
            dt = 0
		#时间差归零
            self.reset_I()
			#重置I
        self._last_t = tnow
		#记录结束时间
        delta_time = float(dt) / float(1000)
		#获取Δt
        output += error * self._kp
		#加入比例控制积分
        if abs(self._kd) > 0 and dt > 0:
		#若微分参数和时间差>0
            if isnan(self._last_derivative):
		    #若微分是NaN
                derivative = 0
			#微分归零
                self._last_derivative = 0
			#PS:前面已经声明为nan，所以openmv没有用微分控制
            else:
            #否则    

                derivative = (error - self._last_error) / delta_time
                #微分为：（这次的差距-上次的差距）/时间差

            derivative = self._last_derivative + \

                                     ((delta_time / (self._RC + delta_time)) * \

                                        (derivative - self._last_derivative))
                #这三行我不懂，怎么会有这种代码在这里。。。？？？

            self._last_error = error
			#更新差值
            self._last_derivative = derivative
			#更新积分值
            output += self._kd * derivative
			#加入微分控制
        output *= scaler
		#乘以总系数
        if abs(self._ki) > 0 and dt > 0:
		#若I参数>0
            self._integrator += (error * self._ki) * scaler * delta_time
			#计算积分控制
            if self._integrator < -self._imax: self._integrator = -self._imax
			
            elif self._integrator > self._imax: self._integrator = self._imax
			#积分大于等于设定最大值时
            output += self._integrator
			#加入积分控制
        return output

    def reset_I(self):
	//重置I
        self._integrator = 0

        self._last_derivative = float('nan')
