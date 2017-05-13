#include "ebox.h"
#include "tb6612.h"
#include "PID.hpp"
#include "scan.hpp"
#include "led.h"//������������ָʾ��
#include "point_led.h"//����ָʾ��
#define refresh_interval 0.01
const int straightPct = 300;//������ֱ��ʱת��
greg::PID pid1,pid2;
Led led1(&PC13, 1); 
PointLed point;
InCapture encoder1(&PA10); //Ĭ��ȫ��1Ϊ������ͱ����� 2Ϊ�Ҳ����ͱ�����
InCapture encoder2(&PB10);
Scan scan; 
Motor motor(&PB9, &PB12, &PB13, &PB11, &PB8, &PB14, &PB15); 
//(Gpio *pwmA, Gpio *Ain1, Gpio *Ain2, Gpio *stby, Gpio *pwmB, Gpio *Bin1, Gpio *Bin2);
uint8_t scanvalue = scan.scanRead();//��ȡ��λ����ɨ������ ֱ��״̬Ϊ00011000
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
}Mode_Typedef;
//void mode0()//�����������������ϵ���� Ӧ���ֵ���ռ�ձ�PB8
//{
//	//pid.refresh(d);
//	//pid.setDesiredPoint(200);//�����ʱĿ���������ڱ�����С200
//	//pid.setWeights(4, 3, 6);
//}
void showMode(Mode_Typedef m)
{
	while (1)
	{
		if (scanvalue == 0xc0) //1100 0000
		{
			m = left1;
			point.write(!0xc0);
		}
		if (scanvalue == 0x60)//0110 0000 
		{
			m = left2;
			point.write(!0x60);
		}
		if (scanvalue == 0x30)//0011 0000
		{
			m = left3;
			point.write(!0x30);
		}
		if (scanvalue == 0x18)//0001 1000
		{
			m = straight;	
			point.write(!0x18);
		}
		if (scanvalue == 0xc0)//0000 1100
		{
			m = right1;	
			point.write(!0xc0);
		}
		if (scanvalue == 0x06)//0000 0110
		{
			m = right2;
			point.write(!0x06);
		}
		if (scanvalue == 0x0c)//0000 0011
		{    
			m = right3;
			point.write(!0x0c);
		}
	}
}
void setup()//pwm ������ PID�ĳ�ʼ��
{
	//*pid.setRefreshInterval(refresh_interval);
	//pid.setOutputLowerLimit(0);
	//pid.setOutputUpperLimit(1500);*/
	led1.begin();
	ebox_init();//ϵͳ��ʼ��	
	point.begin();

	encoder1.begin(1); //1��Ƶ
	encoder1.set_polarity_rising(); 
	encoder2.begin(1); //1��Ƶ
	encoder2.set_polarity_rising();
}
int main(void)
{
	setup();
	showMode(straight);
	while (1)
	{   
		led1.toggle();
		delay_ms(500);
	}
}