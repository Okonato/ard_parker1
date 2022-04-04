
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


// Define Trig and Echo pin:
#define trigPin 14
#define echoPin 12
#define  Led  16
#define  buzzer 13

#define TONE_USE_INT
#define TONE_PITCH 434
#include <Pitch.h>
#include "pitches.h"
//#include "themes.h"
#include "starw.h"

/////////////
int melody[] = {
  
  // Dart Vader theme (Imperial March) - Star wars 
  // Score available at https://musescore.com/user/202909/scores/1141521
  // The tenor saxophone part was used
  
  NOTE_AS4,8, NOTE_AS4,8, NOTE_AS4,8,//1
  NOTE_F5,2, NOTE_C6,2,
  NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F6,2, NOTE_C6,4,  
  NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F6,2, NOTE_C6,4,  
  NOTE_AS5,8, NOTE_A5,8, NOTE_AS5,8, NOTE_G5,2, NOTE_C5,8, NOTE_C5,8, NOTE_C5,8,
  NOTE_F5,2, NOTE_C6,2,
  NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F6,2, NOTE_C6,4,  
  
  NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F6,2, NOTE_C6,4, //8  
  NOTE_AS5,8, NOTE_A5,8, NOTE_AS5,8, NOTE_G5,2, NOTE_C5,-8, NOTE_C5,16, 
  NOTE_D5,-4, NOTE_D5,8, NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F5,8,
  NOTE_F5,8, NOTE_G5,8, NOTE_A5,8, NOTE_G5,4, NOTE_D5,8, NOTE_E5,4,NOTE_C5,-8, NOTE_C5,16,
  NOTE_D5,-4, NOTE_D5,8, NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F5,8,
  
  NOTE_C6,-8, NOTE_G5,16, NOTE_G5,2, REST,8, NOTE_C5,8,//13
  NOTE_D5,-4, NOTE_D5,8, NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F5,8,
  NOTE_F5,8, NOTE_G5,8, NOTE_A5,8, NOTE_G5,4, NOTE_D5,8, NOTE_E5,4,NOTE_C6,-8, NOTE_C6,16,
  NOTE_F6,4, NOTE_DS6,8, NOTE_CS6,4, NOTE_C6,8, NOTE_AS5,4, NOTE_GS5,8, NOTE_G5,4, NOTE_F5,8,
  NOTE_C6,1
  
};

// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int notes = sizeof(melody) / sizeof(melody[0]) / 2;

// this calculates the duration of a whole note in ms
int wholenote = (60000 * 4) / tempo;

int divider = 0, noteDuration = 0;
/////////////
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels


// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ 0b00000000, 0b11000000,
  0b00000001, 0b11000000,
  0b00000001, 0b11000000,
  0b00000011, 0b11100000,
  0b11110011, 0b11100000,
  0b11111110, 0b11111000,
  0b01111110, 0b11111111,
  0b00110011, 0b10011111,
  0b00011111, 0b11111100,
  0b00001101, 0b01110000,
  0b00011011, 0b10100000,
  0b00111111, 0b11100000,
  0b00111111, 0b11110000,
  0b01111100, 0b11110000,
  0b01110000, 0b01110000,
  0b00000000, 0b00110000 };

  // Define variables:
long duration;
int distance;
int maks_odl=300;
int czas_przerwy=2000;
int dzwiek_czas=500;
  
unsigned long dzwiek_przerwa,   swieci=600;
unsigned long przerwa_zapis=0,  przerwa=300;

////// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&  gdy odl mniejsza od granicznej 
void miga(float odl){

//przerwa=round((1-(odl/100))*czas_przerwy);

przerwa=round(((odl/100))*czas_przerwy);

//przerwa1=((odl)/(maks));//*2000;
if (millis()%200==0) 
{Serial.print(odl);  Serial.print(" przerwa=");  Serial.println(przerwa);}
//delay(100);

unsigned long  roznica_czasu,roznica_czasu_dzwiek;
  roznica_czasu=millis()-przerwa_zapis;
  if (digitalRead(Led)==LOW and roznica_czasu>przerwa)
  {
    digitalWrite(Led,HIGH);
  tone(buzzer, NOTE_E1, 200);
    przerwa_zapis=millis();
  }
  else
  if (digitalRead(Led)==HIGH and roznica_czasu>przerwa)
  {
    digitalWrite(Led,LOW);
    przerwa_zapis=millis();
  }
}

