/*
   Copyright (C) 2005 korewaisai
   korewaisai@yahoo.co.jp

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.
*/
#include <QtGui>

#include "Crontab.h"
#include "VariableModel.h"

QVariant VariableModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && role == Qt::DisplayRole) {
        Variable *v = static_cast<Variable*>(index.internalPointer());
        switch (index.column()) {
        case 0:
            return v->name;
        case 1:
            return v->value;
        }
    }

    return QVariant();

}

QVariant VariableModel::headerData(int section, Qt::Orientation orientation,
                                   int role) const
{

    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return tr("Name");
        case 1:
            return tr("Value");
        }
    }

    return QVariant();
}

bool VariableModel::removeVariable(int row)
{
    beginRemoveRows(QModelIndex(), row, row );

    delete variables->at(row);
    variables->removeAt(row);

    endRemoveRows();
    return true;
}

bool VariableModel::insertVariable(int row, Variable *var)
{
    beginInsertRows(QModelIndex(), row, row );

    if (variables->count() > 0 )
        variables->insert(row,var);
    else
        *variables << var;

    endInsertRows();
    return true;
}
void VariableModel::varDataChanged(const QModelIndex &idx)
{
    QModelIndex first = index(idx.row(), 0, QModelIndex());
    QModelIndex end = index(idx.row(), 1, QModelIndex());
    emit dataChanged(first, end);
}
Variable *VariableModel::getVariable(const QModelIndex &idx)
{
    return static_cast<Variable*>(idx.internalPointer());
}