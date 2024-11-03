#pragma once

#include <QLineEdit>
#include "../MainWindow/MainWindow.h"
#include "../Utils.h"

constexpr int WIDTH_L = 708;
constexpr int HEIGHT_L = 50;

class InputLine {
private:
    QLineEdit *inpuLine;
public:
    InputLine(const char *title, MainWindow* mainWindow, int x, int y, int width = WIDTH_L, int height = HEIGHT_L);
    ~InputLine();
    NODISCARD QLineEdit *getInputLine() const;
};
