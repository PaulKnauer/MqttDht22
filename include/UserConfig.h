#ifndef UserConfig_h
#define UserConfig_h

#ifndef WLAN_SSID
#define WLAN_SSID ""
#endif
#ifndef WLAN_PASSWORD
#define WLAN_PASSWORD ""
#endif

#ifndef DHT22_PIN
#define DHT22_PIN 2
#endif

#ifndef DELAY
#define DELAY 60000
#endif

#ifndef MQTT_CLIENT_NAME
#define MQTT_CLIENT_NAME "Dht22Sensor"
#endif
#ifndef MQTT_SERVER
#define MQTT_SERVER "127.0.0.1"
#endif
#ifndef MQTT_SERVERPORT
#define MQTT_SERVERPORT 1883
#endif
#ifndef MQTT_USERNAME
#define MQTT_USERNAME ""
#endif
#ifndef MQTT_PASSWORD
#define MQTT_PASSWORD ""
#endif

#ifndef REQUIRE_CONFIG
#define REQUIRE_CONFIG 0
#endif

#if REQUIRE_CONFIG
static_assert(sizeof(WLAN_SSID) > 1, "WLAN_SSID must be set to a non-empty value");
static_assert(sizeof(WLAN_PASSWORD) > 1, "WLAN_PASSWORD must be set to a non-empty value");
static_assert(sizeof(MQTT_SERVER) > 1, "MQTT_SERVER must be set to a non-empty value");
#endif

#ifndef MQTT_TOPIC_PREFIX
#define MQTT_TOPIC_PREFIX "Office/DHT22"
#endif
#define MQTT_TEMPERATURE_PUBLISH_TOPIC MQTT_TOPIC_PREFIX "/Temperature"
#define MQTT_HUMIDITY_PUBLISH_TOPIC MQTT_TOPIC_PREFIX "/Humidity"
#define MQTT_STATUS_PUBLISH_TOPIC MQTT_TOPIC_PREFIX "/Status"

#define MQTT_HEARTBEAT_PUBLISH_TOPIC MQTT_TOPIC_PREFIX "/Heartbeat"
#ifndef MQTT_HEARTBEAT_INTERVAL_MS
#define MQTT_HEARTBEAT_INTERVAL_MS 300000
#endif

#define MQTT_JSON_PUBLISH_TOPIC MQTT_TOPIC_PREFIX "/Reading"
#ifndef MQTT_PUBLISH_JSON
#define MQTT_PUBLISH_JSON 1
#endif

#define MQTT_ERROR_PUBLISH_TOPIC MQTT_TOPIC_PREFIX "/Error"
#ifndef SENSOR_ERROR_THRESHOLD
#define SENSOR_ERROR_THRESHOLD 3
#endif
#define MQTT_STATUS_ONLINE "online"
#define MQTT_STATUS_OFFLINE "offline"

#define WIFI_RETRY_INTERVAL_MS 5000
#define MQTT_RETRY_INTERVAL_MS 5000

#endif
