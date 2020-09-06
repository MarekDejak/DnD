#include "stringfiltermodel.h"

StringFilterModel::StringFilterModel(QObject* parent) : QSortFilterProxyModel(parent) {}

void StringFilterModel::setAcceptOnFound(bool accept) {
    m_acceptOnFound = accept;
}

bool StringFilterModel::filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const {
    const auto sourceIndex = sourceModel()->index(sourceRow, 0, sourceParent);
    const auto entryOnList = m_stringList.contains(sourceModel()->data(sourceIndex).toString());
    return m_acceptOnFound ? entryOnList : !entryOnList;
}

void StringFilterModel::setFilterStringList(QStringList stringList) {
    m_stringList = stringList;
    invalidateFilter();
}
