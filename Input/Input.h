#pragma once

#include "../InputLine/InputLine.h"
#include "../TextLabel/TextLabel.h"

class Input {
private:
    static InputLine *inputID;
    static InputLine *inputCity;
    static InputLine *inputPopulation;
    static InputLine *inputArea;
    static TextLabel *result;
public:
    static void setInputs(InputLine *inputID, InputLine *inputCity, InputLine *inputPopulation, InputLine *inputArea, TextLabel *result);
    NODISCARD static InputLine *getInputID();
    NODISCARD static InputLine *getInputCity();
    NODISCARD static InputLine *getInputPopulation();
    NODISCARD static InputLine *getInputArea();
    NODISCARD static TextLabel *getResult();
};
