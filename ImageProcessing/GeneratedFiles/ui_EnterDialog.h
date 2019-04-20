/********************************************************************************
** Form generated from reading UI file 'EnterDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENTERDIALOG_H
#define UI_ENTERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_EnterDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QSlider *horizontalSlider;
    QSpinBox *spinBox;
    QSpacerItem *horizontalSpacer;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *EnterDialog)
    {
        if (EnterDialog->objectName().isEmpty())
            EnterDialog->setObjectName(QStringLiteral("EnterDialog"));
        EnterDialog->resize(403, 94);
        gridLayout = new QGridLayout(EnterDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(EnterDialog);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        horizontalSlider = new QSlider(EnterDialog);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(horizontalSlider, 0, 1, 1, 3);

        spinBox = new QSpinBox(EnterDialog);
        spinBox->setObjectName(QStringLiteral("spinBox"));

        gridLayout->addWidget(spinBox, 0, 4, 1, 1);

        horizontalSpacer = new QSpacerItem(132, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 2);

        okButton = new QPushButton(EnterDialog);
        okButton->setObjectName(QStringLiteral("okButton"));

        gridLayout->addWidget(okButton, 1, 2, 1, 1);

        cancelButton = new QPushButton(EnterDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        gridLayout->addWidget(cancelButton, 1, 3, 1, 2);


        retranslateUi(EnterDialog);
        QObject::connect(okButton, SIGNAL(clicked()), EnterDialog, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), EnterDialog, SLOT(reject()));
        QObject::connect(horizontalSlider, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));
        QObject::connect(spinBox, SIGNAL(valueChanged(int)), horizontalSlider, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(EnterDialog);
    } // setupUi

    void retranslateUi(QDialog *EnterDialog)
    {
        EnterDialog->setWindowTitle(QApplication::translate("EnterDialog", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("EnterDialog", "TextLabel", Q_NULLPTR));
        okButton->setText(QApplication::translate("EnterDialog", "OK", Q_NULLPTR));
        cancelButton->setText(QApplication::translate("EnterDialog", "Cancel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class EnterDialog: public Ui_EnterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENTERDIALOG_H
