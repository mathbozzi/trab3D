#ifndef input_H
#define input_H

#include <iostream>
#include <string>
#include <time.h>
#include "tinyxml2.h"

#include "Arena.h"
#include "EstruturasBasicas.h"
#include "Rect.h"
#include "Circle.h"

class INPUT
{
    public:
        INPUT(const std::string path);
        bool isLoaded;
        Arena getArena();
        tinyxml2::XMLDocument input;
        std::vector<Rect> getRects();
        std::vector<Circle> getCircles();
};

#endif // input_H
