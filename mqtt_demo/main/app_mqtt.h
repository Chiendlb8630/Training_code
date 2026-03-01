#pragma once

#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "mqtt_client.h"

#define BROKER_URI     "mqtt://broker.hivemq.com:1883" // Broker URL
#define MQTT_TOPIC_PUB "/Open/msg" // TOPIC
#define MQTT_TOPIC_SUB "Hello" //TOPIC SUB
void mqtt_app_publish(const char *topic, const char *data, int len);
void mqtt_app_start(const char *broker_uri);


