
      
      /////////////////////////////////////////////  
     //   Mobile Weather Station Being Powered  //
    //            by Solar Energy              //
   //               (Android)                 //           
  //             by Kutluhan Aktar           // 
 //                                         //
/////////////////////////////////////////////


// Get the weather information through an Android app constantly and use the solar energy generating by the PV panel to charge devices. 
//
// Features: 
//
// -Get the weather information constantly. 
//
// -Control the laser module. 
//
//
// Connections:
//
// Arduino Uno
//                           DHT11 Temperature and Humidity Sensor
// Pin 2  -------------------
//                           Laser Module
// Pin 3  -------------------
//                           HC-06 Bluetooth Module
// Pin 4  ------------------- TX
// Pin 5  ------------------- RX

#include <SoftwareSerial.h> // Include Arduino libraries.
#include <DHT.h>

int LaserPin = 3; // Define the sensors pins.
int Connect_RX = 4;
int Connect_TX = 5; 

int humidity;    // DHT11 variables.
int temperatureC;
int temperatureF;

SoftwareSerial Connect(Connect_RX, Connect_TX); // Connect the bluetooth module.

DHT dht; // Start DHT11.

void setup() {
Serial.begin(9600); // Initial serial connections.
Connect.begin(9600);
dht.setup(2);  // Define DHT11 pin.
pinMode(LaserPin, OUTPUT);

}

void loop() {
  getDataToDHT(); 
if(Connect.available()){
  char c = Connect.read();
  Laser(c);
 }
  sendDataToConnect();
}

void Laser(char i){ // Commands when Arduino gets a char.
 switch(i){
  case '1':
  digitalWrite(LaserPin, HIGH);  
  break;
  case '2':
  digitalWrite(LaserPin, LOW);
  break;
  } 
}
void getDataToDHT(){ // Collect data and create the data packet.
 humidity = dht.getHumidity();
 temperatureC = dht.getTemperature();
 temperatureF = dht.toFahrenheit(temperatureC);
 delay(dht.getMinimumSamplingPeriod());

}

void sendDataToConnect(){ // Sending function.
 Connect.print(temperatureC);
 Connect.print("°C");
 Connect.print("\n");  
 Connect.print(temperatureF);
 Connect.print("°F");
 Connect.print("\n");  
 Connect.print(humidity);
 Connect.print("%");
 delay(1000);
  
}


