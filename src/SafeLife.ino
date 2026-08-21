#include <DHT.h>
#include <SoftwareSerial.h>

#define PIR_PIN 2
#define DHT_PIN 3
#define BUZZER_PIN 7
#define RESET_PIN 4

// ===== LEDS =====
#define LED_RED 5
#define LED_GREEN 6


SoftwareSerial sim800(10, 11);
DHT dht(DHT_PIN, DHT11);


const char phone[] = "+989360576255";


// ================= STATE =================

enum State { ACTIVE, COOLDOWN };

State systemState = ACTIVE;


// ================= TIMERS =================

unsigned long cooldownStart = 0;

const unsigned long cooldownTime = 300000UL;


// motion stability

unsigned long motionStartTime = 0;

bool motionStable = false;


// temp tracking

unsigned long tempStartTime = 0;

float lastTemp = 0;


// ================= RESET =================

void resetSystem() {

  Serial.println("EVENT: RESET");


  systemState = ACTIVE;

  cooldownStart = 0;


  motionStable = false;

  motionStartTime = 0;


  tempStartTime = 0;


  digitalWrite(BUZZER_PIN, LOW);


  sendSMS("SYSTEM RESET - READY");

}



// ================= SMS =================

bool sendSMS(String msg) {


  sim800.println("AT+CMGF=1");

  delay(500);


  sim800.print("AT+CMGS=\"");

  sim800.print(phone);

  sim800.println("\"");


  delay(500);


  sim800.print(msg);


  delay(500);


  sim800.write(26);


  delay(3000);


  return true;

}



// ================= CALL =================

bool makeCall() {


  Serial.println("CALLING...");


  sim800.println("ATD+989360576255;");


  delay(15000);


  sim800.println("ATH");


  Serial.println("CALL END");


  return true;

}



// ================= TEMP =================

float readTemp() {


  float t = dht.readTemperature();


  if (isnan(t))

    return lastTemp;


  lastTemp = t;


  return t;

}
// ================= RISK =================

int getRisk(bool motion, float temp) {


  if (!motion)

    return 0;


  int risk = 40;


  // دمای بالا

  if (temp > 28)

    risk += 30;


  // دمای بحرانی

  if (temp > 35)

    risk += 30;


  return risk;

}




// ================= SETUP =================

void setup() {


  pinMode(PIR_PIN, INPUT);


  pinMode(BUZZER_PIN, OUTPUT);


  pinMode(RESET_PIN, INPUT_PULLUP);



  pinMode(LED_RED, OUTPUT);


  pinMode(LED_GREEN, OUTPUT);



  Serial.begin(9600);


  sim800.begin(9600);


  dht.begin();



  delay(15000);


  sendSMS("SYSTEM ONLINE");

}





// ================= LOOP =================

void loop() {



  // ================= LED =================


  static unsigned long ledTimer = 0;


  static bool ledState = false;



  if (millis() - ledTimer >= 500) {


    ledTimer = millis();


    ledState = !ledState;


    digitalWrite(LED_RED, ledState);


    digitalWrite(LED_GREEN, !ledState);


  }






  // ================= RESET =================


  if (digitalRead(RESET_PIN) == LOW) {


    resetSystem();


    delay(500);

  }






  // ================= COOLDOWN =================


  if (systemState == COOLDOWN) {


    digitalWrite(BUZZER_PIN, LOW);



    if (millis() - cooldownStart >= cooldownTime) {


      systemState = ACTIVE;


      Serial.println("EVENT: ACTIVE AGAIN");


    }


    return;

  }






  // ================= SENSOR =================


  int motion = digitalRead(PIR_PIN);


  float temp = readTemp();
// ================= FIRE EMERGENCY =================

if (temp >= 40) {

  digitalWrite(BUZZER_PIN, HIGH);


  String fireMsg = "FIRE ALERT\n";
  fireMsg += "Critical Temperature\nTemp: ";
  fireMsg += String(temp, 1);
  fireMsg += " C";


  Serial.println("FIRE EMERGENCY");


  makeCall();

  sendSMS(fireMsg);



  systemState = COOLDOWN;

  cooldownStart = millis();


  Serial.println("EVENT: FIRE COOLDOWN");


  return;

}





  // ================= MOTION STABILITY =================


  if (motion == HIGH) {


    if (motionStartTime == 0)

      motionStartTime = millis();



    // کاهش حساسیت PIR

    if (millis() - motionStartTime >= 5000)

      motionStable = true;


  }

  else {


    motionStartTime = 0;


    motionStable = false;


  }






  // ================= TEMP TRACKING =================


  if (temp > 28) {


    if (tempStartTime == 0)

      tempStartTime = millis();


  }

  else {


    tempStartTime = 0;


  }

// ================= RISK =================

int risk = getRisk(motionStable, temp);




// ================= BUZZER =================

if (motionStable && risk >= 70) {


  digitalWrite(BUZZER_PIN, HIGH);


}

else {


  digitalWrite(BUZZER_PIN, LOW);


}




// ================= LOG =================

Serial.print("Motion: ");

Serial.print(motionStable);


Serial.print(" Temp: ");

Serial.print(temp);


Serial.print(" Risk: ");

Serial.println(risk);







// ================= ALERT =================

if (motionStable) {


  String msg;



  // ===== حالت 1 : دمای محیط =====

  if (temp < 28) {


    msg = "ALERT\nMotion Detected\nTemp: ";


    msg += String(temp, 1);

    msg += " C";


    sendSMS(msg);


  }




  // ===== حالت 2 : دمای بالا =====

  else if (temp <= 35) {


    msg = "WARNING\nMotion Detected\nHigh Temperature\nTemp: ";


    msg += String(temp, 1);


    msg += " C";


    sendSMS(msg);


  }




  // ===== حالت 3 : دمای بحرانی =====

  else {


    msg = "CRITICAL ALERT\nMotion Detected\nCritical Temperature\nTemp: ";


    msg += String(temp, 1);


    msg += " C";



    Serial.println("CRITICAL - CALL START");



    // اول تماس

    makeCall();



    Serial.println("CRITICAL - CALL END");



    // بعد SMS

    sendSMS(msg);


  }





  systemState = COOLDOWN;


  cooldownStart = millis();



  Serial.println("EVENT: COOLDOWN STARTED");

}


}
