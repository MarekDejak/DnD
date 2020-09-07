#pragma once

#include <QString>
#include <QVariant>

#include <map>

class Character {
public:
    Character(){};
    Character(QString name) : m_name(name) {}

    void setName(QString name) { m_name = name; }
    QString name() const { return m_name; }

    void setAbility(QString name, int value) { m_abilities[name] = value; };
    int getAbility(QString name) const { return m_abilities.at(name); };

    std::map<QString, int> getAllAbilities() const { return m_abilities; }

private:
    QString m_name;
    std::map<QString, int> m_abilities;
};

Q_DECLARE_METATYPE(Character*);
