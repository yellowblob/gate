/**
  The Pozyx ready to range tutorial (c) Pozyx Labs
  Please read the tutorial that accompanies this sketch: https://www.pozyx.io/Documentation/Tutorials/ready_to_range/Arduino

  This demo requires two Pozyx devices and one Arduino. It demonstrates the ranging capabilities and the functionality to
  to remotely control a Pozyx device. Place one of the Pozyx shields on the Arduino and upload this sketch. Move around
  with the other Pozyx device.

  This demo measures the range between the two devices. The closer the devices are to each other, the more LEDs will
  light up on both devices.
*/

#include <Pozyx.h>
#include <Pozyx_definitions.h>
#include <Wire.h>

////////////////////////////////////////////////
////////////////// PARAMETERS //////////////////
////////////////////////////////////////////////

uint16_t destination_id;
uint16_t destination_ids[3] = {0x6015,0x600d,0x6026};     // the network id of the other pozyx device: fill in the network id of the other device
signed int range_step_mm = 1000;      // every 1000mm in range, one LED less will be giving light.

uint8_t ranging_protocol = POZYX_RANGE_PROTOCOL_PRECISION; // ranging protocol of the Pozyx.

uint16_t remote_ids[3] = {0x6002,0x6000,0x6034};
uint16_t remote_id;                               // the network ID of the remote device
int destinationCount;
int remoteCount;

////////////////////////////////////////////////

void setup(){
  Serial.begin(115200);

  if(Pozyx.begin() == POZYX_FAILURE){
    Serial.println("ERROR: Unable to connect to POZYX shield");
    Serial.println("Reset required");
    delay(100);
    abort();
  }
  
  Serial.println("------------POZYX RANGING V1.1------------");
  Serial.println("NOTES:");
  Serial.println("- Change the parameters:");
  Serial.println("\tdestination_id (target device)");
  Serial.println("\trange_step (mm)");
  Serial.println();
  Serial.println("- Approach target device to see range and");
  Serial.println("led control");
  Serial.println("------------POZYX RANGING V1.1------------");
  Serial.println();
  Serial.println("START Ranging:");

  remoteCount = sizeof(remote_ids);
  destinationCount = sizeof(destination_ids);
  
  for(int i = 0; i <= remoteCount; i++){
    Pozyx.setRangingProtocol(ranging_protocol, remote_id);
  }
}

void loop(){
  device_range_t range;
  int status = 0;
   
  for(int i = 0; i <= remoteCount; i++){
    remote_id = remote_ids[i];
    for(int j = 0; j <= destinationCount; j++){
      destination_id = destination_ids[j];
      status = Pozyx.doRemoteRanging(remote_id, destination_id, &range);

      if (status == POZYX_SUCCESS){
        Serial.print(range.distance);
        Serial.print(" ");
      }
      else{
        Serial.println("ERROR: ranging");
      }
      
    }
  }

  Serial.println();
  
}
