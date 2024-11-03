#include "Input.h"

InputLine *Input::inputID;
InputLine *Input::inputCity;
InputLine *Input::inputPopulation;
InputLine *Input::inputArea;
TextLabel *Input::result;

void Input::setInputs(InputLine *inputID, InputLine *inputCity, InputLine *inputPopulation, InputLine *inputArea, TextLabel *result) {
    Input::inputID = inputID;
    Input::inputCity = inputCity;
    Input::inputPopulation = inputPopulation;
    Input::inputArea = inputArea;
    Input::result = result;
}

InputLine *Input::getInputID() {
    return inputID;
}

InputLine *Input::getInputCity() {
    return inputCity;
}

InputLine *Input::getInputPopulation() {
    return inputPopulation;
}

InputLine *Input::getInputArea() {
    return inputArea;
}

TextLabel *Input::getResult() {
    return result;
}
