// Libraries
#include <Arduino.h>

#include <SPI.h>
#include <Wire.h>

#include <WiFi.h>
#include <WebServer.h>

#include <ArduinoJson.h>
#include <Adafruit_GFX.h>

#include <Adafruit_SSD1306.h>
#include <MFRC522.h>
#include <SD.h> 
#include <Adafruit_BMP280.h>


// pins
#define GREEN_LED ??
#define RED_LED ??
#define BUZZER ??
#define BUTTON ??
#define POT ??
#define FAN_PWM ??

#define SCL 33 // i2c communication MPE280
#define SDA 32

#define MOSI 23    // shared spi pins  // mosi or/and D1
#define MISO 19
#define CLOCK 18  // D0
#define RESET 22 // RST

#define IRQ 0 // inturupt pin for MRC522

#define CS_MFRC552 17 // device select
#define CS_OLED 16
#define CS_SD_CARD 15

#define DC_OLED 4
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// object creation
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, DC_OLED, RESET, CS_OLED); // lab 8

WebServer server(80); // lab 7

// Global variables

const char* ssid = ""; // lab7
const char* password = "password";
uint8_t byte; //byte recording states
unsigned long buzzerStartTime = 0; //buzzer start time
const unsigned long buzzerDuration = 3000; //duration for buzzer
bool buzzerOn = false; //buzzer on or off status, make an ISR

// Functions 

	//Bitwise Manipulation

	void setBit0(){ //set bit 0 to 1
		byte |= 0b00000001;
	}

	void setBit1(){ //set bit 1 to 1
		byte |= 0b00000010;
	}

	void setBit2(){ //set bit 2 to 1
		byte |= 0b00000100;
	}

	void clearBit0(){ //clear bit 0
		byte &= ~(1 << 0);
	}

	void clearBit1(){
		byte &= ~(1 << 1); //clear bit 1
	}

	void clearBit2(){
		byte &= ~(1 << 2); //clear bit 2
	}

	// Room Occupation & Authorization
	
	void authorizedEntry() { 
		digitalWrite(GREEN_LED, HIGH);
		digitalWrite(RED_LED, LOW);
		setBit0();
		//track time somehow
	}

	void unauthorizedEntry(){
		digitalWrite (GREEN_LED, LOW);
		digitalWrite (RED_LED, HIGH);
		//track time somehow
	}

	void emptyRoom(){ //used when authorizedEntry is not being used
		digitalWrite (GREEN_LED, LOW);
		digitalWrite (RED_LED, LOW);
		clearBit0; //clear bit 0
	}

	const float ReadTemp(){
		
	}



void setup() {

	Serial.begin(115200);
	
	WiFi.softAP(ssid,password);
	Serial.print("IP Address =");
	Serial.println(WiFi.softAPIP());

    server.begin();
	Serial.println("web server started");

	  Serial.println("program started ");

  Wire.begin(); //lab6 start
  Serial.println("I2C communication started");
    if (!BMP.begin(0x76)){
    Serial.println("NO BMP280 detected");
    }
    else{
    Serial.println("BMP280 detected");
    } 
  
  Display.begin(SSD1306_SWITCHCAPVCC);
  Display.clearDisplay();
  Display.setTextSize(1);
  Display.setTextColor(WHITE);  
  Display.setCursor(0, 0);
  Display.print("initializing"); 
  Display.display();   //lab 6 end

	pinMode(GREEN_LED, OUTPUT); //set green led as an output
	pinMode(RED_LED, OUTPUT); //set red led as an output
	pinMode(BUZZER, OUTPUT); //set buzzer as an output
	pinMode(FAN_PWM, OUTPUT);

}

void loop() {
  temperature = BMP.readTemperature();
}
