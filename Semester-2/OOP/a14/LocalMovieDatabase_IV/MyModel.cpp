//
// Created by TANIA on 5/29/2022.
//

#include <QFont>
#include <QBrush>
#include "MyModel.h"
MyModel::MyModel(std::vector<Movie> wl) : watchlist{wl} {
}

int MyModel::rowCount(const QModelIndex & parent) const
{
    return this->watchlist.size();
}

int MyModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 5;
}

QVariant MyModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int column = index.column();
    Movie m = this->watchlist[row];

    switch (role) {
        case Qt::DisplayRole:
            switch (column)
            {
                case 0:
                    return QString::fromStdString(m.getTitle());
                case 1:
                    return QString::fromStdString(m.getGenre());
                case 2:
                    return QString::number(m.getYearRelease());
                case 3:
                    return QString::number(m.getNumberLikes());
                case 4:
                    return QString::fromStdString(m.getTrailer());
                default:
                    break;
            }
        case Qt::FontRole: {
            QFont font{"Verdana", 15};
            return font;
        }
        case Qt::BackgroundRole: {
            if (row % 2 == 1)
            {
                QBrush brush{ QColor{220, 220, 220} };
                return brush;
            }
        }
    }
    return QVariant();
}

QVariant MyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
    {
        if (role == Qt::DisplayRole)
        {
            switch (section)
            {
                case 0:
                    return QString{ "Title" };
                case 1:
                    return QString{ "Genre" };
                case 2:
                    return QString{ "Release year" };
                case 3:
                    return QString{ "Likes" };
                case 4:
                    return QString{ "Trailer" };
                default:
                    break;
            }
        }
    }

    return QVariant();
}

void MyModel::addMovie(const Movie& m)
{
    int n = this->watchlist.size();
    this->beginInsertRows(QModelIndex{}, n, n);
    this->watchlist.push_back(m);
    this->endInsertRows();
}

void MyModel::clearData()
{
    this->beginResetModel();
    this->watchlist.clear();
    this->endResetModel();
}

