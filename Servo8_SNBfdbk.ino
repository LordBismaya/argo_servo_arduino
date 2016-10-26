#include <ArduinoHardware.h>
#include <ros.h>

/*
 * rosserial Servo Control Example
 *
 * This sketch demonstrates the control of hobby R/C servos
 * using ROS and the arduiono
 * 
 * For the full tutorial write up, visit
 * www.ros.org/wiki/rosserial_arduino_demos
 *
 * For more information on the Arduino Servo Library
 * Checkout :
 * http://www.arduino.cc/en/Reference/Servo
 */

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif
#define USE_USBCON
#include <Servo.h> 
#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <rosserial_arduino/Adc.h>


ros::NodeHandle  nh;//Declare ROS nodehandle

rosserial_arduino::Adc adc_msg;//Declare ADC message object
Servo servo;//Declare Servo object

//Servo CallBackFunction
void servo_cb( const geometry_msgs::Twist& msg)
{
  float vel=0;
  vel=msg.linear.x; 
  if(vel>10)// Write only if Value exceeds a threshold
  {
    servo.write(vel); //set servo angle, should be from 0-180  
  }
}

//We average the analog reading to elminate some of the noise
int averageAnalog(int pin)
{
  int v=0;
  /*Not averaging of now. Reading RAW ADC
  for(int i=0; i<4; i++) v+= analogRead(pin);
  return v/4; 
  */
 v=analogRead(pin);
 return v;
}

//ROS subscriber for Twist cmd_vel
ros::Subscriber<geometry_msgs::Twist> acc_Sub("argo_base/cmd_vel", servo_cb);
//ROS Publisher for Brake Position Feedback
ros::Publisher brk_Pub("brakeInfo",&adc_msg);


//Setup the arduino. Invoked only once
void setup()
{
  pinMode(11, OUTPUT);//to enable Roboteq, Pin 11 needs to be high.
  digitalWrite(11, HIGH);//for Roboteq

  nh.initNode();//nh Initialization for spinning ROS msgs.
  nh.subscribe(acc_Sub);//set up Accelerator Subscriber
  nh.advertise(brk_Pub);//set up BrakeFeeback Publisher
  
  servo.attach(12); //attach servo to pin 9
  servo.write(0);//Servo to be at Zero during initialization
}


void loop(){
  //Read ADC Values
  adc_msg.adc0=averageAnalog(0);//Read the contents of Pin2 and 3.
  adc_msg.adc1=averageAnalog(1);
  brk_Pub.publish(&adc_msg);//Publish to brakeInfo topic

  nh.spinOnce();  //Node Handle Spin
  delay(1); //1ms delay
}
