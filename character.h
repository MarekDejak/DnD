#pragma once

#include <QString>
#include <QVariant>

#include <map>

class Character {
public:
    Character(){};
    Character(QString name) : m_name(name) {}
    Character(QString name, QString race, QString profession) : m_name(name), m_race(race), m_profession(profession) {}

    void setName(QString name) { m_name = name; }
    QString name() const { return m_name; }

    void setUsed(bool used) { m_used = used; }
    bool used() const { return m_used; }

    void setAbility(QString name, int value) { m_abilities[name] = value; };
    int getAbility(QString name) const { return m_abilities.at(name); };

    void setRace(QString race) { m_race = race; }
    QString getRace() const { return m_race; }

    void setProfession(QString profession) { m_profession = profession; }
    QString getProfession() const { return m_profession; }

    std::map<QString, int> getAllAbilities() const { return m_abilities; }

private:
    bool m_used = false;
    QString m_name;
    QString m_race;
    QString m_profession;
    std::map<QString, int> m_abilities;
    std::map<QString, QString> m_properties;
};

Q_DECLARE_METATYPE(Character*);
