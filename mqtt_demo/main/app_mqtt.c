#include "app_mqtt.h"

static const char *MQTT_TAG = "MQTT_MODULE";
static esp_mqtt_client_handle_t client = NULL;
static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    esp_mqtt_event_handle_t event = event_data;
    esp_mqtt_client_handle_t client = event->client;
    // msg_id dùng để track QoS 1, 2 (nếu cần)
    int msg_id;

    switch ((esp_mqtt_event_id_t)event_id) {
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(MQTT_TAG, "MQTT_EVENT_CONNECTED");
        // Khi kết nối thành công, tự động sub vào 1 topic.
        msg_id = esp_mqtt_client_subscribe(client, MQTT_TOPIC_SUB, 0);
        ESP_LOGI(MQTT_TAG, "Sent subscribe successful, msg_id=%d", msg_id);

        // Gửi thử một tin nhắn
        esp_mqtt_client_publish(client, MQTT_TOPIC_PUB, "Device Online", 0, 1, 0);
        break;

    case MQTT_EVENT_DISCONNECTED:
        ESP_LOGI(MQTT_TAG, "MQTT_EVENT_DISCONNECTED");
        //ESP-IDF sẽ tự động connect lại
        break;

    case MQTT_EVENT_SUBSCRIBED:
        ESP_LOGI(MQTT_TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
        break;

    case MQTT_EVENT_UNSUBSCRIBED:
        ESP_LOGI(MQTT_TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
        break;

    case MQTT_EVENT_PUBLISHED:
        ESP_LOGI(MQTT_TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
        break;

    case MQTT_EVENT_DATA:
        ESP_LOGI(MQTT_TAG, "MQTT_EVENT_DATA");
        printf("Nhận dữ liệu từ TOPIC: %.*s\r\n", event->topic_len, event->topic);
        printf("Dữ liệu nhận được:  =%.*s\r\n", event->data_len, event->data);
        // Thực hành xử lí event;
        break;

    case MQTT_EVENT_ERROR:
        ESP_LOGI(MQTT_TAG, "MQTT_EVENT_ERROR");
        if (event->error_handle->error_type == MQTT_ERROR_TYPE_TCP_TRANSPORT) {
            ESP_LOGE(MQTT_TAG, " Có lỗi xảy ra");
        }
        break;
    default:
        ESP_LOGI(MQTT_TAG, "Other event id:%d", event->event_id);
        break;
    }
}

void mqtt_app_start(const char *broker_uri)
{
    esp_mqtt_client_config_t mqtt_cfg = {
        .broker.address.uri = broker_uri,
        .credentials.username = NULL, // Điền nếu broker yêu cầu
        .credentials.authentication.password = NULL, // Điền nếu broker yêu cầu
    };
    client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, client);
    esp_mqtt_client_start(client);
}

void mqtt_app_publish(const char *topic, const char *data, int len)
{
    if (client != NULL) {
        int msg_id = esp_mqtt_client_publish(client, topic, data, len, 1, 0);
        ESP_LOGI(MQTT_TAG, "Publishing to %s, msg_id=%d", topic, msg_id);
    } else {
        ESP_LOGE(MQTT_TAG, "Client not initialized");
    }
}