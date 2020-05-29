#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEBeacon.h>

BLEAdvertising *pAdvertising;

#define BEACON_UUID "8ec76ea3-6668-48da-9866-75be8bc86f4d" // UUID 1 128-Bit (may use linux tool uuidgen or random numbers via https://www.uuidgenerator.net/)

uint16_t iBeacon_self_minor = 0;

void iBeacon_init(){
  BLEDevice::init("myESP32");
  pAdvertising = BLEDevice::getAdvertising();
  pAdvertising = BLEDevice::getAdvertising();
}
void iBeacon_set(uint16_t major, uint16_t minor, uint16_t interval) {
  String uuid = BEACON_UUID;
  Serial.println("set uuid: " + uuid);
  Serial.println("set major: " + String(major));
  Serial.println("set minor: " + String(minor));
  iBeacon_self_minor = minor;
  BLEBeacon oBeacon = BLEBeacon();
  oBeacon.setManufacturerId(0x4C00); // fake Apple 0x004C LSB (ENDIAN_CHANGE_U16!)
  oBeacon.setProximityUUID(BLEUUID(uuid.c_str()));
  oBeacon.setMajor(major);
  oBeacon.setMinor(minor);
  oBeacon.setSignalPower(0xc5);
  
  BLEAdvertisementData oAdvertisementData = BLEAdvertisementData();
  BLEAdvertisementData oScanResponseData = BLEAdvertisementData();
  
  oAdvertisementData.setFlags(0x06); // General_Discoverable|BR_EDR_NOT_SUPPORTED 0x04
  
  std::string strServiceData = "";
  
  strServiceData += (char)26;     // Len
  strServiceData += (char)0xFF;   // Type
  strServiceData += oBeacon.getData(); 
  oAdvertisementData.addData(strServiceData);

  oScanResponseData.setShortName("esp_ble");
  
  pAdvertising->setScanResponseData(oScanResponseData);
  pAdvertising->setAdvertisementData(oAdvertisementData);
  pAdvertising->setScanResponseData(oScanResponseData);
  
  pAdvertising->setMinInterval(interval/0.635); // setMinInterval
  pAdvertising->setMaxInterval(interval/0.635); // setMaxInterval
}

void iBeacon_start(){
  pAdvertising->start();
  Serial.println("Advertizing started...");
}

void iBeacon_stop(){
  pAdvertising->stop();
  Serial.println("Advertizing stop...");
}
  
