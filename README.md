# MqttDht22

ESP8266 (Wemos D1) firmware that reads a DHT22 sensor and publishes temperature and humidity to MQTT.

## Build configuration

Secrets and per-device settings are injected via environment variables at build time.

Required:
- `WLAN_SSID`
- `WLAN_PASSWORD`
- `MQTT_SERVER`

Optional (recommended per device):
- `MQTT_CLIENT_NAME` (default: `Dht22Sensor`)
- `MQTT_SERVERPORT` (default: `1883`)
- `MQTT_USERNAME`
- `MQTT_PASSWORD`
- `MQTT_TOPIC_PREFIX` (default: `Office/DHT22`)
- `DHT22_PIN` (default: `2`)

For multiple devices, set a unique `MQTT_CLIENT_NAME` and `MQTT_TOPIC_PREFIX`
per unit.

Example:
```sh
export WLAN_SSID="your-ssid"
export WLAN_PASSWORD="your-pass"
export MQTT_SERVER="192.168.1.22"
export MQTT_SERVERPORT=31883
export MQTT_CLIENT_NAME="OfficeDht22Sensor"
export MQTT_USERNAME=""
export MQTT_PASSWORD=""
```

Alternatively, copy `platformio_override.ini.example` to `platformio_override.ini`
and set values there. This file is ignored by git.

Builds will fail if required values are left empty.

## Topics

Defaults are defined in `src/UserConfig.h`.

Additional topics:
- `MQTT_JSON_PUBLISH_TOPIC` (default: `<prefix>/Reading`)
- `MQTT_PUBLISH_JSON` (default: `1`)
- `MQTT_ERROR_PUBLISH_TOPIC` (default: `<prefix>/Error`)
