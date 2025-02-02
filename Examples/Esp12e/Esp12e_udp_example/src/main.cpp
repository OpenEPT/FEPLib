/*
 Basic ESP8266 MQTT example
 This sketch demonstrates the capabilities of the pubsub library in combination
 with the ESP8266 board/library.
 It connects to an MQTT server then:
  - publishes "hello world" to the topic "outTopic" every two seconds
  - subscribes to the topic "inTopic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary
  - If the first character of the topic "inTopic" is an 1, switch ON the ESP Led,
    else switch it off
 It will reconnect to the server if the connection is lost using a blocking
 reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
 achieve the same result without blocking the main loop.
 To install the ESP8266 board, (using Arduino 1.6.4+):
  - Add the following 3rd party board manager under "File -> Preferences -> Additional Boards Manager URLs":
       http://arduino.esp8266.com/stable/package_esp8266com_index.json
  - Open the "Tools -> Board -> Board Manager" and click install for the ESP8266"
  - Select your ESP8266 in "Tools -> Board"
*/

#include <Arduino.h>
#include <openept_ed.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define BUILTIN_LED 2

const char *ssid = "5G High Freqyency";
const char *password = "21051995";

WiFiUDP Udp;
unsigned int localUdpPort = 53615;
const char *text = "DATA AAA1";
char big_niz[1000];
char data_string[255];
unsigned int cnt;
unsigned int cnt1;


typedef enum
{
	ACTION_BIG,
	ACTION_SMALL
}action_t;
action_t currentAction;
int iterationNo;
void setup() {
	memset(big_niz, 'A', sizeof(big_niz));
	digitalWrite(BUILTIN_LED, HIGH);
	OpenEPT_ED_Init();
	OpenEPT_ED_SendInfo("Try to start EP Link");
	pinMode(BUILTIN_LED, OUTPUT);
	OpenEPT_ED_Start();
	OpenEPT_ED_SendInfo("EP Link started");
	WiFi.begin(ssid, password);
	//Connect to AP
    while (WiFi.status() != WL_CONNECTED){
		delay(500);
		Serial.print(".");
  	}
	digitalWrite(BUILTIN_LED, LOW);
	//print a new line, then print WiFi connected and the IP address
	OpenEPT_ED_SendInfo("Wifi Connecting");
	WiFi.setAutoReconnect(true);
  	WiFi.persistent(true);
	// Print the IP address assigned to ESP-12E
	OpenEPT_ED_SendInfo("Connecting done");
	OpenEPT_ED_SendInfo("IP Addr:");
	OpenEPT_ED_SendInfo((const char*)WiFi.localIP().toString().c_str());
	OpenEPT_ED_SendInfo("Access Point IP Address: ");
  	OpenEPT_ED_SendInfo((const char*)WiFi.gatewayIP().toString().c_str());  // This is the router's IP address
	
	Udp.begin(localUdpPort);

	currentAction = ACTION_BIG;
	iterationNo = 0;
	cnt1 = 0;
}
void loop() 
{	
	//Send dummy data
	
	switch(currentAction)
	{
		case ACTION_BIG:
			snprintf(data_string, sizeof(data_string), "DataL sending %u", cnt);
			OpenEPT_ED_SetEPFast((uint8_t*)data_string, strlen(data_string));
			for(int i = 0; i < 10; i++)
			{
				Udp.beginPacket("192.168.2.100", localUdpPort); // <- Check address for AP, this is hardcoded
				Udp.write(big_niz);
				Udp.endPacket();
				delay(10);		
			}
			snprintf(data_string, sizeof(data_string), "DataL sent %u", cnt);
			OpenEPT_ED_SetEPFast((uint8_t*)data_string, strlen(data_string));
		break;
		case ACTION_SMALL:
			snprintf(data_string, sizeof(data_string), "DataS sending %u", cnt);
			OpenEPT_ED_SetEPFast((uint8_t*)data_string, strlen(data_string));		
			Udp.beginPacket("192.168.2.100", localUdpPort); // <- Check address for AP, this is hardcoded
			Udp.write(text);
			Udp.endPacket();
			snprintf(data_string, sizeof(data_string), "DataS sent %u", cnt);
			OpenEPT_ED_SetEPFast((uint8_t*)data_string, strlen(data_string));
		break;
	}
	if (WiFi.status() != WL_CONNECTED) {
		digitalWrite(BUILTIN_LED, HIGH);
	}
	else {
		digitalWrite(BUILTIN_LED, LOW);
	}
	cnt++;
	iterationNo +=1;
	if(iterationNo % 5 == 0)
	{
		currentAction = currentAction == ACTION_BIG ? ACTION_SMALL : ACTION_BIG;
		OpenEPT_ED_SendInfo("Try to stop EP Link");
		snprintf(data_string, sizeof(data_string), "STOP %u", cnt1);
		OpenEPT_ED_SetEPFast((uint8_t*)data_string, strlen(data_string));
		OpenEPT_ED_Stop();	
		delay(10000);
		OpenEPT_ED_SendInfo("Try to Establish EP Link");
		OpenEPT_ED_Start();
		cnt1 += 1;
		snprintf(data_string, sizeof(data_string), "START %u", cnt1);
		OpenEPT_ED_SetEPFast((uint8_t*)data_string, strlen(data_string));
	}
	else
	{
		delay(1000);
	}
	//if (iterationNo == 10) ESP.deepSleep(5000000);

}
