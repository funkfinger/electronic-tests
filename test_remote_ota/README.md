# Sorting out OTA ESP8266 remote updating...

Steps to getting over the air updating to happen. Some of these steps were inspired by [this site](https://www.bakke.online/index.php/2017/06/02/self-updating-ota-firmware-for-esp8266/).

* WiFi password needs to be set in `settings.h` file which isn't included in repo for obvious reasons.
* settings file looks something like this:

      #define SETTINGS_NETWORK_SSID "wifissid"
      #define SETTINGS_NETWORK_PASS "wifipass"
      #define SETTINGS_OTA_VERSION_ADDRESS_PREFIX "http://<web address>/firmware-"
      #define SETTINGS_OTA_VERSION_ADDRESS_SUFFIX "/version.json"

* `version.json` and `firmware.bin` are uploaded to a folder somewhere publicly accessible, in my case an Amazon S3 bucket.
* the folder `firmware-` is suffixed with the mac address of the ESP8266 to look something like `firmware-0A-1B-2C-3D-4E-5F`
* version file looks something like this:

      {
        "version": 4,
        "firmwareFile": "firmware.bin"
      }
* JSON parsing code was partially generated from the [ArduinoJson Assistant](https://arduinojson.org/assistant/) which helps with the values to plug into the code.

Because I use `platformio` the `.bin` file is located in the project file at:

    .pioenvs/<BOARD NAME>/firmware.bin

You can build this file using the normal `pio run` (no `-t upload`) command.
