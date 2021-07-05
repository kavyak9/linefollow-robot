int MA1=D1,MA2=D2,MB1=D5,MB2=D6,IR1=D7,IR2=D8;

#include <ESP8266WiFi.h>
const char* ssid     = "Infinix";
const char* password = "abcdefgh";
const char* host = "192.168.43.21";
WiFiClient client;
String url = "/d10.php";

int count=0;

int d;
void connection();
void setup() {
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(MA1, OUTPUT);
  pinMode(MA2, OUTPUT);
  pinMode(MB1, OUTPUT);
  pinMode(MB2, OUTPUT);


  
  Serial.begin(115200);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());\
  Serial.print("connecting to ");
  Serial.println(host);  

}



void loop() {


  
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
 // Serial.print("Requesting URL: ");
  //Serial.println(url);
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
     if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  while(client.available()>0) {
    String line = client.readStringUntil('\r');
   
    count=count+1;

     if(count==9)
     {
      Serial.println(line);
d=line.toInt();
     } 


if((d)==1)
{
  Serial.println("turning right");

  digitalWrite(MA1,LOW);
  digitalWrite(MA2,HIGH);                       
  digitalWrite(MB1,LOW);
  digitalWrite(MB2,HIGH);

 
  
  }
else if((d)==2)
{
  Serial.println("turning left");
  
  digitalWrite(MA1,HIGH);
  digitalWrite(MA2,LOW);                       
  digitalWrite(MB1,HIGH);
  digitalWrite(MB2,LOW);


  }

else if((d)==3)
{
  Serial.println("going forward");

  digitalWrite(MA1,HIGH);
  digitalWrite(MA2,LOW);                       
  digitalWrite(MB1,LOW);
  digitalWrite(MB2,HIGH);

  }

else if((d)==4)
{
  Serial.println("going backward");

  digitalWrite(MA1,LOW);
  digitalWrite(MA2,HIGH);                       
  digitalWrite(MB1,HIGH);
  digitalWrite(MB2,LOW);


  }
else
{ 
  Serial.println("stop");

  digitalWrite(MA1,HIGH);
  digitalWrite(MA2,HIGH);                       
  digitalWrite(MB1,HIGH);
  digitalWrite(MB2,HIGH);
 
  
  }


         
  }
count=0;

 


 
}  

