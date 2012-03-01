/**
 * Library for the use of Sharp GP2Y0A21YK IR Ranger
 * (Part # R301-GP2Y0A21YK)
 *
 * Note: Should also work with:
 *     Sharp GP2Y0A21YK0F (RoHS-compliant version of this same part)'
 * Might work with:
 *     Sharp GP2D12* (Narrower detection area) DEFINITELY test against 
 *       known distances to see if typical response curve is equivalent
 *       before you use this in an application!
 *
 * Written for Computer Science House @ Rochester Institute of Technology
 * by Chris Lockfort
 * for its iThwart project, and subsequent use as a basis for robotics projects
 * for general floor use.
 *
 * Magic numbers in the getRangeCm function were deduced from computational
 * regressional analysis of data points on the manufacturer provided 
 * typical response curve graph. The fityk tool suggested a split pearson 7 
 * curve or a sixth degree polynomial with an added gaussian curve, but 
 * using these to calculate on the fly with the floating point crunching power 
 * of a microcontroller seemed a Bad Idea. :-)
 * So it's just a simple power function for normal mode operations (reasonable 
 * accuracy from 10-80cm, as per manufacturer's specs) and a linear function to 
 * guess what's going on closer than 10cm. (These two modes cannot be combined 
 * because one voltage value can represent two possible distances; it does not 
 * fit the mathematical definition of a function.) 
 *
 */

#include "WProgram.h"
#include "CSHSharpIRSensor.h"

CSHSharpIRSensor::CSHSharpIRSensor(int pin){
  _pin = pin;
  _close = false; //Default = normal, official range for this sensor
}
void CSHSharpIRSensor::setCloseMode(bool close){
  _close = close;
}
int CSHSharpIRSensor::getRawData(){
  return analogRead(_pin);
}
float CSHSharpIRSensor::getRangeCm(){
  int reading=analogRead(_pin);
  if(!_close) //Normal, intended use of sensor
	  return pow(21656.89f*reading,-1.24f);
  else //CSH USE OF SENSOR
    return 0.01f*reading-0.22f;
}
float CSHSharpIRSensor::getRangeIn(){
  return getRangeCm()/2.54f;
}
