#pragma once
#include <QMainWindow>
#include <QSortFilterProxyModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
class CharacterModel;
class StringFilterModel;
class QListView;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void editCharacter();
    void deleteCharacter();
    void addNewCharacter();
    void addCharacterToUsed();
    void removeCharacterFromUsed();
    void writeToFile();

private:
    void generateCSV();
    void setupViews();
    void setupModel();
    void setupWindow();
    void setupButtons();
    void loadButtonIcons();
    void updateFilterModels();

    Ui::MainWindow* m_ui;
    QStringList m_usedCharacters;
    CharacterModel* m_model;
    StringFilterModel* m_usedCharactersModel;
    StringFilterModel* m_availableCharactersModel;
    QListView* m_currentListView;
};
