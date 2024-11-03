#include "Button.h"

Button::Button(const char *title, MainWindow *mainWindow, const int x, const int y, const int width, const int height) {
    button = new QPushButton(title, mainWindow);
    button->setGeometry(x, y, width, height);
    button->setStyleSheet("QPushButton {background-color: #2d2d2d; border-radius: 10px; font-size: 18px; font-weight: bold;}"
                          "QPushButton:hover {background-color: #3c3c3c}");
}

Button::~Button() {
    delete button;
}

QPushButton *Button::getButton() const {
    return button;
}
