/********************************************************************************
** Form generated from reading UI file 'ImageProcessing.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEPROCESSING_H
#define UI_IMAGEPROCESSING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageProcessingClass
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionExit;
    QAction *actionInfomation;
    QAction *actionAbout;
    QAction *actionRotate;
    QAction *actionRotate_180;
    QAction *actionZoom_In;
    QAction *actionZoom_out;
    QAction *actionReset;
    QAction *actionBinary;
    QAction *actionLaplace_filter;
    QAction *actionBlur_image;
    QAction *actionCanny_filter;
    QAction *actionHistogram;
    QAction *actionOpen_Video;
    QAction *actionFlip;
    QAction *actionFlip_Y_axis;
    QAction *actionEqualize_Histograms;
    QAction *actionHSV_Image;
    QAction *actionSegment_Image;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_2;
    QLabel *imageLabel;
    QToolBar *mainToolBar;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuProcess;
    QMenu *menuImage;
    QMenu *menuView;

    void setupUi(QMainWindow *ImageProcessingClass)
    {
        if (ImageProcessingClass->objectName().isEmpty())
            ImageProcessingClass->setObjectName(QStringLiteral("ImageProcessingClass"));
        ImageProcessingClass->resize(1094, 784);
        actionOpen = new QAction(ImageProcessingClass);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(ImageProcessingClass);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionExit = new QAction(ImageProcessingClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionInfomation = new QAction(ImageProcessingClass);
        actionInfomation->setObjectName(QStringLiteral("actionInfomation"));
        actionAbout = new QAction(ImageProcessingClass);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionRotate = new QAction(ImageProcessingClass);
        actionRotate->setObjectName(QStringLiteral("actionRotate"));
        actionRotate_180 = new QAction(ImageProcessingClass);
        actionRotate_180->setObjectName(QStringLiteral("actionRotate_180"));
        actionZoom_In = new QAction(ImageProcessingClass);
        actionZoom_In->setObjectName(QStringLiteral("actionZoom_In"));
        actionZoom_out = new QAction(ImageProcessingClass);
        actionZoom_out->setObjectName(QStringLiteral("actionZoom_out"));
        actionReset = new QAction(ImageProcessingClass);
        actionReset->setObjectName(QStringLiteral("actionReset"));
        actionBinary = new QAction(ImageProcessingClass);
        actionBinary->setObjectName(QStringLiteral("actionBinary"));
        actionLaplace_filter = new QAction(ImageProcessingClass);
        actionLaplace_filter->setObjectName(QStringLiteral("actionLaplace_filter"));
        actionBlur_image = new QAction(ImageProcessingClass);
        actionBlur_image->setObjectName(QStringLiteral("actionBlur_image"));
        actionCanny_filter = new QAction(ImageProcessingClass);
        actionCanny_filter->setObjectName(QStringLiteral("actionCanny_filter"));
        actionHistogram = new QAction(ImageProcessingClass);
        actionHistogram->setObjectName(QStringLiteral("actionHistogram"));
        actionOpen_Video = new QAction(ImageProcessingClass);
        actionOpen_Video->setObjectName(QStringLiteral("actionOpen_Video"));
        actionFlip = new QAction(ImageProcessingClass);
        actionFlip->setObjectName(QStringLiteral("actionFlip"));
        actionFlip_Y_axis = new QAction(ImageProcessingClass);
        actionFlip_Y_axis->setObjectName(QStringLiteral("actionFlip_Y_axis"));
        actionEqualize_Histograms = new QAction(ImageProcessingClass);
        actionEqualize_Histograms->setObjectName(QStringLiteral("actionEqualize_Histograms"));
        actionHSV_Image = new QAction(ImageProcessingClass);
        actionHSV_Image->setObjectName(QStringLiteral("actionHSV_Image"));
        actionSegment_Image = new QAction(ImageProcessingClass);
        actionSegment_Image->setObjectName(QStringLiteral("actionSegment_Image"));
        centralWidget = new QWidget(ImageProcessingClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(2, 2, 2, 2);
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1088, 731));
        gridLayout_2 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        imageLabel = new QLabel(scrollAreaWidgetContents);
        imageLabel->setObjectName(QStringLiteral("imageLabel"));
        imageLabel->setStyleSheet(QLatin1String("background-color: rgb(0, 0, 0);\n"
"color: rgb(255, 255, 255);"));
        imageLabel->setScaledContents(false);
        imageLabel->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(imageLabel, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scrollArea, 0, 0, 1, 1);

        ImageProcessingClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(ImageProcessingClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ImageProcessingClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        menuBar = new QMenuBar(ImageProcessingClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1094, 31));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuProcess = new QMenu(menuBar);
        menuProcess->setObjectName(QStringLiteral("menuProcess"));
        menuImage = new QMenu(menuBar);
        menuImage->setObjectName(QStringLiteral("menuImage"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        ImageProcessingClass->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuProcess->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuImage->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addSeparator();
        menuFile->addAction(actionOpen_Video);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuProcess->addAction(actionBinary);
        menuProcess->addAction(actionBlur_image);
        menuProcess->addAction(actionHSV_Image);
        menuProcess->addAction(actionSegment_Image);
        menuProcess->addSeparator();
        menuProcess->addAction(actionLaplace_filter);
        menuProcess->addAction(actionCanny_filter);
        menuProcess->addSeparator();
        menuProcess->addAction(actionEqualize_Histograms);
        menuImage->addAction(actionInfomation);
        menuImage->addAction(actionAbout);
        menuView->addAction(actionRotate);
        menuView->addAction(actionFlip);
        menuView->addSeparator();
        menuView->addAction(actionZoom_In);
        menuView->addAction(actionZoom_out);
        menuView->addSeparator();
        menuView->addAction(actionHistogram);
        menuView->addSeparator();
        menuView->addAction(actionReset);

        retranslateUi(ImageProcessingClass);

        QMetaObject::connectSlotsByName(ImageProcessingClass);
    } // setupUi

    void retranslateUi(QMainWindow *ImageProcessingClass)
    {
        ImageProcessingClass->setWindowTitle(QApplication::translate("ImageProcessingClass", "ImageProcessing", Q_NULLPTR));
        actionOpen->setText(QApplication::translate("ImageProcessingClass", "Open Image", Q_NULLPTR));
        actionSave->setText(QApplication::translate("ImageProcessingClass", "Save Image", Q_NULLPTR));
        actionExit->setText(QApplication::translate("ImageProcessingClass", "Exit", Q_NULLPTR));
        actionInfomation->setText(QApplication::translate("ImageProcessingClass", "Infomation", Q_NULLPTR));
        actionAbout->setText(QApplication::translate("ImageProcessingClass", "About", Q_NULLPTR));
        actionRotate->setText(QApplication::translate("ImageProcessingClass", "Rotate", Q_NULLPTR));
        actionRotate_180->setText(QApplication::translate("ImageProcessingClass", "Rotate 180\302\260", Q_NULLPTR));
        actionZoom_In->setText(QApplication::translate("ImageProcessingClass", "Zoom In", Q_NULLPTR));
        actionZoom_out->setText(QApplication::translate("ImageProcessingClass", "Zoom Out", Q_NULLPTR));
        actionReset->setText(QApplication::translate("ImageProcessingClass", "Reset", Q_NULLPTR));
        actionBinary->setText(QApplication::translate("ImageProcessingClass", "Binary Image", Q_NULLPTR));
        actionLaplace_filter->setText(QApplication::translate("ImageProcessingClass", "Laplace Filter", Q_NULLPTR));
        actionBlur_image->setText(QApplication::translate("ImageProcessingClass", "Blur Image", Q_NULLPTR));
        actionCanny_filter->setText(QApplication::translate("ImageProcessingClass", "Canny Filter", Q_NULLPTR));
        actionHistogram->setText(QApplication::translate("ImageProcessingClass", "Histogram", Q_NULLPTR));
        actionOpen_Video->setText(QApplication::translate("ImageProcessingClass", "Open Video", Q_NULLPTR));
        actionFlip->setText(QApplication::translate("ImageProcessingClass", "Flip", Q_NULLPTR));
        actionFlip_Y_axis->setText(QApplication::translate("ImageProcessingClass", "Flip Y-axis", Q_NULLPTR));
        actionEqualize_Histograms->setText(QApplication::translate("ImageProcessingClass", "Equalize Histograms", Q_NULLPTR));
        actionHSV_Image->setText(QApplication::translate("ImageProcessingClass", "HSV Image", Q_NULLPTR));
        actionSegment_Image->setText(QApplication::translate("ImageProcessingClass", "Segment Image", Q_NULLPTR));
        imageLabel->setText(QApplication::translate("ImageProcessingClass", "image", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("ImageProcessingClass", "File", Q_NULLPTR));
        menuProcess->setTitle(QApplication::translate("ImageProcessingClass", "Process", Q_NULLPTR));
        menuImage->setTitle(QApplication::translate("ImageProcessingClass", "Help", Q_NULLPTR));
        menuView->setTitle(QApplication::translate("ImageProcessingClass", "View", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ImageProcessingClass: public Ui_ImageProcessingClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEPROCESSING_H
