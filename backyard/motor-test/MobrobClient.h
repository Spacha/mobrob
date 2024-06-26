#ifndef __MOBROB_CLIENT_H__
#define __MOBROB_CLIENT_H__

#define FW_VERSION "1.2.3"

enum Status { UNCONNECTED, CONNECTED };
enum Mode { MANUAL = 0, EXPLORE = 1 };

// WiFi credentials
#define NETWORK_NAME     "Heiluva_sipuli"
#define NETWORK_PASSWORD "Slummi2017"

#include "WiFi.h"
#include "AsyncUDP.h"
#include "ArduinoJson.h"

#define SERVER_POLL_INTERVAL  2000
#define SERVER_TIMEOUT        5000

// Statically allocate message objects
// FIXME: Should we only use a single document based on the maximum size?
//StaticJsonDocument<96> serverHelloMsg;
//serverHelloMsg["type"] = "ROBOT_UPDATE";

// See: https://arduinojson.org/v6/assistant
//StaticJsonDocument<196> msg; // FIXME: Can these be nested?
StaticJsonDocument<192> msg;
StaticJsonDocument<96> msg_data;
//String<> msg_str;

//char msg_type[16];

//StaticJsonDocument<200> robotUpdateMsg; // TODO: Update size
//robotUpdateMsg["type"] = "ROBOT_UPDATE";

// typedef struct
// {
//   char fw_version[16];
// } robot_hello_data;

// typedef struct
// {
//   char fw_version[16];
// } robot_update_data;


class MobrobClient
{
protected:
  IPAddress m_server_addr;
  uint16_t m_server_port;
  uint64_t m_seq_no;
  AsyncUDP m_udp;
  bool m_connected;
  unsigned long m_last_message_t;
  std::function<void(float, Mode)> m_update_configuration_cb;
  std::function<void(float, float)> m_control_cb;

  bool connect_udp();
  bool wifi_connected();

public:
  MobrobClient(IPAddress server_addr, uint16_t server_port, std::function<void(float, Mode)> update_configuration_cb, std::function<void(float, float)> control_cb);
  ~MobrobClient();

  bool try_connect(uint16_t timeout);
  bool connected();
  void send_robot_hello();
  void send_robot_update(float roll, float pitch, float temperature, float travel_dist);
  void send_ack(int seq_no);
  void send_message(const char *type, JsonDocument data);
  void handle_packet(AsyncUDPPacket packet);
};

/**
 * TODO.
 */
MobrobClient::MobrobClient(IPAddress server_addr, uint16_t server_port, std::function<void(float, Mode)> update_configuration_cb, std::function<void(float, float)> control_cb)
  : m_server_addr(server_addr),
    m_server_port(server_port),
    m_update_configuration_cb(update_configuration_cb),
    m_control_cb(control_cb),
    m_last_message_t(0),
    m_connected(false),
    m_seq_no(0)
{}

/**
 * TODO.
 */
MobrobClient::~MobrobClient() {}

/**
 * TODO.
 */
bool MobrobClient::try_connect(uint16_t timeout)
{
  Serial.println("[CLT] Trying to connect to WiFi...");

  if (!wifi_connected())
  {
    // try connecting
    //WiFi.mode(WIFI_STA);
    WiFi.begin(NETWORK_NAME, NETWORK_PASSWORD);

    // wait until the timeout or connection
    unsigned long start_t = millis();
    while (!connected() && (millis() - start_t) < timeout) {
      vTaskDelay(100 / portTICK_PERIOD_MS);
    }
  }

  // if wifi was connected, try connecting to the UDP server
  if (wifi_connected())
  {
    Serial.print("[CLT] WiFi connected. Local IP:");
    Serial.println(WiFi.localIP());

    if (connect_udp())
    {
      m_connected = true;
    }
  }

  return connected();
}

/**
 * TODO.
 */
