
## 兰州隧道进出洞检测程序
工作原理：
在火车的两侧分别安装一个相机和一个激光器，通过检测激光斑点在图像
中的位置，跟库三角计算原理，可得到斑点打到的实物距相机的距离，从
而判断火车的进出洞状态。
程序分为以下模块：
### 采集模块
打开两个相机，接收触发信号并采集图像
### 图像处理及距离计算模块
对采集的图像进行处理并计算斑点距离
### 进出洞判断模块
根据距离判断进出洞状态
### 硬件模块
接收主机发来的工作模式信号，以及发送进出洞信号到主机