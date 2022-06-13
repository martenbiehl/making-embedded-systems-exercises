
static const uint8_t SM300D2_DATA_LENGTH = 17;


void setup() {
  // initialize both serial ports:
  Serial.begin(9600);
  Serial1.begin(9600);
  // Serial1.setTimeout(5000);
  Serial.printf("Start");
}

void loop() {

  if (Serial1.available()) {
    bool found_start = false;
    uint8_t d;
    while(!found_start) {
      d = Serial1.read();
      found_start = (d == 0x3C);
    }

    Serial.printf("\n\nFound starting code: 0x%02x :: ", d);

    uint8_t data[SM300D2_DATA_LENGTH] = {0};
    // size_t readBytes = Serial1.readBytes((unsigned char*)data+1, SM300D2_DATA_LENGTH-1);
    // Serial.printf("Read %d bytes\n", readBytes);
    data[0] = d;
    int i = 1;
    while (i < SM300D2_DATA_LENGTH) {
      if (Serial1.available() > 0) {
        int inByte = Serial1.read();
        if (i == 1 && inByte != 0x02) {
          Serial.printf("Wrong version");
          return;          
        }
        if (inByte == 0x3c && i < SM300D2_DATA_LENGTH-2) {
          Serial.printf("Restart");
          i = 0;
        }
        // if (d != 0 ) {
          data[i] = inByte;
          i++;
          Serial.printf("byte received: 0x%02x\n", inByte);
        // } else {
          // Serial.printf("Skipping null byte\n");
        // }
      }
    }

    if (i < SM300D2_DATA_LENGTH) {
      Serial.printf("Only received %d bytes", i);
      return;
    }

    i = 0;
    while (i<SM300D2_DATA_LENGTH) {
      Serial.printf(", 0x%02x ", data[i++]);
    }
    Serial.printf("%d\n", i);

    uint8_t checksum = calculate_checksum(data);

    Serial.printf("Received: 0x%02x, Calculated: 0x%02x, Possible: 0x%02x, 0x%02x",data[SM300D2_DATA_LENGTH - 1], checksum,  checksum - 0x80, checksum + 0x80);

    if ((checksum != data[SM300D2_DATA_LENGTH - 1]) &&
      (checksum - 0x80 != data[SM300D2_DATA_LENGTH - 1]) &&
      (checksum + 0x80 != data[SM300D2_DATA_LENGTH - 1])) {
      Serial.printf("\nError: Checksum does not match.");
      return;
    } else {
      Serial.printf("\nChecksum correct");
    }

    const uint16_t co2 = (data[2] * 256) + data[3];
    const uint16_t formaldehyde = (data[4] * 256) + data[5];
    const uint16_t tvoc = (data[6] * 256) + data[7];
    const uint16_t pm_2_5 = (data[8] * 256) + data[9];
    const uint16_t pm_10_0 = (data[10] * 256) + data[11];
    // A negative value is indicated by adding 0x80 (128) to the temperature value
    const float temperature = ((data[12] + (data[13] * 0.1f)) > 128)
                                  ? (((data[12] + (data[13] * 0.1f)) - 128) * -1)
                                  : data[12] + (data[13] * 0.1f);
    const float humidity = data[14] + (data[15] * 0.1f);

    Serial.printf("CO₂: %u ppm", co2);
    Serial.printf("Formaldehyde: %u µg/m³", formaldehyde);
    Serial.printf("TVOC: %u µg/m³", tvoc);
    Serial.printf("PM2.5: %u µg/m³", pm_2_5);
    Serial.printf("PM10: %u µg/m³", pm_10_0);
    Serial.printf("Temperature: %.2f °C", temperature);
    Serial.printf("Humidity: %.2f percent", humidity);
    Serial.printf("\n");
    // Serial.write((char*)data);
  }

}

uint8_t calculate_checksum(uint8_t *data) {
  uint8_t sum = 0;
  for (int i = 0; i < (SM300D2_DATA_LENGTH - 1); i++) {
    sum += *data++;
  }
  return sum;
}
