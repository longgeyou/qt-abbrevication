/********************************************************************************
** Form generated from reading UI file 'dialogdirectory.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGDIRECTORY_H
#define UI_DIALOGDIRECTORY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame_9;
    QHBoxLayout *horizontalLayout_5;
    QFrame *frame_7;
    QLabel *label;
    QFrame *frame_11;
    QHBoxLayout *horizontalLayout_4;
    QFrame *frame_6;
    QLabel *label_currentDirValue;
    QHBoxLayout *horizontalLayout_3;
    QFrame *frame_5;
    QLabel *label_3;
    QFrame *frame_12;
    QLabel *label_result;
    QFrame *frame_10;
    QHBoxLayout *horizontalLayout_2;
    QFrame *frame_3;
    QLineEdit *lineEdit_dir;
    QPushButton *pushButton_fileBrowse;
    QPushButton *pushButton_apply;
    QFrame *frame_4;
    QFrame *frame_8;
    QHBoxLayout *horizontalLayout;
    QFrame *frame;
    QDialogButtonBox *buttonBox;
    QFrame *frame_2;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(441, 297);
        verticalLayout = new QVBoxLayout(Dialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        frame_9 = new QFrame(Dialog);
        frame_9->setObjectName(QStringLiteral("frame_9"));
        frame_9->setFrameShape(QFrame::StyledPanel);
        frame_9->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(frame_9);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        frame_7 = new QFrame(Dialog);
        frame_7->setObjectName(QStringLiteral("frame_7"));
        frame_7->setFrameShape(QFrame::StyledPanel);
        frame_7->setFrameShadow(QFrame::Raised);

        horizontalLayout_5->addWidget(frame_7);

        label = new QLabel(Dialog);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_5->addWidget(label);

        frame_11 = new QFrame(Dialog);
        frame_11->setObjectName(QStringLiteral("frame_11"));
        frame_11->setFrameShape(QFrame::StyledPanel);
        frame_11->setFrameShadow(QFrame::Raised);

        horizontalLayout_5->addWidget(frame_11);

        horizontalLayout_5->setStretch(0, 5);
        horizontalLayout_5->setStretch(1, 5);
        horizontalLayout_5->setStretch(2, 10);

        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        frame_6 = new QFrame(Dialog);
        frame_6->setObjectName(QStringLiteral("frame_6"));
        frame_6->setFrameShape(QFrame::StyledPanel);
        frame_6->setFrameShadow(QFrame::Raised);

        horizontalLayout_4->addWidget(frame_6);

        label_currentDirValue = new QLabel(Dialog);
        label_currentDirValue->setObjectName(QStringLiteral("label_currentDirValue"));

        horizontalLayout_4->addWidget(label_currentDirValue);

        horizontalLayout_4->setStretch(0, 5);
        horizontalLayout_4->setStretch(1, 11);

        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        frame_5 = new QFrame(Dialog);
        frame_5->setObjectName(QStringLiteral("frame_5"));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);

        horizontalLayout_3->addWidget(frame_5);

        label_3 = new QLabel(Dialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        frame_12 = new QFrame(Dialog);
        frame_12->setObjectName(QStringLiteral("frame_12"));
        frame_12->setFrameShape(QFrame::StyledPanel);
        frame_12->setFrameShadow(QFrame::Raised);

        horizontalLayout_3->addWidget(frame_12);

        label_result = new QLabel(Dialog);
        label_result->setObjectName(QStringLiteral("label_result"));

        horizontalLayout_3->addWidget(label_result);

        frame_10 = new QFrame(Dialog);
        frame_10->setObjectName(QStringLiteral("frame_10"));
        frame_10->setFrameShape(QFrame::StyledPanel);
        frame_10->setFrameShadow(QFrame::Raised);

        horizontalLayout_3->addWidget(frame_10);

        horizontalLayout_3->setStretch(0, 5);
        horizontalLayout_3->setStretch(1, 5);
        horizontalLayout_3->setStretch(2, 6);
        horizontalLayout_3->setStretch(3, 3);
        horizontalLayout_3->setStretch(4, 1);

        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        frame_3 = new QFrame(Dialog);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);

        horizontalLayout_2->addWidget(frame_3);

        lineEdit_dir = new QLineEdit(Dialog);
        lineEdit_dir->setObjectName(QStringLiteral("lineEdit_dir"));

        horizontalLayout_2->addWidget(lineEdit_dir);

        pushButton_fileBrowse = new QPushButton(Dialog);
        pushButton_fileBrowse->setObjectName(QStringLiteral("pushButton_fileBrowse"));

        horizontalLayout_2->addWidget(pushButton_fileBrowse);

        pushButton_apply = new QPushButton(Dialog);
        pushButton_apply->setObjectName(QStringLiteral("pushButton_apply"));

        horizontalLayout_2->addWidget(pushButton_apply);

        frame_4 = new QFrame(Dialog);
        frame_4->setObjectName(QStringLiteral("frame_4"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);

        horizontalLayout_2->addWidget(frame_4);

        horizontalLayout_2->setStretch(0, 5);
        horizontalLayout_2->setStretch(1, 6);
        horizontalLayout_2->setStretch(2, 4);
        horizontalLayout_2->setStretch(3, 3);
        horizontalLayout_2->setStretch(4, 2);

        verticalLayout->addLayout(horizontalLayout_2);

        frame_8 = new QFrame(Dialog);
        frame_8->setObjectName(QStringLiteral("frame_8"));
        frame_8->setFrameShape(QFrame::StyledPanel);
        frame_8->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(frame_8);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        frame = new QFrame(Dialog);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        horizontalLayout->addWidget(frame);

        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout->addWidget(buttonBox);

        frame_2 = new QFrame(Dialog);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);

        horizontalLayout->addWidget(frame_2);

        horizontalLayout->setStretch(0, 10);
        horizontalLayout->setStretch(1, 6);

        verticalLayout->addLayout(horizontalLayout);

        verticalLayout->setStretch(0, 4);
        verticalLayout->setStretch(1, 4);
        verticalLayout->setStretch(2, 4);
        verticalLayout->setStretch(3, 4);
        verticalLayout->setStretch(4, 4);
        verticalLayout->setStretch(5, 4);
        verticalLayout->setStretch(6, 4);
        frame_8->raise();
        frame_9->raise();

        retranslateUi(Dialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "\347\233\256\345\275\225", Q_NULLPTR));
        label->setText(QApplication::translate("Dialog", "\345\275\223\345\211\215\347\233\256\345\275\225", Q_NULLPTR));
        label_currentDirValue->setText(QApplication::translate("Dialog", "TextLabel", Q_NULLPTR));
        label_3->setText(QApplication::translate("Dialog", "\350\256\276\347\275\256\347\233\256\345\275\225", Q_NULLPTR));
        label_result->setText(QApplication::translate("Dialog", "[]", Q_NULLPTR));
        pushButton_fileBrowse->setText(QApplication::translate("Dialog", "...", Q_NULLPTR));
        pushButton_apply->setText(QApplication::translate("Dialog", "apply", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGDIRECTORY_H
