// custom_components/ablsalto/ablsalto_component.h
#pragma once

#include "esphome.h"

class AblsaltoComponent : public Component, public UARTDevice {
 public:
  AblsaltoComponent(UARTComponent *parent) : UARTDevice(parent) {}

  void setup() override {
    // Setup UART
    this->set_rx_pin(16);
    this->set_tx_pin(17);
    this->set_baud_rate(38400);
    this->set_data_bits(8);
    this->set_stop_bits(1);
    this->set_parity(UART_PARITY_NONE);
  }

  void loop() override {
    // Loop logic goes here
  }

  void update() override {
    // Update logic goes here
  }

  void charge(float charging_current) {
    // Example: Convert charging_current to a formatted string
    char command[20];
    snprintf(command, sizeof(command), "!1 12 %04d\r\n", static_cast<int>(charging_current));

    // Send the command over UART
    this->send_command(command);

    // Wait for the response
    char response[20];
    size_t len = this->read_bytes(reinterpret_cast<uint8_t *>(response), sizeof(response), 1000);

    if (len > 0) {
      response[len] = '\0';  // Null-terminate the response
      ESP_LOGD("ablsalto", "Received response: %s", response);

      // Check if the response starts with ">1 12"
      if (strstr(response, ">1 12") == response) {
        ESP_LOGD("ablsalto", "Command successful: Charging started");
      } else {
        ESP_LOGW("ablsalto", "Command failed: Unexpected response");
      }
    } else {
      ESP_LOGW("ablsalto", "Command failed: No response received");
    }
  }

 private:
  void send_command(const char *command) {
    ESP_LOGD("ablsalto", "Sending command: %s", command);
    this->write(command);
  }
};
