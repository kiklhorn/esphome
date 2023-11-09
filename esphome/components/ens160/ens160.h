#include "esphome.h"
#include "ScioSense_ENS160.h"

class ENS160 : public PollingComponent, public Sensor {
    public:
        ScioSense_ENS160 ens160;
        Sensor *AQI_sensor = new Sensor();
        Sensor *TVOC_sensor = new Sensor();
        Sensor *eCO2_sensor = new Sensor();

        ENS160() : PollingComponent(15000) { }
        float get_setup_priority() const override { return esphome::setup_priority::IO; }

        void setup() override {
            ens160.begin();
        }
        void update() override {
            int aqi = ens160.getAQI();
            int tvoc = ens160.getTVOC();
            int eco2 = ens160.geteCO2();
            AQI_sensor->publish_state(aqi);
            TVOC_sensor->publish_state(tvoc);
            eCO2_sensor->publish_state(eco2);
            ESP_LOGD("ENS160", "The value of sensor AQI is: %.0f", aqi);
            ESP_LOGD("ENS160", "The value of sensor TVOC is: %.0f", tvoc);
            ESP_LOGD("ENS160", "The value of sensor eCO2 is: %.0f", eco2);
        // This will be called every "update_interval" milliseconds.
        }
};