#pragma once

#include <QMainWindow>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);

private:
    enum WidgetIndices { SelectChar = 0, Map = 1 };
    void setupWindow();
};