///// *****************
void Play_CrazyFrog()
{
/*
  for (int thisNote = 0; thisNote < (sizeof(CrazyFrog_note)/sizeof(int)); thisNote++) {

    int noteDuration = 1000 / CrazyFrog_duration[thisNote]; //convert duration to time delay
    tone(8, CrazyFrog_note[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.30;//Here 1.30 is tempo, decrease to play it faster
    delay(pauseBetweenNotes);
    noTone(8); //stop music on pin 8 
    }
    */
}
/// *************************************
void setup() {
//// &&&&&&&&&&&&&&

 for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, melody[thisNote], noteDuration*0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);
    
    // stop the waveform generation before the next note.
    noTone(buzzer);
  }

///// &&&&&&&&&&&&&&&

    // Define inputs and outputs:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(Led, OUTPUT);  
  pinMode(buzzer, OUTPUT);  

  
  Serial.begin(9600);
/*
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  */

    // sygnal dzwikowy START
    digitalWrite(Led, LOW);
 tone(buzzer, NOTE_G3, 500);
    delay(500);    
    digitalWrite(Led, HIGH);
 tone(buzzer, NOTE_G1, 300);
    delay(500); 
    delay(200);
    digitalWrite(Led, LOW);
 tone(buzzer, NOTE_E1, 200);
    delay(100);    
    digitalWrite(Led, HIGH);
  digitalWrite(buzzer,LOW);
////////////
  Serial.println("OLED FeatherWing test");
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32

////////////
  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
 // Clear the buffer
  display.clearDisplay();

  // Draw a single pixel in white
  display.drawPixel(10, 10, SSD1306_WHITE);

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
  delay(200);


//  testanimate(logo_bmp, LOGO_WIDTH, LOGO_HEIGHT); // Animate bitmaps

     display.clearDisplay();

  display.setTextSize(3); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  delay(10);
  display.setCursor(10, 0);
  display.println(F("START"));
  display.display();  
  display.setCursor(0, 10);
  display.write(219); 
  delay(20);
    display.display();      // Show initial text  
 // delay(200);
  for(int i=0;i<100;i++)
  {
    display.setCursor(i, 10);
    display.write(219); 
    delay(1);
    display.display();      // Show initial text
  }
  display.clearDisplay();
  display.invertDisplay(false);

//delay(200);
}

void loop() {
  
///////// &&&&&&&&&&&&&&&&&&&&&&&&
odczyt_odl();  // odczytuje odlebuzzerc i wyrzuca WART "distance"

display.setTextSize(2); // Draw 2X-scale text
display.setTextColor(SSD1306_WHITE);
 
//Serial.print(" Odlebuzzerc = ");  Serial.print(distance);  Serial.println(" cm    ");

display.clearDisplay();

if(distance>maks_odl) distance=maks_odl;  // wartosc graniczna MAX odległosci

int procent=(distance*100)/200;
if(procent>100) procent=100;

display.setCursor(10, 0);
  if(distance<200)   
  {
  miga(procent);   // co ma zrobic miganie 
    display.print(distance);
    display.print("");  
  }
  else
  {
   digitalWrite(Led,HIGH);
    display.print(">200");
  }
  display.setCursor(65, 0);   display.print((procent)); 
  display.setCursor(105, 0);    display.print("%");
  display.fillRect(10, 20, procent, 8, WHITE);
  display.display(); 

  display.display();      // Show initial text
  delay(10);

  /// &&&&&&&&&&&&&&&&&&&&&&

}

  ////// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&  odczytyje odlebuzzerc z modulu ECHO
void odczyt_odl()
{
// Clear the trigPin by setting it LOW:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);

  // Trigger the sensor by setting the trigPin high for 10 microseconds:
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echoPin, pulseIn() returns the duration (length of the pulse) in microseconds:
  // Calculate the distance:
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  
//  return distance;
}
