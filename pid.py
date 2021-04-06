from pyb import millis # 插件重置后，返回毫秒数。
from math import pi, isnan # isnan(x):若 x 非数字，则返回 True

class PID:
    _kp = _ki = _kd = _integrator = _imax = 0 # integrator：整合者
    _last_error = _last_derivative = _last_t = 0 # derivative：衍生物
    _RC = 1/(2 * pi * 20)
    def __init__(self, p=0, i=0, d=0, imax=0):
        self._kp = float(p)
        self._ki = float(i)
        self._kd = float(d)
        self._imax = abs(imax)
        self._last_derivative = float('nan')

    def get_pid(self, error, scaler): # error:误差值;scalar:
        tnow = millis() # 现在的时间
        dt = tnow - self._last_t # 现在的时间减去上次的时间等于时间的变化量
        output = 0
        if self._last_t == 0 or dt > 1000: # 如果上次的时间等于0且这次时间变化量大于1000
            dt = 0
            self.reset_I() #
        self._last_t = tnow # 本次时间变为上次时间
        delta_time = float(dt) / float(1000) # 疑似时间变化量的微分
        output += error * self._kp # 输出值为误差值与kp参数乘积的累加
        if abs(self._kd) > 0 and dt > 0: # 如果微分系数kd的绝对值大于0且时间的差值大于0
            if isnan(self._last_derivative): # 如果self._last_derivative这个值大于0则返回True
                derivative = 0 # 就把这个值赋值为0
                self._last_derivative = 0 # 就把这个值赋值为0
            else:
                derivative = (error - self._last_error) / delta_time # 本次误差与上次误差关于时间（delta_tim）的微分
            derivative = self._last_derivative + \
                                     ((delta_time / (self._RC + delta_time)) * \
                                        (derivative - self._last_derivative))
            self._last_error = error
            self._last_derivative = derivative
            output += self._kd * derivative
        output *= scaler
        if abs(self._ki) > 0 and dt > 0:
            self._integrator += (error * self._ki) * scaler * delta_time
            if self._integrator < -self._imax: self._integrator = -self._imax
            elif self._integrator > self._imax: self._integrator = self._imax
            output += self._integrator
        return output
    def reset_I(self):
        self._integrator = 0
        self._last_derivative = float('nan')
