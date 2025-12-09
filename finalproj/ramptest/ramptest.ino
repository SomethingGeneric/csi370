// Matt C CSI 370 Final Project

// Pin definitions
#define PWMA 10
#define AIN1 6
#define AIN2 7

extern "C" {
  void setup_timer1_pwm(void);
  void set_pwm_duty(uint8_t duty);
  void precise_delay_ms(uint16_t milliseconds);
}

void setup() {
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  
  Serial.begin(9600);
  setup_timer1_pwm();
  
  Serial.println("Finding minimum duty cycle...");
  Serial.println("Press key to start ramp test");
}

void loop() {
  while(Serial.available() == 0) {}
  while(Serial.available() > 0) { Serial.read(); }
  
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  
  // Ramp from 0 to 255 in steps of 10
  for(int duty = 0; duty <= 255; duty += 10) {
    Serial.print("Duty cycle: ");
    Serial.print(duty);
    Serial.print(" (");
    Serial.print((duty * 100) / 255);
    Serial.println("%)");
    
    set_pwm_duty(duty);
    precise_delay_ms(2000);  // 2 seconds at each level
  }
  
  // Stop
  set_pwm_duty(0);
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  Serial.println("Test complete. Press key to repeat.");
}

// Assembly code (same as before)
asm(
  ".global setup_timer1_pwm\n"
  "setup_timer1_pwm:\n"
  "  push r16\n"
  "  ldi r16, 0x21\n"
  "  sts 0x80, r16\n"
  "  ldi r16, 0x0A\n"
  "  sts 0x81, r16\n"
  "  ldi r16, 0\n"
  "  sts 0x8A, r16\n"
  "  sts 0x8B, r16\n"
  "  pop r16\n"
  "  ret\n"
);

asm(
  ".global set_pwm_duty\n"
  "set_pwm_duty:\n"
  "  push r16\n"
  "  mov r16, r24\n"
  "  sts 0x8A, r16\n"
  "  ldi r16, 0\n"
  "  sts 0x8B, r16\n"
  "  pop r16\n"
  "  ret\n"
);

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