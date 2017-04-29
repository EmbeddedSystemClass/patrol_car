#include "ebox.h"
#include "ebox_in_capture.h"
#include "PID.hpp"
#include "ebox_pwm.h"
#include "scan.hpp"
#include "led.h"
#define refresh_interval 0.01
const int pct = 300;//������ֱ��ʱת��
int mode;
greg::PID pid; Led led(&PC13,1);
InCapture encoder1(&PA10); //Ĭ��ȫ��1Ϊ������ͱ����� 2Ϊ�Ҳ����ͱ�����
InCapture encoder2(&PB10);
Scan scan; 
uint8_t scanvalue = scan.scan_init();//��ȡ��λ����ɨ������ ֱ��״̬Ϊ00011000
Pwm pwm1(&PB9); Pwm pwm2(&PB8);
float d = encoder1.get_wave_peroid() - encoder2.get_wave_peroid();
typedef enum
{	
    left1,
	left2,
	left3,
    straight,
	right1,
	right2,
	right3
}Car_Mode_Typedef;
void setMotorspeed(int a, int b)
{
	pwm1.set_duty(a);
	pwm2.set_duty(b);
}
void mode0()//�����������������ϵ���� Ӧ���ֵ���ռ�ձ�PB8
{
	pid.refresh(d);
	pid.setDesiredPoint(200);//�����ʱĿ���������ڱ�����С200
	pid.setWeights(4, 3, 6);
}
void setMode(Car_Mode_Typedef m)
{
	mode = m;
}
void setup()//pwm ������ PID�ĳ�ʼ��
{
	pid.setRefreshInterval(refresh_interval);
	pid.setOutputLowerLimit(0);
	pid.setOutputUpperLimit(1500);
	led.begin();
	ebox_init();//ϵͳ��ʼ��	
	pwm1.set_oc_polarity(0);//�Ƚ�ƥ�������͵�ƽ
	pwm1.begin(72000, 500);
	encoder1.begin(1); //1��Ƶ
	encoder1.set_polarity_rising(); 
	pwm2.set_oc_polarity(0);//�Ƚ�ƥ�������͵�ƽ
	pwm2.begin(72000, 500);
	encoder2.begin(1); //1��Ƶ
	encoder2.set_polarity_rising();
}
int main(void)
{
	setup();
	uart1.begin(115200);
	while (1)
	{   
		led.toggle();
		delay_ms(500);
		uart1.printf("%f %f\r", encoder1.get_wave_peroid(),encoder2.get_wave_frq());
	}
}