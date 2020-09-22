#pragma once

#include <QDialog>
#include <QColor>

namespace Ui {
class WaypointDialog;
}

class WaypointDialog : public QDialog {
    Q_OBJECT

public:
    explicit WaypointDialog(QWidget* parent = nullptr);
    ~WaypointDialog();
    QColor color() { return m_color; }
    QString text() { return m_text; }

private:
    Ui::WaypointDialog* ui;
    QColor m_color;
    QString m_text;

private slots:
    void onColorClicked();
    void onAcceptClicked();
};
