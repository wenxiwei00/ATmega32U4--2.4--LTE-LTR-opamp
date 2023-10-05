# ATmega32U4--2.4--LTE-LTR-opamp
用LTE发射红外光，用LTR接收红外光。接收到不同频率，就亮不同的灯。  
### 电路图  
1. 发射端用的是LTE4208，接收端用的是LTR4206E，运算放大器是TLV273
2. 使用了信号放大器，设置100kΩ，这会使得output被放大很多。拿着红外发射器去照接收器，距离1米去照都能接收到  
![image](https://github.com/wenxiwei00/ATmega32U4--2.4--LTE-LTR-opamp/assets/114196821/13fb5f96-c026-43ef-a3b2-c037b380d44f)  

### 最终效果  
拿发射端对准接收端去照：当给发射端25赫兹方波时候红灯亮，220hz时候蓝灯亮，662hz绿灯亮。  
https://youtube.com/shorts/6ind60bPfPM?feature=share
