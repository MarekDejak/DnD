#pragma once

#include <QAbstractListModel>

#include "charactermodel.h"

class SkillsProxyModel : public QAbstractListModel {
public:
    SkillsProxyModel(CharacterModel* model, QObject* parent);

    virtual int rowCount(const QModelIndex& index) const override;
    virtual QVariant data(const QModelIndex& index, int role) const override;
    virtual bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    virtual Qt::ItemFlags flags(const QModelIndex& index) const override;

    void removeSkill(QString skill);
    void addSkill();

private:
    CharacterModel* m_model;
};
