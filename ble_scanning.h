#define NUMBEROFBEACON 100

typedef struct BLE {
  int minor;
  int rss;
  int counter;
  unsigned long time;
  bool flag_detect;
}BLE_t;

BLE_t b[NUMBEROFBEACON];

char rawData[26];
char uuid[16];
uint8_t i = 0;

//function prototype
void ble_scan_init();
void read_ble();
double calculateDistance(double rssi);

void ble_scan_init(){
  Serial2.begin(115200);
  delay(100);
}

void read_ble(){
  if(Serial2.available()){
  char in=Serial2.read();
  if(in=='B'){
   rawData[0]=in;
   uint8_t sum = 0;
   String uuidf = "";
   
   for(i=1;i<=26;i++)
   {
    rawData[i]=Serial2.read();
    if(i>=2 && i<=24)sum+=rawData[i];
   }
   delay(10);
   if(rawData[0] == 'B' && rawData[1] == 'T' && rawData[26]=='\n' && sum==rawData[25] && sum!=0){
    for(i=0;i<=15;i++)
    {
        uuid[i]=rawData[i+2];
        uuidf+=uuid[i];
    }
    uint16_t cardMajor=rawData[18];
    cardMajor=(cardMajor<<8) + rawData[19];

    uint16_t cardMinor=rawData[20];
    cardMinor=(cardMinor<<8) + rawData[21];

    int rssi = rawData[22];
    rssi = ~rssi;
    rssi = rssi+B01;
    rssi = rssi & 0xff;
    rssi = ~rssi;

    double rss = rssi;
    double distance = calculateDistance(rss);
    if(distance <= proximity){
      for(i=0; i<NUMBEROFBEACON; i++){
               if(cardMinor == b[i].minor){
                b[i].time = millis();
                b[i].rss = rssi;
                b[i].counter += 1;
                Serial.print("Existing :"); Serial.print(b[i].minor); Serial.print("-"); Serial.print(b[i].counter); Serial.print("-"); Serial.println(b[i].time);
                return;
              }
            }
            for(int j=0; j<NUMBEROFBEACON; j++){
              if(b[j].minor == NULL){
                b[j].minor = cardMinor;
                b[j].time = millis();
                b[j].rss = rssi;
                b[j].counter += 1;
                Serial.print("append success ->"); Serial.println(b[j].minor);
                return;
            }
          }
        }   
      }
    }
  }
}

double calculateDistance(double rssi) {
    float txPower = -59.0;
    if (rssi == 0) {
        return -1.0; // if we cannot determine distance, return -1.
    }
    double ratio = rssi * 1.0 / txPower;

    if (ratio < 1.0) {
        return pow(ratio, 10);
    } 
    else {
        double accuracy = (0.89976) * pow(ratio, 7.7095) + 0.111;
        return accuracy;
    }
}
