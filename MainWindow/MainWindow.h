#pragma once

#include <QMainWindow>

class MainWindow : public QMainWindow {
private:
    void keyPressEvent(QKeyEvent *event) override;
    void setupUI();
    void closeEvent(QCloseEvent *event) override;
public:
    MainWindow();
};
