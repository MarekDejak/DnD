#pragma once
#include <QWidget>
#include <QSortFilterProxyModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class SelectCharacter;
}
QT_END_NAMESPACE
class CharacterModel;
class StringFilterModel;
class QListView;

class SelectCharacter : public QWidget {
    Q_OBJECT

public:
    SelectCharacter(CharacterModel* model, QWidget* parent = nullptr);
    ~SelectCharacter();

signals:
    void startPressed();

private slots:
    void editAbilities();
    void editCharacter();
    void deleteCharacter();
    void addNewCharacter();
    void addCharacterToUsed();
    void removeCharacterFromUsed();
    void writeToFile();

private:
    void onStartPressed();
    void setupViews();
    void setupProxyModels();
    void setupButtons();
    void loadButtonIcons();
    void updateFilterModels();

    Ui::SelectCharacter* m_ui;
    QStringList m_usedCharacters;
    CharacterModel* m_model;
    StringFilterModel* m_usedCharactersModel;
    StringFilterModel* m_availableCharactersModel;
    QListView* m_currentListView;
};
