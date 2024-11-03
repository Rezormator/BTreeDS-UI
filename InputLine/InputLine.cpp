#include "InputLine.h"

InputLine::InputLine(const char *title, MainWindow* mainWindow, const int x, const int y, const int width, const int height) {
    inpuLine = new QLineEdit(mainWindow);
    inpuLine->setPlaceholderText(title);
    inpuLine->setGeometry(x, y, width, height);
    inpuLine->setStyleSheet("border-radius: 10px");
}
InputLine::~InputLine() {
    delete inpuLine;
}

QLineEdit *InputLine::getInputLine() const {
    return inpuLine;
}
