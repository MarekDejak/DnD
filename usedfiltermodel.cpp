#include "usedfiltermodel.h"

#include "charactermodel.h"

UsedFilterModel::UsedFilterModel(QObject* parent) : QSortFilterProxyModel(parent) {}

void UsedFilterModel::setAcceptOnFound(bool accept) {
    m_acceptOnFound = accept;
}

bool UsedFilterModel::filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const {
    const auto sourceIndex = sourceModel()->index(sourceRow, 0, sourceParent);
    const auto entryUsed = sourceModel()->data(sourceIndex, CharacterModel::UsedRole).toBool();

    return m_acceptOnFound ? entryUsed : !entryUsed;
}
