#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <ESP8266WebServer.h>

// Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
ESP8266WebServer server(80);

int leftPin = 12;
int rightPin = 14;

int speedL = 0;
int speedR = 0;

void setup() {
  Serial.begin(9600);

  pinMode(12, OUTPUT);
  pinMode(14, OUTPUT);

  digitalWrite(12, LOW);
  digitalWrite(14, LOW);

  /*
  pwm.begin();
  pwm.setPWMFreq(1600);

  pwm.setPWM(15, 0, 4096);
  pwm.setPWM(14, 0, 4096);
  */

  Serial.print("Setting soft-AP ... ");
  WiFi.begin("FIXME-NAT", "hs1337_FIXME");
  WiFi.hostname("codefast");

  Serial.print("Connecting");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("Connected!");
  Serial.println(WiFi.localIP());
  

  launchServer();
}

void loop() {
  server.handleClient();

  long scale = 1000;
  delayMicroseconds(speedL * scale);

  digitalWrite(leftPin, LOW);
  digitalWrite(rightPin, LOW);

  delayMicroseconds(100 * scale - speedL * scale);
  
  digitalWrite(leftPin, HIGH);
  digitalWrite(rightPin, HIGH);
  
}

void launchServer() {
  Serial.println("Lauching web server...");
  
  // Routes
  server.on("/", sendOK);
  server.on("/on", setOn);

  server.begin();
  
  Serial.println("Web server ready!");
}

void sendOK() {
  server.send(200, "text/plain", "OK");
}

void setOn() {
  String message = "";
  
  if (server.arg("left") == "") {
    message += "Left argument not found\n";
  } else {     //Parameter found
    speedL = _max(_min(server.arg("left").toInt(), 100), 0);
    Serial.println("Left speed: " + server.arg("left") + "%");
  }
  
  if (server.arg("right") == "") {
    // Parameter not found
    message += "Right argument not found\n";
  } else {
    speedR = _max(_min(server.arg("right").toInt(), 100), 0);
    Serial.println("Right speed: " + server.arg("right") + "%");
  }
  
  message += "OK\n";
  
  server.send(200, "text/plain", message);
}



