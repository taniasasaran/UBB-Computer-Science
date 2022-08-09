//
// Created by TANIA on 5/29/2022.
//

#pragma once

#include <QWidget>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "MyModel.h"

QT_BEGIN_NAMESPACE

class Ui_TableViewWidget
{
public:
    QVBoxLayout *verticalLayout;
    QTableView *productsTableView;

    void setupUi(QWidget *TableViewWidget)
    {
        if (TableViewWidget->objectName().isEmpty())
            TableViewWidget->setObjectName(QString::fromUtf8("TableViewWidget"));
        TableViewWidget->resize(400, 300);
        verticalLayout = new QVBoxLayout(TableViewWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        productsTableView = new QTableView(TableViewWidget);
        productsTableView->setObjectName(QString::fromUtf8("productsTableView"));
        QFont font;
        font.setPointSize(16);
        productsTableView->setFont(font);

        verticalLayout->addWidget(productsTableView);

        retranslateUi(TableViewWidget);

        QMetaObject::connectSlotsByName(TableViewWidget);
    } // setupUi

    void retranslateUi(QWidget *TableViewWidget)
    {
        TableViewWidget->setWindowTitle(QCoreApplication::translate("TableViewWidget", "TableViewWidget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TableViewWidget: public Ui_TableViewWidget {
        TableViewWidget(MyModel *model, QWidget *parent);
    };
} // namespace Ui

QT_END_NAMESPACE

class TableViewWidget : public QWidget
{
Q_OBJECT
private:
    Ui::TableViewWidget ui;
public:
    TableViewWidget(MyModel *model, QWidget *parent, Ui::TableViewWidget _ui);
    ~TableViewWidget();
};

