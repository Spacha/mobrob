#include "WiFi.h"
#include "AsyncUDP.h"

const char * ssid = "";
const char * password = "";

AsyncUDP udp;

void setup()
{
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("WiFi Failed");
        while(1) {
            delay(1000);
        }
    }

    Serial.println("WiFi connected!");
    
    if(udp.connect(IPAddress(192,168,1,168), 3333)) {
        Serial.println("UDP connected");
        //udp.print("Hello Server!");
        udp.onPacket([](AsyncUDPPacket packet) {
          Serial.print("UDP Packet Type: ");
          Serial.print(packet.isBroadcast() ? "Broadcast" : packet.isMulticast() ? "Multicast" : "Unicast");
          Serial.print(", From: ");
          Serial.print(packet.remoteIP());
          Serial.print(":");
          Serial.print(packet.remotePort());
          Serial.print(", To: ");
          Serial.print(packet.localIP());
          Serial.print(":");
          Serial.print(packet.localPort());
          Serial.print(", Length: ");
          Serial.print(packet.length());
          Serial.print(", Data: ");
          Serial.write(packet.data(), packet.length());
          Serial.println();
          //reply to the client
          packet.printf("Got %u bytes of data", packet.length());
        });
        //Send unicast
        udp.print("Hello Server!");
    }
}

AsyncUDPMessage msg_buffer(64);
int counter = 0;

void loop()
{
    //delay(1000);
    ////Send broadcast on port 1234
    //udp.broadcastTo("Anyone here?", 1234);

    delay(10000);
    Serial.println("Sending something to the server.");
    //sprintf(msg_data, "Counter value: %d", counter);
    msg_buffer.flush();
    msg_buffer.printf("Counter value: %d", counter);
    udp.sendTo(msg_buffer, IPAddress(192,168,1,168), 3333);

    counter++;
}
