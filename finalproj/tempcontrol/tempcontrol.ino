// Pin definitions
#define PWMA 10
#define AIN1 6
#define AIN2 7

// Temperature thresholds (Fahrenheit)
#define TEMP_LOW 65.0
#define TEMP_HIGH 75.0

// Motor runtime in milliseconds
#define MOTOR_RUN_TIME 500

// Motor speed (0-255)
#define MOTOR_SPEED 10

extern "C" {
  void set_motor_forward(void);
  void set_motor_reverse(void);
  void set_motor_stop(void);
  void precise_delay_ms(uint16_t milliseconds);
}

// Global variables
float currentTemp = 70.0;
String inputString = "";
boolean stringComplete = false;

void setup() {
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  
  Serial.begin(9600);
  inputString.reserve(50);
  
  Serial.println("=================================");
  Serial.println("Temperature-Controlled Window System");
  Serial.println("=================================");
  Serial.println("Send temperature as: TEMP:XX.X");
  Serial.println("Temperature range:");
  Serial.println("  < 65F: Close window (motor reverse)");
  Serial.println("  65-75F: No action");
  Serial.println("  > 75F: Open window (motor forward)");
  Serial.println("=================================");
}

void loop() {
  if (stringComplete) {
    parseTemperature();
    controlMotor();
    
    inputString = "";
    stringComplete = false;
  }
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;
    
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

void parseTemperature() {
  if (inputString.startsWith("TEMP:")) {
    String tempStr = inputString.substring(5);
    currentTemp = tempStr.toFloat();
    
    Serial.print("Received temperature: ");
    Serial.print(currentTemp);
    Serial.println("F");
  } else {
    Serial.println("ERROR: Invalid format. Use TEMP:XX.X");
  }
}

void controlMotor() {
  if (currentTemp < TEMP_LOW) {
    // Too cold - close window (reverse)
    Serial.print("COLD (");
    Serial.print(currentTemp);
    Serial.println("F) - Closing window...");
    
    analogWrite(PWMA, MOTOR_SPEED);
    set_motor_reverse();
    precise_delay_ms(MOTOR_RUN_TIME);
    set_motor_stop();
    analogWrite(PWMA, 0);
    
    Serial.println("Window closed.");
    
  } else if (currentTemp > TEMP_HIGH) {
    // Too hot - open window (forward)
    Serial.print("HOT (");
    Serial.print(currentTemp);
    Serial.println("F) - Opening window...");
    
    analogWrite(PWMA, MOTOR_SPEED);
    set_motor_forward();
    precise_delay_ms(MOTOR_RUN_TIME);
    set_motor_stop();
    analogWrite(PWMA, 0);
    
    Serial.println("Window opened.");
    
  } else {
    // Comfortable range - do nothing
    Serial.print("COMFORTABLE (");
    Serial.print(currentTemp);
    Serial.println("F) - No action needed.");
  }
  
  Serial.println("---------------------------------");
}

// ============================================
// ASSEMBLY FUNCTIONS
// ============================================

// Assembly: Motor forward (AIN1=HIGH, AIN2=LOW)
asm(
  ".global set_motor_forward\n"
  "set_motor_forward:\n"
  "  push r16\n"
  "  in r16, 0x0B\n"      // Read PORTD
  "  ori r16, 0x40\n"     // Set bit 6 (AIN1) HIGH
  "  andi r16, 0x7F\n"    // Clear bit 7 (AIN2) LOW
  "  out 0x0B, r16\n"     // Write PORTD
  "  pop r16\n"
  "  ret\n"
);

// Assembly: Motor reverse (AIN1=LOW, AIN2=HIGH)
asm(
  ".global set_motor_reverse\n"
  "set_motor_reverse:\n"
  "  push r16\n"
  "  in r16, 0x0B\n"      // Read PORTD
  "  andi r16, 0xBF\n"    // Clear bit 6 (AIN1) LOW
  "  ori r16, 0x80\n"     // Set bit 7 (AIN2) HIGH
  "  out 0x0B, r16\n"     // Write PORTD
  "  pop r16\n"
  "  ret\n"
);

// Assembly: Stop motor (both LOW)
asm(
  ".global set_motor_stop\n"
  "set_motor_stop:\n"
  "  push r16\n"
  "  in r16, 0x0B\n"      // Read PORTD
  "  andi r16, 0x3F\n"    // Clear bits 6 and 7
  "  out 0x0B, r16\n"     // Write PORTD
  "  pop r16\n"
  "  ret\n"
);

// Assembly: Precise millisecond delay using cycle-counted loops
// Input: r25:r24 = milliseconds
// At 16MHz, creates accurate delays for motor runtime control
asm(
  ".global precise_delay_ms\n"
  "precise_delay_ms:\n"
  "  push r16\n"
  "  push r17\n"
  "  push r18\n"
  "  push r19\n"
  
  "delay_ms_outer:\n"
  "  cp r24, r1\n"
  "  cpc r25, r1\n"
  "  breq delay_ms_done\n"
  
  "  ldi r18, 16\n"
  "  ldi r19, 250\n"
  
  "delay_ms_inner:\n"
  "  dec r19\n"
  "  brne delay_ms_inner\n"
  "  ldi r19, 250\n"
  "  dec r18\n"
  "  brne delay_ms_inner\n"
  
  "  subi r24, 1\n"
  "  sbci r25, 0\n"
  "  rjmp delay_ms_outer\n"
  
  "delay_ms_done:\n"
  "  pop r19\n"
  "  pop r18\n"
  "  pop r17\n"
  "  pop r16\n"
  "  ret\n"
);