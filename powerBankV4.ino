
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 32, &Wire, -1);

int cell_1_adc;
int cell_2_adc;
int cell_3_adc;
int cell_4_adc;
int cell_5_adc;

float cell_1_voltage;
float cell_2_voltage;
float cell_3_voltage;
float cell_4_voltage;
float cell_5_voltage;

float cell_1_single;
float cell_2_single;
float cell_3_single;
float cell_4_single;
float cell_5_single;

float battery_percentage;


void setup() {

 pinMode(A6, INPUT);
 pinMode(A3, INPUT);
 pinMode(A2, INPUT);
 pinMode(A1, INPUT);
 pinMode(A0, INPUT);

  Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
  {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
display.clearDisplay();
display.setTextColor(SSD1306_WHITE);
}

void loop() {

// Storing ADC Value //////////////////////////////////

cell_1_adc = analogRead(A6);
cell_2_adc = analogRead(A3);
cell_3_adc = analogRead(A2);
cell_4_adc = analogRead(A1);
cell_5_adc = analogRead(A0);

// Calculate Pin Voltage after divider ///////////////

cell_1_voltage = cell_1_adc * (5.0 / 1023.0);
cell_1_voltage = cell_1_voltage * 4.15 / 4.15;

cell_2_voltage = cell_2_adc * (5.0 / 1023.0) * ((6.8 + 5.1) / 6.8);
cell_2_voltage = cell_2_voltage * 8.26 / 8.38;

cell_3_voltage = cell_3_adc * (5.0 / 1023.0) * ((5.1 + 10) / 5.1);
cell_3_voltage = cell_3_voltage * 12.37 / 12.26;

cell_4_voltage = cell_4_adc * (5.0 / 1023.0) * ((20 + 51) / 20);
cell_4_voltage = cell_4_voltage * 16.54 / 13.97;

cell_5_voltage = cell_5_adc * (5.0 / 1023.0) * ((20 + 68) / 20);
cell_5_voltage = cell_5_voltage * 20.6 / 18.89;

cell_5_single = cell_5_voltage - cell_4_voltage;
cell_4_single = cell_4_voltage - cell_3_voltage;
cell_3_single = cell_3_voltage - cell_2_voltage;
cell_2_single = cell_2_voltage - cell_1_voltage;

battery_percentage = ((cell_5_voltage - 15) / (21 - 15)) * 100;

float cellVoltages[5] = {cell_1_voltage, cell_2_single, cell_3_single, cell_4_single, cell_5_single};

Serial.println("##############################");

for (int i = 0; i < 5; ++i) {
  Serial.print("cell_" + String(i + 1) + ": ");
  Serial.println(cellVoltages[i]);
}

Serial.print("Battery percent: ");
Serial.println(battery_percentage);

Serial.println("##############################");

display.clearDisplay();

  display.setTextSize(1); 
  display.setCursor(0, 1);
  display.println(F("C1:"));
  display.setCursor(20, 1);
  display.print(cell_1_voltage, 2);
  display.println(F("V")); 


  ///////////////////////////////////////////////////////////


  display.setTextSize(1);  // Set text size to 2 (adjust as needed)
  display.setCursor(0, 10); //x, y
  display.println(F("C2:"));
  display.setCursor(20, 11);
  display.print(cell_2_single, 2); // Print adjusted voltage with 2 decimal places
  display.println(F("V")); // Print "V" and move to the next line


  ///////////////////////////////////////////////////////////


  display.setTextSize(1);  // Set text size to 2 (adjust as needed)
  display.setCursor(0, 20); //x, y
  display.println(F("C3:"));
  display.setCursor(20, 20);
  display.print(cell_3_single, 2); // Print adjusted voltage with 2 decimal places
  display.println(F("V")); // Print "V" and move to the next line

  ///////////////////////////////////////////////////////////


  display.setTextSize(1);  // Set text size to 2 (adjust as needed)
  display.setCursor(60, 0); //x, y
  display.println(F("C4:"));
  display.setCursor(80, 0);
  display.print(cell_4_single, 2); // Print adjusted voltage with 2 decimal places
  display.println(F("V")); // Print "V" and move to the next line

  ///////////////////////////////////////////////////////////


  display.setTextSize(1);  // Set text size to 2 (adjust as needed)
  display.setCursor(60, 10); //x, y
  display.println(F("C5:"));
  display.setCursor(80, 10);
  display.print(cell_5_single, 2); // Print adjusted voltage with 2 decimal places
  display.println(F("V")); // Print "V" and move to the next line

  ///////////////////////////////////////////////////////////


  display.setTextSize(1);  // Set text size to 2 (adjust as needed)
  display.setCursor(60, 20); //x, y
  display.println(F("CA:"));
  display.setCursor(80, 20);
  display.print(cell_5_voltage, 2); // Print adjusted voltage with 2 decimal places
  display.println(F("V")); // Print "V" and move to the next line

  display.display();

  delay(700);

  display.clearDisplay();

  display.setTextSize(1);  // Set text size to 2 (adjust as needed)
  display.setCursor(20, 5); //x, y
  display.println(F("BATTERY PERCENT"));
  display.setCursor(60, 15);
  display.print(battery_percentage, 2); // Print adjusted voltage with 2 decimal places
  display.println(F("%")); // Print "V" and move to the next line 

  display.display();

  delay(700);

}