bool MobrobClient::connected()
{
  // if server is connected, check if the UDP server has timed out
  if (m_connected && (millis() - m_last_message_t >= SERVER_TIMEOUT))
  {
    m_connected = false;
    Serial.println("[CLT] Server timed out.");
  }

  return m_connected;
}

///////////////////////////////////////////////////////////
// Nonpublic methods
///////////////////////////////////////////////////////////

void MobrobClient::handle_packet(AsyncUDPPacket packet)
{
  if (packet.length() == 0)
    return;
  
  m_last_message_t = millis();

  Serial.print("[CLT] Received data: ");
  //Serial.write(packet.data(), packet.length());
  Serial.println();

  // handle message
  JsonDocument msg; // FIXME: Use static message for deserialization also!
  deserializeJson(msg, packet.data());

  serializeJson(msg, Serial);
  Serial.println();

  String msg_type = msg["type"];
  int seq_no = msg["seq_no"];

  if (msg_type == "SERVER_HELLO")
  {
    Serial.print("[CLT] Server hello received!");
    send_ack(seq_no);
  }
  else if (msg_type == "CONFIGURATION")
  {
    float track_speed = msg["data"]["speed"];
    Mode mode = static_cast<Mode>(msg["data"]["mode"].as<int>());

    m_update_configuration_cb(track_speed, mode);
    send_ack(seq_no);

    if (!connected())
    {
      m_connected = true;
    }
  }
  else if (msg_type == "CONTROL")
  {
    float left_track = msg["data"]["left_track"];
    float right_track = msg["data"]["right_track"];

    m_control_cb(left_track, right_track);
    send_ack(seq_no);

    if (!connected())
    {
      m_connected = true;
    }
  }
  else if (msg_type == "ACK")
  {
    Serial.println("ACK received.");
  }
  else
  {
    Serial.print("[CLT] Unknown message type: ");
    Serial.println(msg_type);
  }
}


/**

 * TODO.
 */
bool MobrobClient::connect_udp()
{
  if (m_udp.connect(m_server_addr, m_server_port))
  {
    Serial.print("[CLT] UDP status:");
    Serial.println(m_udp.connected());
    Serial.println("[CLT] Starting connection protocol.");

    // register message handler
    m_udp.onPacket([this](AsyncUDPPacket packet) {
      this->handle_packet(packet);
    });

    //Serial.println("[CLT] Connected. Sending SERVER_HELLO.");

    // keep polling the UDP server until connecte
    while (!connected())
    {
      // TODO: MOVE TO MAIN!
      send_robot_hello();
      vTaskDelay(SERVER_POLL_INTERVAL / portTICK_PERIOD_MS);
    }

    return true;
  }

  return false;
}

void MobrobClient::send_robot_hello()
{
  msg_data.clear();
  msg_data["fw_version"] = FW_VERSION;
  send_message("ROBOT_HELLO", msg_data);
}

void MobrobClient::send_ack(int seq_no)
{
  msg_data.clear();
  msg_data["seq_no"] = seq_no;
  send_message("ACK", msg_data);
}

void MobrobClient::send_robot_update(float roll, float pitch, float temperature, float travel_dist)
{
  msg_data.clear();
  msg_data["roll"] = roll;
  msg_data["pitch"] = pitch;
  msg_data["temperature"] = temperature;
  msg_data["travel_dist"] = travel_dist;
  send_message("ROBOT_UPDATE", msg_data);
}

void MobrobClient::send_message(const char *type, JsonDocument data)
{
  msg["type"] = type;
  msg["seq_no"] = m_seq_no++;
  msg["data"] = data;

  // FIXME: Stream straight to the socket without a String!
  String msg_str; // FIXME: In heap
  serializeJson(msg, msg_str);
  m_udp.print(msg_str);

  Serial.print("[CLT] Sent: ");
  serializeJson(msg, Serial);
  Serial.println();
  //msg_data.clear();
}

/**
 * TODO.
 */
bool MobrobClient::wifi_connected()
{
  return WiFi.status() == WL_CONNECTED;
}

#endif /* __MOBROB_CLIENT_H__ */
