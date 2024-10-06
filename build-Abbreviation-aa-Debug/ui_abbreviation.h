/********************************************************************************
** Form generated from reading UI file 'abbreviation.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABBREVIATION_H
#define UI_ABBREVIATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Abbreviation
{
public:
    QAction *action_add_button;
    QAction *action_text_show;
    QAction *action_set_content;
    QAction *action;
    QAction *action_fileProTest;
    QAction *action_test;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEdit_search;
    QPushButton *pushButton_6;
    QScrollArea *scrollArea_abbreDisplay;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_abbreButton;
    QSpacerItem *verticalSpacer;
    QTextBrowser *textBrowser_main;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menu_help;
    QMenu *menu_content;
    QMenu *menu_test;
    QMenu *menu;

    void setupUi(QMainWindow *Abbreviation)
    {
        if (Abbreviation->objectName().isEmpty())
            Abbreviation->setObjectName(QStringLiteral("Abbreviation"));
        Abbreviation->setWindowModality(Qt::NonModal);
        Abbreviation->resize(816, 588);
        Abbreviation->setLayoutDirection(Qt::LeftToRight);
        Abbreviation->setStyleSheet(QStringLiteral(""));
        action_add_button = new QAction(Abbreviation);
        action_add_button->setObjectName(QStringLiteral("action_add_button"));
        action_text_show = new QAction(Abbreviation);
        action_text_show->setObjectName(QStringLiteral("action_text_show"));
        action_set_content = new QAction(Abbreviation);
        action_set_content->setObjectName(QStringLiteral("action_set_content"));
        action = new QAction(Abbreviation);
        action->setObjectName(QStringLiteral("action"));
        action_fileProTest = new QAction(Abbreviation);
        action_fileProTest->setObjectName(QStringLiteral("action_fileProTest"));
        action_test = new QAction(Abbreviation);
        action_test->setObjectName(QStringLiteral("action_test"));
        centralWidget = new QWidget(Abbreviation);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        lineEdit_search = new QLineEdit(centralWidget);
        lineEdit_search->setObjectName(QStringLiteral("lineEdit_search"));

        horizontalLayout_2->addWidget(lineEdit_search);

        pushButton_6 = new QPushButton(centralWidget);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        horizontalLayout_2->addWidget(pushButton_6);


        verticalLayout->addLayout(horizontalLayout_2);

        scrollArea_abbreDisplay = new QScrollArea(centralWidget);
        scrollArea_abbreDisplay->setObjectName(QStringLiteral("scrollArea_abbreDisplay"));
        scrollArea_abbreDisplay->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea_abbreDisplay->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea_abbreDisplay->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        scrollArea_abbreDisplay->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 222, 488));
        verticalLayout_abbreButton = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_abbreButton->setSpacing(6);
        verticalLayout_abbreButton->setContentsMargins(11, 11, 11, 11);
        verticalLayout_abbreButton->setObjectName(QStringLiteral("verticalLayout_abbreButton"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_abbreButton->addItem(verticalSpacer);

        scrollArea_abbreDisplay->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea_abbreDisplay);


        horizontalLayout->addLayout(verticalLayout);

        textBrowser_main = new QTextBrowser(centralWidget);
        textBrowser_main->setObjectName(QStringLiteral("textBrowser_main"));
        textBrowser_main->setEnabled(true);

        horizontalLayout->addWidget(textBrowser_main);

        horizontalLayout->setStretch(0, 2);
        horizontalLayout->setStretch(1, 5);

        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        Abbreviation->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Abbreviation);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Abbreviation->setStatusBar(statusBar);
        menuBar = new QMenuBar(Abbreviation);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 816, 23));
        menuBar->setNativeMenuBar(false);
        menu_help = new QMenu(menuBar);
        menu_help->setObjectName(QStringLiteral("menu_help"));
        menu_content = new QMenu(menuBar);
        menu_content->setObjectName(QStringLiteral("menu_content"));
        menu_test = new QMenu(menuBar);
        menu_test->setObjectName(QStringLiteral("menu_test"));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        Abbreviation->setMenuBar(menuBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_content->menuAction());
        menuBar->addAction(menu_help->menuAction());
        menuBar->addAction(menu_test->menuAction());
        menu_content->addAction(action_set_content);
        menu_test->addAction(action_add_button);
        menu_test->addAction(action_text_show);
        menu_test->addAction(action_fileProTest);
        menu_test->addAction(action_test);
        menu->addAction(action);

        retranslateUi(Abbreviation);

        QMetaObject::connectSlotsByName(Abbreviation);
    } // setupUi

    void retranslateUi(QMainWindow *Abbreviation)
    {
        Abbreviation->setWindowTitle(QApplication::translate("Abbreviation", "Abbreviation", Q_NULLPTR));
        action_add_button->setText(QApplication::translate("Abbreviation", "\346\226\260\345\242\236\346\214\211\351\222\256", Q_NULLPTR));
        action_text_show->setText(QApplication::translate("Abbreviation", "\346\226\207\346\234\254\346\230\276\347\244\272", Q_NULLPTR));
        action_set_content->setText(QApplication::translate("Abbreviation", "\350\256\276\347\275\256\347\233\256\345\275\225", Q_NULLPTR));
        action->setText(QApplication::translate("Abbreviation", "\346\211\253\346\217\217", Q_NULLPTR));
        action_fileProTest->setText(QApplication::translate("Abbreviation", "\346\226\207\346\234\254\345\244\204\347\220\206\346\265\213\350\257\225", Q_NULLPTR));
        action_test->setText(QApplication::translate("Abbreviation", "\346\265\213\350\257\225", Q_NULLPTR));
        pushButton_6->setText(QApplication::translate("Abbreviation", "PushButton", Q_NULLPTR));
        menu_help->setTitle(QApplication::translate("Abbreviation", "\345\270\256\345\212\251", Q_NULLPTR));
        menu_content->setTitle(QApplication::translate("Abbreviation", "\350\256\276\347\275\256", Q_NULLPTR));
        menu_test->setTitle(QApplication::translate("Abbreviation", "\346\265\213\350\257\225", Q_NULLPTR));
        menu->setTitle(QApplication::translate("Abbreviation", "\346\226\207\344\273\266", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Abbreviation: public Ui_Abbreviation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABBREVIATION_H
