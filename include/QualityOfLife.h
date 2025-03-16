//
// Created by yunarta on 3/15/25.
//

#ifndef QUALITYOFLIFE_H
#define QUALITYOFLIFE_H

#include <ArduinoJson.h>

class ArduinoAppConfig {
public:
     JsonDocument doc;
     void begin();
} extern Config;

void connectToInternet();

#endif //QUALITYOFLIFE_H
