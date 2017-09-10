// Water meter sensor using ESP8266 and a MAG3110 Magnetometer
// Dan Kouba, 2017

#include <SparkFun_MAG3110.h>

MAG3110 mag = MAG3110(); //Instantiate MAG3110
long int last_time = 0;

void setup() {
  Serial.begin(115200);
  
  Serial.println("\n");

  // Initializes the mag sensor
  Serial.print("Initializing MAG3110...");
  while(!mag.initialize()){
    Serial.print(".");
  }
  Serial.println("success");
  
  mag.setDR_OS(MAG3110_DR_OS_80_16);  // Set data rate to 80Hz, OSR 16
  mag.rawData(true);
  mag.start();                        // Puts the sensor in active mode
}

void loop() {

  float x, y, z;
  //Only read data when it's ready
  if(mag.dataReady()) {
    
    //Read the data
    long int cur_time = micros() - last_time;
    mag.readMicroTeslas(&x, &y, &z);

    //Serial.print(micros() - last_time);
    //Serial.print(",");
    Serial.print(x);
    Serial.print(",");
    Serial.print(y);
    Serial.print(",");
    Serial.println(z);

    last_time = micros();
  }
}
