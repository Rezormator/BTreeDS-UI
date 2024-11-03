#pragma once

#include <QPushButton>
#include "../MainWindow/MainWindow.h"
#include "../Utils.h"

constexpr int WIDTH_B = 109;
constexpr int HEIGHT_B = 50;

class Button {
private:
    QPushButton *button;
public:
    Button(const char *title, MainWindow* mainWindow, int x, int y, int width = WIDTH_B, int height = HEIGHT_B);
    ~Button();
    NODISCARD QPushButton *getButton() const;
};
