#include <FirebaseArduino.h>

#include <ESP8266WiFi.h>



#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>


    const int trigPin =D3;
    const int echoPin = D4;
    // defines variables
    long duration;
    int distance;

TinyGPSPlus gps;  // The TinyGPS++ object

SoftwareSerial ss(D1, D2); // The serial connection to the GPS device


#define FIREBASE_HOST "example.firebaseio.com"
#define FIREBASE_AUTH "yourFirebaseaAuth"

const char* ssid = "SSID";
const char* password = "PASSWORD";

float latitude , longitude;
int year , month , date, hour , minute , second;
String date_str , time_str , lat_str , lng_str;
int pm;

WiFiServer server(80);
void setup()
{
  Serial.begin(9600);
  ss.begin(9600);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());

 Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT); // Sets the echoPin as an Input
    Serial.begin(9600); // Starts the serial communication
}

void loop()
{

  while (ss.available() > 0)
    if (gps.encode(ss.read()))
    {
      if (gps.location.isValid())
      {
        latitude = gps.location.lat();
        lat_str = String(latitude , 6);
        longitude = gps.location.lng();
        lng_str = String(longitude , 6);
      }
    }
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client)
  {
    return;
  }

// Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance= duration*0.034/2;
    // Prints the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.println(distance);
    if (distance>50)
    {
      Serial.print("Empty");
      Firebase.setString("message", "empty");

  if (Firebase.failed()) {
      Serial.print("setting /message failed:");
      Serial.println(Firebase.error());  
      return;
    }
    }
    else if(distance>40&&distance<50)
    {
    Serial.println("quater");
    Firebase.setString("message", "quater");
   if (Firebase.failed()) {
      Serial.print("setting /message failed:");
      Serial.println(Firebase.error());  
      return;
    }
    }
        else if(distance>30&&distance<40)
        
    {
    Serial.println("half");
    Firebase.setString("message", "half");
   if (Firebase.failed()) {
      Serial.print("setting /message failed:");
      Serial.println(Firebase.error());  
      return;
    }
    }
        else if(distance>20&&distance<30)
    {
    Serial.println("almost_full");
    Firebase.setString("message", "almost_full");
   if (Firebase.failed()) {
      Serial.print("setting /message failed:");
      Serial.println(Firebase.error());  
      return;
    }
    }
        else if(distance<20)
    {
    Serial.println("full");
    Firebase.setString("message", "full");
   if (Firebase.failed()) {
      Serial.print("setting /message failed:");
      Serial.println(Firebase.error());  
      return;
    }
    }
    delay(1000);

  while (ss.available() > 0)
    if (gps.encode(ss.read()))
    {
      if (gps.location.isValid())
      {
        latitude = gps.location.lat();
        Serial.print("lat: ");
  Serial.print(latitude,6);
 Serial.print("\t");
        lat_str = String(latitude,6);
        
        longitude = gps.location.lng();
        Serial.print(" long: ");
  Serial.print(longitude,6);
Serial.print("\t");
        lng_str = String(longitude,6);
      }
    }
  // Check if a client has connected
//  WiFiClient client = server.available();
//  if(ss.available() == 0)
//  {Serial.print ("no gps");
//  delay(1000);
//  Serial.print('\n');
//  }
  if (!client)
  {
    return;
  }

 
  delay(100);


}
