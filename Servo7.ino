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
#include <std_msgs/UInt16.h>
#include <geometry_msgs/Twist.h>

ros::NodeHandle  nh;

Servo servo;

void servo_cb( const geometry_msgs::Twist& msg){
float vel=msg.linear.x;
float angu=msg.angular.z;

if(vel<20){
  vel=0;}
  
  servo.write(vel); //set servo angle, should be from 0-180  
  

}


ros::Subscriber<geometry_msgs::Twist> sub("argo_base/cmd_vel", servo_cb);

void setup(){
  pinMode(11, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
  digitalWrite(11, HIGH);
  servo.attach(12); //attach it to pin 9
}

void loop(){
  nh.spinOnce();
  delay(1);
}
