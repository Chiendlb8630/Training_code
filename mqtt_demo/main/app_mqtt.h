#pragma once

#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "mqtt_client.h"

#define BROKER_URI     "" // Broker URL
#define MQTT_TOPIC_PUB "" // TOPIC
#define MQTT_TOPIC_SUB "" //TOPIC SUB
void mqtt_app_publish(const char *topic, const char *data, int len);
void mqtt_app_start(const char *broker_uri);


