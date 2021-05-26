#include <mainpp.h>
#include <ros.h>
#include <std_msgs/String.h>

ros::NodeHandle nh;

std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

char hello[] = "Hello world!";

void setup(void)
{
	nh.initNode();
	nh.advertise(chatter);
}

void loop(void)
{
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
	
	str_msg.data = hello;
	chatter.publish(&str_msg);
	nh.spinOnce();
	HAL_Delay(1000);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
	nh.getHardware()->flush();
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	nh.getHardware()->reset_rbuf();
}
