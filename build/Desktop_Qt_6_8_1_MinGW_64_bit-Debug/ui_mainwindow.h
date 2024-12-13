/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_as;
    QAction *actionCopy;
    QAction *actionCut;
    QAction *actionPaste;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionNew;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTextEdit *textEdit;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuTools;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName("actionOpen");
        QIcon icon;
        if (QIcon::hasThemeIcon(QIcon::ThemeIcon::DocumentOpen)) {
            icon = QIcon::fromTheme(QIcon::ThemeIcon::DocumentOpen);
        } else {
            icon.addFile(QString::fromUtf8("open.jpg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        }
        actionOpen->setIcon(icon);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName("actionSave");
        QIcon icon1;
        if (QIcon::hasThemeIcon(QIcon::ThemeIcon::DocumentSave)) {
            icon1 = QIcon::fromTheme(QIcon::ThemeIcon::DocumentSave);
        } else {
            icon1.addFile(QString::fromUtf8("save.jpg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        }
        actionSave->setIcon(icon1);
        actionSave_as = new QAction(MainWindow);
        actionSave_as->setObjectName("actionSave_as");
        QIcon icon2;
        if (QIcon::hasThemeIcon(QIcon::ThemeIcon::DocumentSaveAs)) {
            icon2 = QIcon::fromTheme(QIcon::ThemeIcon::DocumentSaveAs);
        } else {
            icon2.addFile(QString::fromUtf8("save as.jpg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        }
        actionSave_as->setIcon(icon2);
        actionCopy = new QAction(MainWindow);
        actionCopy->setObjectName("actionCopy");
        QIcon icon3;
        if (QIcon::hasThemeIcon(QIcon::ThemeIcon::EditCopy)) {
            icon3 = QIcon::fromTheme(QIcon::ThemeIcon::EditCopy);
        } else {
            icon3.addFile(QString::fromUtf8("copy.jpg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        }
        actionCopy->setIcon(icon3);
        actionCut = new QAction(MainWindow);
        actionCut->setObjectName("actionCut");
        QIcon icon4;
        if (QIcon::hasThemeIcon(QIcon::ThemeIcon::EditCut)) {
            icon4 = QIcon::fromTheme(QIcon::ThemeIcon::EditCut);
        } else {
            icon4.addFile(QString::fromUtf8("cut.jpg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        }
        actionCut->setIcon(icon4);
        actionPaste = new QAction(MainWindow);
        actionPaste->setObjectName("actionPaste");
        QIcon icon5;
        if (QIcon::hasThemeIcon(QIcon::ThemeIcon::EditPaste)) {
            icon5 = QIcon::fromTheme(QIcon::ThemeIcon::EditPaste);
        } else {
            icon5.addFile(QString::fromUtf8("paste.jpg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        }
        actionPaste->setIcon(icon5);
        actionUndo = new QAction(MainWindow);
        actionUndo->setObjectName("actionUndo");
        QIcon icon6;
        if (QIcon::hasThemeIcon(QIcon::ThemeIcon::EditUndo)) {
            icon6 = QIcon::fromTheme(QIcon::ThemeIcon::EditUndo);
        } else {
            icon6.addFile(QString::fromUtf8("undo.jpg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        }
        actionUndo->setIcon(icon6);
        actionRedo = new QAction(MainWindow);
        actionRedo->setObjectName("actionRedo");
        QIcon icon7;
        if (QIcon::hasThemeIcon(QIcon::ThemeIcon::EditRedo)) {
            icon7 = QIcon::fromTheme(QIcon::ThemeIcon::EditRedo);
        } else {
            icon7.addFile(QString::fromUtf8("redo.jpg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        }
        actionRedo->setIcon(icon7);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName("actionNew");
        QIcon icon8;
        if (QIcon::hasThemeIcon(QIcon::ThemeIcon::DocumentNew)) {
            icon8 = QIcon::fromTheme(QIcon::ThemeIcon::DocumentNew);
        } else {
            icon8.addFile(QString::fromUtf8("new.jpg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        }
        actionNew->setIcon(icon8);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName("textEdit");

        verticalLayout->addWidget(textEdit);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName("menuEdit");
        menuTools = new QMenu(menubar);
        menuTools->setObjectName("menuTools");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuTools->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_as);
        menuEdit->addAction(actionCopy);
        menuEdit->addAction(actionCut);
        menuEdit->addAction(actionPaste);
        menuEdit->addSeparator();
        menuEdit->addAction(actionUndo);
        menuEdit->addAction(actionRedo);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        actionSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        actionSave_as->setText(QCoreApplication::translate("MainWindow", "Save as", nullptr));
        actionCopy->setText(QCoreApplication::translate("MainWindow", "Copy", nullptr));
        actionCut->setText(QCoreApplication::translate("MainWindow", "Cut", nullptr));
        actionPaste->setText(QCoreApplication::translate("MainWindow", "Paste", nullptr));
        actionUndo->setText(QCoreApplication::translate("MainWindow", "Undo", nullptr));
        actionRedo->setText(QCoreApplication::translate("MainWindow", "Redo", nullptr));
        actionNew->setText(QCoreApplication::translate("MainWindow", "New", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("MainWindow", "Edit", nullptr));
        menuTools->setTitle(QCoreApplication::translate("MainWindow", "Tools", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
