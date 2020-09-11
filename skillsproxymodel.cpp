#include "skillsproxymodel.h"

#include "charactermodel.h"

SkillsProxyModel::SkillsProxyModel(CharacterModel* model, QObject* parent)
    : QAbstractListModel(parent), m_model(model) {}

int SkillsProxyModel::rowCount(const QModelIndex& index) const {
    Q_UNUSED(index);
    return m_model->data(m_model->index(0, 0), CharacterModel::SkillsRole).toStringList().count();
}

QVariant SkillsProxyModel::data(const QModelIndex& index, int role) const {
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        return m_model->data(m_model->index(0, 0), CharacterModel::SkillsRole).toStringList().at(index.row());
    }
    return QVariant();
}

bool SkillsProxyModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    if (role == Qt::EditRole) {
        m_model->editSkill(data(index, role).toString(), value.toString());
        return true;
    }
    return false;
}

Qt::ItemFlags SkillsProxyModel::flags(const QModelIndex& index) const {
    return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
}
