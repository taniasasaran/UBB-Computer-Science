//
// Created by TANIA on 5/29/2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ui_TableViewWidget.h" resolved

#include "ui_TableViewWidget.h"
#include "MyModel.h"
#include "QWidget"
#include <QSortFilterProxyModel>

TableViewWidget::TableViewWidget(MyModel *model, QWidget *parent, Ui::TableViewWidget _ui) : QWidget(parent), ui(ui) {
    ui.setupUi(this);

//    ui.productsTableView->setModel(model);

    QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel{};
    proxyModel->setSourceModel(model);
    proxyModel->setSortRole(Qt::UserRole);
    ui.productsTableView->setModel(proxyModel);
    ui.productsTableView->setSortingEnabled(true);
}

TableViewWidget::~TableViewWidget()
{
}

