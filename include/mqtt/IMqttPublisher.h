#ifndef IMQTT_PUBLISHER_H
#define IMQTT_PUBLISHER_H

class IMqttPublisher {
  public:
    virtual ~IMqttPublisher() = default;
    virtual void connect() = 0;
    virtual void loop() = 0;
    virtual bool publish(const char *topic, const char *payload, bool retained) = 0;
    virtual bool isConnected() const = 0;
    virtual bool isWifiConnected() const = 0;
};

#endif
