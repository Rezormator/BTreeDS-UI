#include "TextLabel.h"

TextLabel::TextLabel(const char *title, MainWindow* mainWindow, const int x, const int y, const int width, const int height) {
    textLabel = new QLabel(title, mainWindow);
    textLabel->setGeometry(x, y, width, height);
    textLabel->setAlignment(Qt::AlignCenter);
    textLabel->setStyleSheet("background-color: #2d2d2d; border-radius: 10px;");
}

TextLabel::~TextLabel() {
    delete textLabel;
}

QLabel *TextLabel::getTextLabel() const {
    return textLabel;
}
