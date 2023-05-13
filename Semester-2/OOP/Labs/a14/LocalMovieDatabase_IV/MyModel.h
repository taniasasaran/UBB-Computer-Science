//
// Created by TANIA on 5/29/2022.
//
#pragma once
#include <QAbstractTableModel>
#include "domain.h"

class MyModel : public QAbstractTableModel{
private:
    std::vector<Movie> watchlist;
public:
    MyModel(std::vector<Movie> wl);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void addMovie(const Movie &m);

    void clearData();
};
