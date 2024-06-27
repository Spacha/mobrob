#ifndef __MOBROB_CLIENT_H__
#define __MOBROB_CLIENT_H__

/*
 * This file is part of the Mobrob project.
 *
 * This is the UDP client for the robot for connecting with the server.
 */

#include "WiFi.h"
#include "AsyncUDP.h"
#include "ArduinoJson.h"
#include "mobrob.h"

#define SERVER_POLL_INTERVAL  2000
#define SERVER_TIMEOUT        5000

// Statically allocate message objects
// See: https://arduinojson.org/v6/assistant
StaticJsonDocument<192> msg;
StaticJsonDocument<96> msg_data;

/**
 * The client object for maintaining the connection state.
 */
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

  void setup();
  bool try_connect(uint16_t timeout);
  bool connected();
  void send_robot_hello();
  void send_robot_update(float roll, float pitch, float temperature, float travel_dist, float obstacle_dist);
  void send_ack(int seq_no);
  void send_message(const char *type, JsonDocument data);
  void handle_packet(AsyncUDPPacket packet);
};


///////////////////////////////////////////////////////////////////////////////
// Method definitions
///////////////////////////////////////////////////////////////////////////////

/**
 * Construct the MobrobClient class. This does not start a connection yet.
 * 
 * @param server_addr The IP address of the server
 * @param server_port The IP address of the server
 * @param update_configuration_cb A callback function to call when a new configuration is received
 * @param control_cb A callback function to call when a control message is received
 */
MobrobClient::MobrobClient(IPAddress server_addr, uint16_t server_port,
                           std::function<void(float, Mode)> update_configuration_cb,
                           std::function<void(float, float)> control_cb
                           )
  : m_server_addr(server_addr),
    m_server_port(server_port),
    m_update_configuration_cb(update_configuration_cb),
    m_control_cb(control_cb),
    m_last_message_t(0),
    m_connected(false),
    m_seq_no(0)
{}

/**
 * Destruct the MobrobClient class.
 */
MobrobClient::~MobrobClient() {}

/**
 * Setup the Mobrob client by setting up the Wi-Fi mode.
 * 
 * NOTE: This has to be called before pinMode setups in Arduino setup!
 *       Otherwise some of the pins (e.g., 25) will not work!
 */
void MobrobClient::setup()
{
  WiFi.mode(WIFI_STA);
}

/**
 * Try connecting to the server. First, if Wi-Fi connection is not established,
 * try connecting. Then, start the UDP server connection protocol.
 * 
 * @param timeout Milliseconds before the Wi-Fi connection is timed out
 * @return True if the connection was successfully formed, false otherwise
 */
bool MobrobClient::try_connect(uint16_t timeout)
{
  Serial.println("[CLT] Trying to connect to WiFi...");

  if (!wifi_connected())
  {
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
 * Get the connection status of the client, including Wi-Fi and the server.
 * 
 * @return True if the connection is up, false otherwise.
 */
bool MobrobClient::connected()
{
  // if server is connected, check if the UDP server has timed out
  if (m_connected && (millis() - m_last_message_t >= SERVER_TIMEOUT))
  {
    m_connected = false;
    // Serial.println("[CLT] Server timed out.");
  }

  return m_connected;
}

///////////////////////////////////////////////////////////
// Nonpublic methods
///////////////////////////////////////////////////////////

/**
 * A callback method for handling a received UDP packet.
 * 
 * @param packet The UDP packet containing the data and its length
 */
void MobrobClient::handle_packet(AsyncUDPPacket packet)
{
  if (packet.length() == 0)
    return;
  
  m_last_message_t = millis();

  //Serial.print("[CLT] Received data: ");
  //Serial.write(packet.data(), packet.length());
  //Serial.println();

  // dEserialize the message into a JSON document
  JsonDocument msg; // FIXME: Use static message for deserialization also!
  deserializeJson(msg, packet.data());

  //serializeJson(msg, Serial);
  //Serial.println();

  String msg_type = msg["type"];
  int seq_no = msg["seq_no"];

  // Handle the packet based on the message type

  if (msg_type == "SERVER_HELLO")
  {
    // Serial.print("[CLT] Server hello received!");
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
      Serial.println("[CLT] Connected to the server.");
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
    // Serial.println("ACK received.");
  }
  else
  {
    Serial.print("[CLT] Unknown message type: ");
    Serial.println(msg_type);
  }
}


/**
 * Connect to UDP. This includes the handshake with the server.
 * 
 * @return True if the connection was formed, false otherwise.
 */
bool MobrobClient::connect_udp()
{
  if (m_udp.connect(m_server_addr, m_server_port))
  {
    // Serial.print("[CLT] UDP status:");
    // Serial.println(m_udp.connected());
    // Serial.println("[CLT] Starting connection protocol.");

    // register message handler
    m_udp.onPacket([this](AsyncUDPPacket packet) {
      this->handle_packet(packet);
    });

    //Serial.println("[CLT] Connected. Sending SERVER_HELLO.");

    // keep polling the UDP server until connecte
    while (!connected())
    {
      send_robot_hello();
      vTaskDelay(SERVER_POLL_INTERVAL / portTICK_PERIOD_MS);
    }

    return true;
  }

  return false;
}

/**
 * Send the 'robot hello' handshake message to
 * the server as a part of forming a connection.
 */
void MobrobClient::send_robot_hello()
{
  msg_data.clear();
  msg_data["fw_version"] = FW_VERSION;
  send_message("ROBOT_HELLO", msg_data);
}

/**
 * Send an ACK of some particular message to the server.
 * 
 * @param seq_no The sequence number of the packet being ACK'd
 */
void MobrobClient::send_ack(int seq_no)
{
  msg_data.clear();
  msg_data["seq_no"] = seq_no;
  send_message("ACK", msg_data);
}

/**
 * Send a 'robot update' message to the server containing measurement data.
 * 
 * @param roll The latest roll measurement of the robot
 * @param pitch The latet pitch of the robot
 * @param temperature The latest temperature measurement
 * @param travel_dist The latest travel distance
 * @param obstacle_dist The latest measured distance to an obstacle
 */
void MobrobClient::send_robot_update(float roll, float pitch, float temperature, float travel_dist, float obstacle_dist)
{
  msg_data.clear();
  msg_data["roll"] = roll;
  msg_data["pitch"] = pitch;
  msg_data["temperature"] = temperature;
  msg_data["travel_dist"] = travel_dist;
  msg_data["obstacle_dist"] = obstacle_dist;
  send_message("ROBOT_UPDATE", msg_data);
}

/**
 * Send a message to the server.
 * 
 * @param type The message type, such as {'ROBOT_HELLO', 'ROBOT_UPDATE', 'ACK'}
 * @param data The message data as a JSON document
 */
void MobrobClient::send_message(const char *type, JsonDocument data)
{
  msg["type"] = type;
  msg["seq_no"] = m_seq_no++;
  msg["data"] = data;

  // FIXME: Stream straight to the socket without a String!
  String msg_str; // FIXME: In heap
  serializeJson(msg, msg_str);
  m_udp.print(msg_str);

  //Serial.print("[CLT] Sent: ");
  serializeJson(msg, Serial);
  //Serial.println();
  //msg_data.clear();
}


/**
 * Whether the Wi-Fi is connected. Does not account for the UDP server connection.
 * 
 * @return True if Wi-Fi is connected, false otherwise
 */
bool MobrobClient::wifi_connected()
{
  return WiFi.status() == WL_CONNECTED;
}

#endif /* __MOBROB_CLIENT_H__ */
