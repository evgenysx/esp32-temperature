#include <Arduino.h>

#include "cekwifi.h"
//
#include "sensors.h"
#include "panel.h"

#include "OneWire.h"
#include "DallasTemperature.h"

#include "mqtt.h"
#include "settings.h"
#include "gprs.h"

#include "Update.h"
#define ONE_WIRE_BUS 15
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

#define SENSOR_TEMPERATURE_2 13
OneWire oneWireTempr2(SENSOR_TEMPERATURE_2);
DallasTemperature sensorsTempr2(&oneWireTempr2);


MqttClient mqttWifiClient;
/* create an instance of PubSubClient client */
WiFiClient espClient;

MqttClient mqttGprsClient;

GsmCustomClient* gsmClient;

cek::EepromSettings settings;


void setup() {
  //mqttWifiClient.setClient(espClient);

  Serial.begin(115200);
  Serial2.begin(9600);

  if(!cek::loadSettings()){
    Serial.println("Не найдена известная прошивка");
    // auto settings = cek::getEepromSettings();
    // settings.version = 2;
    // settings.name = "cek_solar_enya";
    // if(!settings.save()){
    //   Serial.println("Не удалось сохранить прошивку");
    // }
    // Serial.println("Cохранена прошивка " + settings.name + " / версия " + String(settings.version));
  }else{
    settings = cek::getEepromSettings();
    //  settings.wifi.ssid = "GalaxyM51";
    //  settings.wifi.pwd = "Kvmw9630";

    // if(!settings.save()) n
    //    Serial.println("Не удалось сохранить прошивку");
    


    Serial.println("Загружена прошивка " + settings.name + " / версия " + String(settings.version));
    Serial.println("Wifi " + settings.wifi.ssid);
  }
  auto uid = String(ESP.getEfuseMac() >> 30);
  //initAPWifi(uid);
  
  initWifi(settings.wifi.ssid, settings.wifi.pwd);
  cek::ws_bus::startHttpServer();
  cek::sensors::init();
  
  // registerHandler("222");
  // std::function<void()> serverHandler;
  //registerHandler("/api/sendSMS", )
  // gsmClient = GsmCustomClient::create(Serial2);

  // cek::ws_bus::notify(cek::ws_bus::eEventType::GsmUpdateBattPercent, gsmClient->getBattPercent());
  // gsmClient->initGPRS();
  // auto bal = gsmClient->getBalance("*100#");
  // Serial.println("balance = " + bal);
  // gsmClient->sendSMS("+79081608348", "Test esp32");
  //gsmClient->initGPRS();

  //mqttGprsClient.setClient(getGsmClient());
  // delay(3000);
  // test_sim800_module();
  // delay(5000);
  //send_SMS();

  return;
  Serial.begin(115200); 
  initWifi(settings.wifi.ssid, settings.wifi.pwd);
  // Запуск библиотеки
  sensors.begin();
  sensorsTempr2.begin();



  
}




void loop() {
  //updateSerial();
  //gprsLoop();


  // Serial.println("signal quality = " + String(gsmClient->getSignalQuality()));
  // Serial.println("battery level = " + String(gsmClient->getBattPercent()));
  // Serial.println(gsmClient->getBalance("*100#"));
  


  // mqttGprsClient.mqttconnect();
  // mqttGprsClient.loop();
  /*
 // запрашиваем sensor.requestTemperatures() для получения глобальной температуры
  // запрос всех устройств на шине
  
  sensors.requestTemperatures(); // Отправляем команды для получения температуры
  sensorsTempr2.requestTemperatures(); // Отправляем команды для получения температуры

  auto temperature = sensors.getTempCByIndex(0);
  auto temperature2 = sensorsTempr2.getTempCByIndex(0);
  Serial.println(temperature);
  Serial.println(temperature2); // Почему "byIndex"? 
    // У вас может быть несколько IC на одной шине. 
    // 0 относится к первой IC

  mqttClient.publish("cek/sp2/tmr1", temperature);
  mqttClient.publish("cek/sp2/tmr2", temperature2);
  

  delay(3000);*/

  //mqttGprsClient.publish("cek/sp2/tmr1", 30.2);
 
  //delay(10000);
}


