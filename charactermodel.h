#pragma once

#include "character.h"

#include <QAbstractTableModel>
#include <QFile>

class CharacterModel : public QAbstractTableModel {
    Q_OBJECT
public:
    CharacterModel(QWidget* parent = nullptr);
    ~CharacterModel();

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;

    void setFile(QString fileName);

public slots:
    void writeDataFile();

signals:
    void fatal(QString fatal);
    void error(QString error);
    void warning(QString warning);

private:
    bool openFile();
    QString getUniqueCharacterName();
    void emitWarningAndDeleteCharacter(Character* character);
    void parseDataFile();

    QStringList m_skills;
    QVector<Character*> m_characters;
    QFile m_dataFile;
};
