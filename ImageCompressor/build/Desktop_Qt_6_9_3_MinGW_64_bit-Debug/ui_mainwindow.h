/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *Compression;
    QHBoxLayout *horizontalLayout_9;
    QGroupBox *OriginalImage;
    QVBoxLayout *verticalLayout_2;
    QPushButton *btnLoad;
    QPushButton *btnCompress;
    QPushButton *lblRatio;
    QGroupBox *Controls;
    QVBoxLayout *verticalLayout_3;
    QLabel *lblOriginal;
    QWidget *Decompression;
    QHBoxLayout *horizontalLayout_10;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_4;
    QLabel *labelCompressedName;
    QPushButton *btnDecompress;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_5;
    QLabel *lblDecompressed;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        Compression = new QWidget();
        Compression->setObjectName("Compression");
        horizontalLayout_9 = new QHBoxLayout(Compression);
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        OriginalImage = new QGroupBox(Compression);
        OriginalImage->setObjectName("OriginalImage");
        verticalLayout_2 = new QVBoxLayout(OriginalImage);
        verticalLayout_2->setObjectName("verticalLayout_2");
        btnLoad = new QPushButton(OriginalImage);
        btnLoad->setObjectName("btnLoad");

        verticalLayout_2->addWidget(btnLoad);

        btnCompress = new QPushButton(OriginalImage);
        btnCompress->setObjectName("btnCompress");

        verticalLayout_2->addWidget(btnCompress);

        lblRatio = new QPushButton(OriginalImage);
        lblRatio->setObjectName("lblRatio");

        verticalLayout_2->addWidget(lblRatio);


        horizontalLayout_9->addWidget(OriginalImage);

        Controls = new QGroupBox(Compression);
        Controls->setObjectName("Controls");
        verticalLayout_3 = new QVBoxLayout(Controls);
        verticalLayout_3->setObjectName("verticalLayout_3");
        lblOriginal = new QLabel(Controls);
        lblOriginal->setObjectName("lblOriginal");
        lblOriginal->setMinimumSize(QSize(300, 300));
        lblOriginal->setScaledContents(true);

        verticalLayout_3->addWidget(lblOriginal);


        horizontalLayout_9->addWidget(Controls);

        tabWidget->addTab(Compression, QString());
        Decompression = new QWidget();
        Decompression->setObjectName("Decompression");
        horizontalLayout_10 = new QHBoxLayout(Decompression);
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        groupBox = new QGroupBox(Decompression);
        groupBox->setObjectName("groupBox");
        verticalLayout_4 = new QVBoxLayout(groupBox);
        verticalLayout_4->setObjectName("verticalLayout_4");
        labelCompressedName = new QLabel(groupBox);
        labelCompressedName->setObjectName("labelCompressedName");

        verticalLayout_4->addWidget(labelCompressedName);

        btnDecompress = new QPushButton(groupBox);
        btnDecompress->setObjectName("btnDecompress");

        verticalLayout_4->addWidget(btnDecompress);


        horizontalLayout_10->addWidget(groupBox);

        groupBox_2 = new QGroupBox(Decompression);
        groupBox_2->setObjectName("groupBox_2");
        verticalLayout_5 = new QVBoxLayout(groupBox_2);
        verticalLayout_5->setObjectName("verticalLayout_5");
        lblDecompressed = new QLabel(groupBox_2);
        lblDecompressed->setObjectName("lblDecompressed");
        lblDecompressed->setMinimumSize(QSize(300, 300));
        lblDecompressed->setScaledContents(true);

        verticalLayout_5->addWidget(lblDecompressed);


        horizontalLayout_10->addWidget(groupBox_2);

        tabWidget->addTab(Decompression, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        OriginalImage->setTitle(QCoreApplication::translate("MainWindow", "Controls", nullptr));
        btnLoad->setText(QCoreApplication::translate("MainWindow", "Open Image", nullptr));
        btnCompress->setText(QCoreApplication::translate("MainWindow", "Compress", nullptr));
        lblRatio->setText(QCoreApplication::translate("MainWindow", "Compression Ratio: ", nullptr));
        Controls->setTitle(QCoreApplication::translate("MainWindow", "Original Image", nullptr));
        lblOriginal->setText(QCoreApplication::translate("MainWindow", "Image Label", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Compression), QCoreApplication::translate("MainWindow", "Compression", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Compressed File", nullptr));
        labelCompressedName->setText(QCoreApplication::translate("MainWindow", "Filename", nullptr));
        btnDecompress->setText(QCoreApplication::translate("MainWindow", "Decompress", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "GroupBox", nullptr));
        lblDecompressed->setText(QCoreApplication::translate("MainWindow", "Decompressed image", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Decompression), QCoreApplication::translate("MainWindow", "Decompression", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
