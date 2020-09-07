#pragma once

#include "charactermodel.h"

#include <QMainWindow>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);

private:
    enum WidgetIndices { SelectChar = 0, Map = 1 };

    void generateCSV();
    void setupWindow();
    void setupModel();
    void setupUI();

    CharacterModel* m_model;
};
