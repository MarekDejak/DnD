#pragma once

#include <QSortFilterProxyModel>

class UsedFilterModel : public QSortFilterProxyModel {
public:
    UsedFilterModel(QObject* parent);

    void setAcceptOnFound(bool accept);
    void setFilterStringList(QStringList stringList);
    bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;

private:
    bool m_acceptOnFound = true;
    QStringList m_stringList;
};
