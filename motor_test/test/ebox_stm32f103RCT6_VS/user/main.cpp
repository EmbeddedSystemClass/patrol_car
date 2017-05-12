#include "ebox.h"
#include "tb6612.h"
Motor motor(&PB9,&PB12,&PB13,&PB11,&PB8,&PB14,&PB15);
InCapture encoder1(&PA10); //Ĭ��ȫ��1Ϊ������ͱ����� 2Ϊ�Ҳ����ͱ�����
InCapture encoder2(&PB10);
void setup()
{
    ebox_init();
	encoder1.begin(1); //1��Ƶ
	encoder1.set_polarity_rising();
	encoder2.begin(1); //1��Ƶ
	encoder2.set_polarity_rising();
	uart1.begin(115200);
	motor.begin();
}
int main(void)
{
	setup();
	motor.setMode(Forward);
	motor.setMotorPct(300, 300);
	uart1.printf("%d", encoder1.get_wave_high_time());
	delay_ms(500);
}