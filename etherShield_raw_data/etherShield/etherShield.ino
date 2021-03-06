#include "src/etherShield.h"

static uint8_t mymac[6] = {0x54,0x55,0x58,0x10,0x00,0x24}; 
static uint8_t myip[4] = {192,168,1,17};

#define BUFFER_SIZE 250
unsigned char buf[BUFFER_SIZE+1];


uint16_t pkt_len;

EtherShield es=EtherShield();

void eth_init()
{
    /*initialize enc28j60*/
  es.ES_enc28j60Init(mymac);
  es.ES_enc28j60clkout(2); // change clkout from 6.25MHz to 12.5MHz
 
  delay(10);

  // 0x476 is PHLCON LEDA=links status, LEDB=receive/transmit
  // enc28j60PhyWrite(PHLCON,0b0000 0100 0111 01 10);
  es.ES_enc28j60PhyWrite(PHLCON,0x476);
  delay(100);
 
  //init the ethernet/ip layer:
  es.ES_init_ip_arp_udp_tcp(mymac,myip,80);
}

uint16_t packet_receive()
{
  return es.ES_enc28j60PacketReceive(BUFFER_SIZE, buf);
}

//=================================================================

void setup(){

  Serial.begin(115200);
 
  eth_init();
 
}

void loop(){
  pkt_len = packet_receive();

  if(pkt_len!=0){
      printf("\n\n=================================================\n");
      printf("pkt_len = %d\n",pkt_len);
      
      printf("Destination Mac address : ");
      for(int i = 0; i < 6; i++) {
        printf("%02x", buf[i]);
      }
      printf("\n");

      printf("Source Mac address : ");
      for(int i = 0; i < 6; i++) printf("%02x", buf[i + 6]);
      printf("\n");

      printf("Ethernet Type : ");
      for(int i = 0; i < 2; i++) printf("%02x", buf[i + 12]);
      printf("\n");

//      for(int i=0;i<pkt_len;i++)
//      {
//        if(i%16 == 0) Serial.printf("\n");
//        Serial.printf("%02x ",*(buf+i));
//      }
  }  
  //delay(1);
}
