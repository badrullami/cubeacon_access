#include "mbedtls/aes.h"

char *key = "abcdefghijklmnop";
 
void encrypt(unsigned char *plainText, char *key, unsigned char *outputBuffer){
 
  mbedtls_aes_context aes;
 
  mbedtls_aes_init( &aes );
  mbedtls_aes_setkey_enc( &aes, (const unsigned char*) key, strlen(key) * 8 );
  mbedtls_aes_crypt_ecb( &aes, MBEDTLS_AES_ENCRYPT, (const unsigned char*)plainText, outputBuffer);
  mbedtls_aes_free( &aes );
}
 
void decrypt(unsigned char * chipherText, char * key, unsigned char * outputBuffer){
 
  mbedtls_aes_context aes;
 
  mbedtls_aes_init( &aes );
  mbedtls_aes_setkey_dec( &aes, (const unsigned char*) key, strlen(key) * 8 );
  mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_DECRYPT, (const unsigned char*)chipherText, outputBuffer);
  mbedtls_aes_free( &aes );
}

void string_insert (String& string, const char* what, size_t where)
{
  string = string.substring(0,where) + what + string.substring(where); 
}

void uuid_change_endianess(String& uuid_str)
{
  char temp[2];
  uint8_t n=0;
  uint8_t k = uuid_str.length()-2;
  
  while(n<uuid_str.length()/2)
  {
    if(uuid_str.c_str()[n] == '-')n++;
    if(uuid_str.c_str()[k+1] == '-')k--;
    
    temp[0] = uuid_str[n];
    temp[1] = uuid_str[n+1];
    
    uuid_str[n] = uuid_str[k];
    uuid_str[n+1] = uuid_str[k+1];      
  
    uuid_str[k] = temp[0];
    uuid_str[k+1] = temp[1];
    
    n+=2;
    k-=2;
  }
}

void uuid_strip_insert(String& raw_uuid){
  string_insert(raw_uuid, "-", 24);
  string_insert(raw_uuid, "-", 20);
  string_insert(raw_uuid, "-", 16);
  string_insert(raw_uuid, "-", 12);
}

void aes_encrypt(String text_input, String& text_output){
  unsigned char input[16];
  unsigned char cipherTextOutput[16];
  String myuuid = "";

  memcpy(input, text_input.c_str(), text_input.length());
  encrypt(input, key, cipherTextOutput);
  
  Serial.println("original text :" + text_input);
  for (int i = 0; i < 16; i++) {
    char str[3];
    sprintf(str, "%02x", (int)cipherTextOutput[i]);
    myuuid += str;
  }
  Serial.println("Advertising :" + myuuid);
  uuid_change_endianess(myuuid);
  uuid_strip_insert(myuuid);
  text_output = myuuid;
}
