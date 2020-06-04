#define LED0       25
#define LED1       26
#define BUZZER     27

#define LED_ON(LED)    digitalWrite(LED, HIGH)
#define LED_OFF(LED)   digitalWrite(LED, LOW)

#define  BUZZER_ON()   digitalWrite(BUZZER, HIGH)
#define  BUZZER_OFF()  digitalWrite(BUZZER, LOW)

boolean state = false;

void notif_cardpresent();
void notif_accessgrant();
void notif_accessreject();

void notif_init(){
  pinMode(LED0,OUTPUT);
  pinMode(LED1,OUTPUT);
  pinMode(BUZZER,OUTPUT);
}

void notif_beep(uint8_t counter, uint16_t longbeep){
  for(uint8_t i=1; i<=counter; i++){
    LED_ON(LED0);
    BUZZER_ON();
    delay(longbeep);
    LED_OFF(LED0);
    BUZZER_OFF();
    delay(longbeep);
  }  
}

void notif_powerup(){
  notif_beep(2,100);
}

void notif_accessgrant(){
  notif_beep(1,100);
}

void notif_accessreject(){
  notif_beep(2,500);
}
void notif_network_connected(){
  state = !state; 
  digitalWrite(LED1,state);
}
void notif_network_notconnected(){
  digitalWrite(LED1,false);
}
