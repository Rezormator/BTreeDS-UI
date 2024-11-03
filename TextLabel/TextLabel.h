#pragma once

#include <QLabel>
#include "../MainWindow/MainWindow.h"
#include "../Utils.h"

constexpr int WIDTH_T = 708;
constexpr int HEIGHT_T = 50;

class TextLabel {
private:
    QLabel *textLabel;
public:
    TextLabel(const char *title, MainWindow* mainWindow, int x, int y, int width = WIDTH_T, int height = HEIGHT_T);
    ~TextLabel();
    NODISCARD QLabel *getTextLabel() const;
};
