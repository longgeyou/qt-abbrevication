#ifndef ABBREVIATION_H
#define ABBREVIATION_H

#include <QMainWindow>
#include <QtWidgets/QPushButton>
#include <stack>
#include <array>




//常量
#define SUB_DIR_PATH ".share/abbreviation"  //路径
#define CONFIG_FILE ".config" //配置文件名
#define DATA_DIR "data" //存放数据的文件名
#define ABBREVIATION_MAX_SIZE 16   //缩写的长度


//结构体
typedef struct ConfigData{  //配置项的数据结构
    QString property;
    QString value;
}struct_configData;

 struct AbbreviationData{  //缩写解释项的数据结构
    QString abbre;      //字母缩写
    QString describe;   //解释
    QString from;       //来自哪个文件
    QString doc;       //来自哪个文档
};


//属性名称
#define PROPERTY_NAME_HOME_DIR "HomeDir"
#define PROPERTY_DOCUMENT "DOCUMENT"
namespace Ui {
class Abbreviation;
class Dialog;
}


class Abbreviation : public QMainWindow
{
    Q_OBJECT

public:
    explicit Abbreviation(QWidget *parent = 0);
    ~Abbreviation();

    std::vector<QPushButton *> pushButtonVector;  //按钮对象指针集合（用栈存储）
    void setUi();   //设置UI
    void init();    //初始化

    //1、路径和配置文件
    QString current_dir_path;
    QString config_file_path;
    bool pathIsExist;
    bool configFIleIsExist;
    QString configFIleName;
    void init_dir();
    std::vector<struct_configData> configData;    //配置数据
    bool configFileLoad(QString configFileName);    //载入配置文件
    bool getConfigValue(QString propertyName, QString *value);  //获取配置值
    bool getConfigValue(QString propertyName, QString value);    //设置配置值
    bool configFileSave(QString configFileName); //属性存入配置
    bool configDataIsOk;

    //2、缩写解释的文件处理
    std::vector<struct AbbreviationData> abbreviationData;      //缩写信息的存储
    void abbreFilePro(QString fileName);    //单个文件内容的处理
    std::vector<QString> vector_fileName;      //文件名的存储
    void dirFindAllFile(QString dirName);       //目录下找到所有文件
    void abbreEntryPro(QString fileName, QString entry);      //单条数据的处理
    QString currentReferDocument;

    //3、搜索显示
    void searchFilter(QString key);
    std::vector<struct AbbreviationData> searchResult;      //搜索结果


public slots:
    //主窗口
    void slot_addButtonTest(); //添加按钮
    void slot_test();  //测试
    void slot_textShow();   //文本显示
    void slot_search();     //搜索
    void slot_abbreButtonOnClicked(int num);

    //目录对话框
    void slot_dirSet();
    void slot_fileBrowse();
    void slot_dialogAccept();
    void slot_dialogReject();
    void slot_dialogApply();
    void slot_fileProTest();



private:
    Ui::Abbreviation *ui;
    Ui::Dialog *dialogUi;
    QDialog *dialogObj;
};

#endif // ABBREVIATION_H




