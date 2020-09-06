#pragma once

#include <QCursor>
#include <QIcon>
#include <QList>
#include <QString>

QIcon loadIconFromFiles(const QString &fileNameOrID,
                        QList<int> iconSizeList = QList<int>());
QCursor loadCursorFromFiles(const QString &fileNameOrID, double hotX = 0.0,
                            double hotY = 0.0,
                            QList<int> iconsSizeList = QList<int>());
