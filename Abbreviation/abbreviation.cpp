#include "abbreviation.h"
#include "ui_abbreviation.h"
#include "ui_dialogdirectory.h"
#include <QFileDialog>
#include <qDebug>
#include <QStandardPaths>



//类Abbreviation的构造函数
Abbreviation::Abbreviation(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Abbreviation),
    dialogUi(new Ui::Dialog)
{
    ui->setupUi(this);

    dialogObj = new QDialog;
    dialogUi->setupUi(dialogObj);

    setUi();
    init();


    //主窗口菜单功能
    connect(ui->action_add_button, &QAction::triggered, this, &Abbreviation::slot_addButtonTest);
    connect(ui->action_test, &QAction::triggered, this, &Abbreviation::slot_test);
    connect(ui->action_text_show, &QAction::triggered, this, &Abbreviation::slot_textShow);
    connect(ui->action_set_content, &QAction::triggered, this, &Abbreviation::slot_dirSet);
    connect(ui->action_scan, &QAction::triggered, this, &Abbreviation::slot_scan);    //扫描
    connect(ui->action_fileProTest, &QAction::triggered, this, &Abbreviation::slot_fileProTest);
    connect(ui->action_helpUse, &QAction::triggered, this, &Abbreviation::slot_helpUse);    //使用帮助
    connect(ui->action_fontAdd, &QAction::triggered, [this](){ slot_fontChange(1);});   //字体变化，变大
    connect(ui->action_fontDec, &QAction::triggered, [this](){ slot_fontChange(2);});   //字体变化，变小

    //主窗口控件
    connect(ui->lineEdit_search, &QLineEdit::textEdited, this, &Abbreviation::slot_search);    //搜索框
    connect(ui->pushButton_try, &QPushButton::clicked, this, &Abbreviation::slot_try);    //try按钮
    //目录设置对话框
    connect(dialogUi->pushButton_fileBrowse, &QPushButton::clicked, this, &Abbreviation::slot_fileBrowse);
    connect(dialogUi->buttonBox, &QDialogButtonBox::accepted, this, &Abbreviation::slot_dialogAccept);
    connect(dialogUi->buttonBox, &QDialogButtonBox::rejected, this, &Abbreviation::slot_dialogReject);
    connect(dialogUi->pushButton_apply, &QPushButton::clicked, this, &Abbreviation::slot_dialogApply);


}

//析构函数
Abbreviation::~Abbreviation()
{
    delete ui;

    delete dialogObj;

    //清空
    for(auto probe = pushButtonVector.begin(); probe != pushButtonVector.end();)
    {
        QPushButton *button = *probe;
        ui->verticalLayout_abbreButton->removeWidget(button);
        delete button;
        probe = pushButtonVector.erase(probe);
    }

}

//UI的更多设计
void Abbreviation::setUi()
{
    setWindowTitle(QStringLiteral("缩写查询"));

}

//初始化设置
void Abbreviation::init()
{
    qDebug()<<"===================init start=======================";
    init_dir(); //目录初始化
    filePro(false); //扫描文件

    //属性值设置，注意，上面的 init_dir 已经包含了 配置文件的载入
    //例子："font: 12pt '楷体';"
    QString fontValue;
    QString sheet;
    if(getConfigValue(QString(PROPERTY_FONTSIZE), &fontValue))
    {
        int size = fontValue.toInt();
        if(size > 0 && size< 100)  //确保数字的范围
        {
            sheet = QString("font: %1pt '楷体';").arg(size);
            ui->textBrowser_main->setStyleSheet(sheet);
        }
    }

    //显示所有搜索结果
    searchResult.clear();
    for(const auto &elem : abbreviationData)
        searchResult.push_back(elem);
    searchResultShow();
}



/*=========================================================================================
                                       1、窗口菜单栏
=========================================================================================*/
//测试（菜单栏）：按钮新增
void Abbreviation::slot_addButtonTest()
{
    /*static int cnt = 1;
    for(int i = 0; i < 5; i++)
    {
        QPushButton *pushButton = new QPushButton(ui->centralWidget);
        pushButton->setText(QString("新增%1,count=%2").arg(cnt++).arg(ui->verticalLayout_abbreButton->count())); //QStringLiteral
        ui->verticalLayout_abbreButton->insertWidget(ui->verticalLayout_abbreButton->count() - 1, pushButton);
        pushButtonVector.push_back(pushButton);
    }*/
}

//测试（菜单栏）：文本显示
void Abbreviation::slot_textShow()
{
    qDebug() << "slot_textShow start";
    //文本显示
    //ui->textBrowser_main->setText("hello world!");

    //用户目录
    //QString userPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation); //用户目录
    //qDebug() << userDocumentsDir;

    //创建目录
    /*QString path = QString("%1/%2").arg(userPath).arg(SUB_DIR_PATH);
    QDir dir;
    qDebug() << "path1:" << path;
    dir.cd(path);
    //dir.cd(QString("C:/Users"));
    qDebug() << "path2:" << dir.absolutePath();
    QString dirName = "t";
    if(! dir.exists(dirName))
    {
        qDebug() << "mkdir ...";
        qDebug() << dir.absolutePath();
        //dir.mkdir(dirName);
    }*/
}

//扫描
void Abbreviation::slot_scan()
{
    filePro(true); //扫描文件


}

//使用帮助
/*
1、设置目录
    1.1 属性配置文件，一般在用户目录文件夹，例如 C:/user
        /username，子目录为.share/abbreviation，文件名
        .config，内容为HomeDir=F:/test，修改F:/test即
        可；
    1.2 菜单栏
2、放置数据文件
    2.1 如果设置的目录为"F:/test"，那么在该目录下新建文
        件夹data，把数据文件放在此文件夹下；
    2.2 应用打开时会自动扫描data文件夹下的所有文件，包括
        子目录。
3、数据文件内容
    3.1	一条数据项有四个内容，即缩写、解释、来自的文档
        名、数据文档名；
    3.1 例子【AES Advanced Encryption Standard】：一般一
        行代表一条数据，这里AES是缩写，后面的是解释；
    3.2 特殊的缩写DOCUMENT，例如【DOCUMENT T-REC-G.984.
        4.pdf】，用于指定后面的数据项来自于文档《T-REC-
        G.984.4.pdf》。
*/
void Abbreviation::slot_helpUse()
{
    QString str(
    "1. 设置目录:\r\n"
    "   1.1 属性配置文件，一般在用户目录文件夹，例如 \"C:/user/username\"，子目录为 \".share/abbreviation\"，文件名为 \".config\"，内容为 HomeDir=F:/test，修改 F:/test 即可；\r\n"
    "   1.2 菜单栏配置\r\n"
    "\r\n"
    "2. 放置数据文件:\r\n"
    "   2.1 如果设置的目录为 \"F:/test\"，那么在该目录下新建文件夹 data，把数据文件放在此文件夹下；\r\n"
    "   2.2 应用打开时会自动扫描 data 文件夹下的所有文件，包括子目录。\r\n"
    "\r\n"
    "3. 数据文件内容:\r\n"
    "   3.1 一条数据项有四个内容，即缩写、解释、来自的文档名、数据文档名；\r\n"
    "   3.2 例子【AES Advanced Encryption Standard】：一般一行代表一条数据，这里 AES 是缩写，后面的是解释；\r\n"
    "   3.3 特殊的缩写 DOCUMENT，例如【DOCUMENT T-REC-G.984.4.pdf】，用于指定后面的数据项来自于文档《T-REC-G.984.4.pdf》。"
        );
    ui->textBrowser_main->setText(str);
}

//菜单栏功能：字体变化 1：变大 2：变小
//参考：font: 16pt "楷体";
void Abbreviation::slot_fontChange(int n)
{
    qDebug() << "slot_fontChange n=" << n;
    if(n != 1 && n != 2)return;
    QString fontValue;
    QString sheet;
    if(configDataIsOk && getConfigValue(QString(PROPERTY_FONTSIZE), &fontValue))
    {
        int size = fontValue.toInt();
        if(size > 0 && size< 100)  //确保数字的范围
        {
            if(n == 1)
                size++;
            else if(n == 2)
                size--;
            sheet = QString("font: %1pt '楷体';").arg(size);
            ui->textBrowser_main->setStyleSheet(sheet);
            //存入配置文件
            setConfigValue(QString(PROPERTY_FONTSIZE), QString("%1").arg(size));
            if(configFIleIsExist)configFileSave(configFIleName);
        }
    }
}



/*=========================================================================================
                                       2、目录相关的对话框
=========================================================================================*/

//目录（菜单栏）：设置目录
void Abbreviation::slot_dirSet()
{


    //ui->textBrowser_main->setText("dir set");
    dialogUi->label_currentDirValue->setText(current_dir_path);
    dialogUi->label_result->hide();
    dialogUi->lineEdit_dir->setText(QString(""));

    dialogObj->exec();
    //qDebug("slot_dirSet finish");
}

//对话框响应：浏览文件
void Abbreviation::slot_fileBrowse()
{
    //qDebug("slot_fileBrowse !");
    //QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),"/home",
    //                                                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), current_dir_path,
                                                    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (!dir.isEmpty())   //检查用户是否选择了目录
    {
       // 显示选择的文件路径
       qDebug() << dir;
       dialogUi->lineEdit_dir->setText(dir);

    }
}

//响应：对话框确认
void Abbreviation::slot_dialogAccept()
{
    qDebug()<<"slot_dialogAccept";

    slot_dialogApply();
    dialogObj->accept();
}

//响应：对话框取消
void Abbreviation::slot_dialogReject()
{
    qDebug()<<"slot_dialogAccept";


    dialogObj->reject();
}

//响应：对话框中的应用按键
void Abbreviation::slot_dialogApply()
{
    qDebug()<<"slot_dialogApply";

    QString dirValue = dialogUi->lineEdit_dir->text();
    QDir dir(dirValue);
    if(dirValue.isEmpty() || !dir.exists())
    {
        dialogUi->label_result->setText("目录不存在或者为空！");
        dialogUi->label_result->show();
    }
    else
    {
        if(configDataIsOk && setConfigValue(PROPERTY_NAME_HOME_DIR, dirValue))
        {
            dialogUi->label_result->setText("设置成功");

            current_dir_path = dirValue;

            dialogUi->label_currentDirValue->setText(dirValue);

            if(configFIleIsExist)
            {
                configFileSave(configFIleName);
            }
        }
        else
        {
            dialogUi->label_result->setText("设置失败");
        }

        dialogUi->label_result->show();
    }

}



/*=========================================================================================
                                       3、路径和配置文件
=========================================================================================*/
//初始化
void Abbreviation::init_dir()
{
    //路径
    pathIsExist = false;

    QDir dirProbe;

    //默认用户路径
    QString path = QStandardPaths::writableLocation(QStandardPaths::HomeLocation); //默认用户路径
    if(!dirProbe.cd(path))
    {
        qDebug() << "无法进入默认用户路径 " << path;
    }
    else
    {
        qDebug() << "默认用户路径：" << path;
        //默认应用路径
        current_dir_path = QString("%1/%2").arg(path).arg(SUB_DIR_PATH); //应用路径
        if(!dirProbe.cd(current_dir_path))
        {
            qDebug() << "无法进入默认应用路径： " << current_dir_path << " 将创建...";


            if(dirProbe.mkpath(current_dir_path))
            {
                qDebug() << "创建成功";
                pathIsExist = true;
            }
            else
            {
                qDebug() << "创建失败";
            }
        }
        else
        {
            qDebug() << "默认应用路径：" << current_dir_path;
            pathIsExist = true;
        }
    }

    //用户


    //配置文件
    configFIleIsExist = false;
    QString file_path;
    if(pathIsExist == true)
    {
        file_path = QString("%1/%2").arg(current_dir_path).arg(CONFIG_FILE);
        qDebug() << "配置文件:" << file_path;
        configFIleName = file_path;
        QFile file(file_path);
        if(file.exists())
        {
            qDebug() << file_path << " 文件存在";
            configFIleIsExist = true;
        }
        else
        {
            qDebug() << file_path << " 文件不存在，将创建";

            if(file.open( QIODevice::WriteOnly))
            {
                qDebug() << file_path << " 文件创建成功";
                configFIleIsExist = true;
                file.close();
            }
            else
            {
                qDebug() << file_path << " 文件打创建失败";
            }
        }



    }

    //写入测试
#if 0
    if(configFIleIsExist)
    {
         QFile file(file_path);
        if(file.exists() && file.open( QIODevice::Append))
        {
            qDebug() << "写入测试内容 ...";
            QString msg = "test ok\r\n";
            file.write((const char *)msg.toStdString().c_str(), qstrlen(msg.toStdString().c_str()));
            file.close();
        }
    }
#endif

    //配置文件的载入
    if(configFIleIsExist)
    {
        configDataIsOk = configFileLoad(file_path);

        qDebug() << "----------------configData------------------";
        // 使用迭代器访问所有元素
        for (auto it = configData.begin(); it != configData.end(); ++it) {
            qDebug() << "属性：" << it->property << " 数值：" << it->value ;
        }

    }

    //获取设置的主目录值
    QString value;
    if(configFIleIsExist)
    {
        if(getConfigValue(QString(PROPERTY_NAME_HOME_DIR), &value))
        {
            //qDebug() << "设置的主目录值" << value;

            if(!dirProbe.cd(value))
            {
                qDebug() << "无法进入配置的主目录 " << value;
            }
            else
            {
                    qDebug() << "配置的应用目录" << value;
                    current_dir_path = value;
            }
        }
    }
}
//配置文件载入
bool Abbreviation::configFileLoad(QString configFileName)
{
    //qDebug() << "==================getConfigValue start==================";

    #define LINE_MAX_BYTE 256
    bool ret = false;
    char line[LINE_MAX_BYTE];
    QString lineQstr;
    qint64 len;
    QFile file(configFileName);
    //QStringList parts;
    struct_configData data;

    if(file.exists())
    {
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            ret = true;


            while(1)
            {
                len = file.readLine(line, LINE_MAX_BYTE);
                if(len == -1) //读到结尾一般返回 -1
                    break;
                //qDebug() << "[" << line << "]";
                lineQstr = QString(line);
                if(lineQstr.at(lineQstr.length() - 1) == QChar('\n'))
                {
                    lineQstr.remove(lineQstr.length() - 1, 1);
                }

                //解析出属性值
                QStringList parts = lineQstr.split('=');
                if(parts.size() == 2)
                {
                    //qDebug() << "[解析出属性值]";
                    //qDebug() << parts[0] << ":" << parts[1];
                    data.property = parts[0];
                    data.value = parts[1];
                    configData.push_back(data);
                }
            }

        }

    }

    return ret;
}

//属性存入配置文件
bool Abbreviation::configFileSave(QString configFileName)
{
    bool ret = false;
    QFile file(configFileName);
    QString tmpStr;
    if(configDataIsOk && file.exists())
    {
        if(file.open(QIODevice::WriteOnly))
        {
            ret = true;
            for(auto it = configData.begin(); it != configData.end(); ++it)
            {
                tmpStr = QString("%1=%2\r\n").arg(it->property).arg(it->value);

                file.write(tmpStr.toUtf8());
            }
        }
    }
    return ret;
}

/*配置属性值的获取
    格式一般是 property=value
    提供的属性有:
        HomeDir：主目录，用于存放配置文件；参考默认值 C:\Users\along\.share\abbreviation
*/

bool Abbreviation::getConfigValue(QString propertyName, QString *value)
{
    //qDebug() << "==================getConfigValues start==================";
    bool ret = false;
    if(configDataIsOk)
    {
        for (auto it = configData.begin(); it != configData.end(); ++it) {
            if(it->property == propertyName)
            {
                ret = true;
                *value = it->value;
            }
        }
    }

    return ret;
}

//配置属性值的设置
bool Abbreviation::setConfigValue(QString propertyName, QString value)
{
    bool ret = false;
    if(configDataIsOk)
    {
        for (auto it = configData.begin(); it != configData.end(); ++it) {
            if(it->property == propertyName)
            {
                ret = true;
                it->value = value;
            }
        }
    }

    return ret;
}


/*=========================================================================================
                                       4、缩写解释的文件处理
=========================================================================================*/
//测试入口
void Abbreviation::slot_fileProTest()
{
    qDebug() << "=====================slot_fileProTest start=====================";

    //qDebug() << current_dir_path << "-------------文件------------";
    //qDebug() << "主目录" << current_dir_path;

    //filePro(true);

}

//扫描文件和处理（打开应用时会调用一次）
void Abbreviation::filePro(bool showIsOpen)
{
    vector_fileName.clear();
    QString path = QString("%1/%2").arg(current_dir_path).arg(DATA_DIR);
    dirFindAllFile(path);

    //qDebug() << "-------------文件处理------------";
    abbreviationData.clear();   //清空存储区
    QString str("扫描中...\r\n");
    for(const auto &elem : vector_fileName)
    {
        //qDebug() << "文件" << elem;
        str.append(elem);
        str.append("\r\n");
        abbreFilePro(elem);
    }
    str.append("扫描完成");
    if(showIsOpen)ui->textBrowser_main->setText(str);

    //排序
    std::sort(abbreviationData.begin(), abbreviationData.end(), [](const  struct AbbreviationData &a, const  struct AbbreviationData &b) {
        return a.abbre.toLower() < b.abbre.toLower();
    });

    /*qDebug() << "-------------内容显示------------";
    for(const auto &elem : abbreviationData)
    {
        qDebug() << "缩写：" << elem.abbre <<
                    " 描述：" << elem.describe <<
                    " 文档：" << elem.doc <<
                    " 来自：" << elem.from;
    }*/

}



//目录下找到所有的文件
void Abbreviation::dirFindAllFile(QString dirName)
{

    QFileInfoList fileInfoList;
    QDir dir(dirName);
    if(dir.exists())
    {
        fileInfoList = dir.entryInfoList();
        for (const QFileInfo &fileInfo : fileInfoList)
        {
            if (fileInfo.isFile())
            {
                vector_fileName.push_back(QString(fileInfo.absoluteFilePath().toStdString().c_str()));
                //qDebug()<< fileInfo.absoluteFilePath().toStdString().c_str() ;
            }
            else if(fileInfo.isDir() && fileInfo.fileName() != QString(".")
                    && fileInfo.fileName() != QString(".."))
            {
                dirFindAllFile(fileInfo.filePath());
            }
        }
    }
}

//单个文件的处理
void Abbreviation::abbreFilePro(QString fileName)
{
#define READ_BUF_LEN 2048
    char buf[READ_BUF_LEN] = {0};
    QFile file(fileName);
    int len;
    if(file.exists() && file.open(QIODevice::ReadOnly))
    {
        currentReferDocument = "empty";
        while(1)
        {
            len = file.readLine(buf, READ_BUF_LEN);
            if(len == -1) //读到结尾一般返回 -1
                break;
            abbreEntryPro(fileName, buf);
            //qDebug() << buf;
        }
    }
}

//单条数据的处理
void Abbreviation::abbreEntryPro(QString fileName, QString entry)
{
    #define BUF_SIZE 2048

    enum enum_step{
        step_start,
        step_abbreviation,
        step_middle,
        step_describe,
        //step_end,
        step_faild
    };

    char buf[BUF_SIZE] = {0};
    char bufAbbre[ABBREVIATION_MAX_SIZE + 1] = {0};   //存储字母缩写
    char bufDescribe[BUF_SIZE] = {0};   //存储缩写字母的描述（长度有限制）
    struct AbbreviationData abbreData;


    strncpy(buf, entry.toStdString().c_str(), BUF_SIZE);
    int i, len, step;
    int bufAbbre_cnt, bufDescribe_cnt;
    len = strlen(buf);
    step = step_start;

    bufAbbre_cnt = 0;
    bufDescribe_cnt = 0;

    //状态机
    for(i = 0; i < len && i < BUF_SIZE; i++)
    {
        if(buf[i] == '\r')goto mark_step_end;   //换行
        switch(step)
        {
            case step_start:{
                if(buf[i] != ' ')
                {
                    bufAbbre[bufAbbre_cnt++] = buf[i];
                    step = step_abbreviation;
                }
            }break;
            case step_abbreviation:{
                if(buf[i] == ' ')
                {
                    if(bufAbbre_cnt >= ABBREVIATION_MAX_SIZE)     //越界
                        step = step_faild;
                    else
                    {
                        bufAbbre[bufAbbre_cnt++] = '\0';
                        step = step_middle;
                    }

                }
                else
                {
                    if(bufAbbre_cnt >= ABBREVIATION_MAX_SIZE - 1)     //缩写的字母个数越界
                        step = step_faild;
                    else
                        bufAbbre[bufAbbre_cnt++] = buf[i];
                }
            }break;
            case step_middle:{
                if(buf[i] != ' ')
                {
                    bufDescribe[bufDescribe_cnt++] = buf[i];
                    step = step_describe;
                }
            }break;
            case step_describe:{
                    bufDescribe[bufDescribe_cnt++] = buf[i];
            }break;
            case step_faild:{
                goto mark_step_end; //跳出循环
            }break;
        }
    }
mark_step_end:

    if(step == step_describe)
    {
        if(QString(bufAbbre) == QString(ABBREVIATION_DOCUMENT))   //特殊的项，DOCUMENT开头，表示当前文档名
        {
            currentReferDocument = bufDescribe;
        }
        else
        {
            abbreData.abbre = QString(bufAbbre);
            abbreData.describe = QString(bufDescribe);
            abbreData.doc = currentReferDocument;
            abbreData.from = fileName;
            abbreviationData.push_back(abbreData);
        }

        //qDebug() << "缩写：" << bufAbbre << "  描述：" << bufDescribe;

    }
}

/*=========================================================================================
                                       4、搜索显示
=========================================================================================*/

//槽响应：测试
void Abbreviation::slot_test()
{
    qDebug() << "slot_test";

    //QFont font("楷体", 14);
    //ui->textBrowser_main->setFont(font);
    //ui->textBrowser_main->setStyleSheet("font: 12pt '楷体';");

#if 0
    static int cnt = 1;
    QPushButton *pushButton = new QPushButton(ui->centralWidget);
    pushButton->setText(QString("按钮%1").arg(cnt));
    ui->verticalLayout_abbreButton->insertWidget(ui->verticalLayout_abbreButton->count() - 1, pushButton);
    pushButtonStackVector.push_back(pushButton);

    connect(pushButton, &QPushButton::clicked, [this](){slot_abbreButtonOnClicked(cnt);} );
    cnt++;
#endif

    //searchFilter(QString(ui->lineEdit_search->text()));

#if 0
    searchFilter(QString(ui->lineEdit_search->text()));
    QPushButton *pushButton;
    int index = 0;
    //清空
    for(auto probe = pushButtonVector.begin(); probe != pushButtonVector.end();)
    {
        QPushButton *button = *probe;
        ui->verticalLayout_abbreButton->removeWidget(button);
        delete button;
        probe = pushButtonVector.erase(probe);
    }

    //搜索结果显示
    qDebug() <<"---------------搜索结果--------------";
    index = 0;
    for(const auto &elem : searchResult)
    {
        pushButton = new QPushButton;
        pushButton->setText(elem.abbre);
        ui->verticalLayout_abbreButton->insertWidget(ui->verticalLayout_abbreButton->count() - 1, pushButton);
        pushButtonVector.push_back(pushButton);

        connect(pushButton, &QPushButton::clicked, [this, index](){slot_abbreButtonOnClicked(index);} );

        qDebug() << "缩写：" << elem.abbre << " index：" << index;
        index++;
    }
#endif

#if 0
    QString htmlContent =
            "<!DOCTYPE html>\n"
            "<style>\n"
            "p1 {\n"
            "  font-size: 60px;\n"
            "  color: #f0f;\n"
            "}\n"
            "p2 {\n"
            "    font-size: 30px;\n"
            "    /* background-color: red; */\n"
            "    color: black;\n"
            "}\n"
            "p3 {\n"
            "  font-size: 16px;\n"
            "  color: blue;\n"
            "}\n"
            "</style>\n"
            "<body>\n"
            "  <p1><b>ACE</b></p1><br><br>\n"
            "  <p2>Circuit Emulation Service </p2><br><br>\n"
            "  <p3><i>disnet-conflict-study.pdf</i></p3><br>\n"
            "  <p3><i>disnet-conflict-study.pdf</i></p3>\n"
            "</body>\n"
            "</html>";
    ui->textBrowser_main->setHtml(htmlContent);
#endif
}

//按钮响应
void Abbreviation::slot_abbreButtonOnClicked(int num)
{
    qDebug() << "按钮"<< searchResult[num].abbre <<" 按钮编号" << num;

    QString str;

    struct AbbreviationData result = *(searchResult.begin() + num);


    /*str.append("缩写：");
    str.append(result.abbre);
    str.append("\r\n");
    str.append("描述：");
    str.append(result.describe);
    str.append("\r\n");
    str.append("文档：");
    str.append(result.doc);
    str.append("\r\n");
    str.append("来自：");
    str.append(result.from);
    ui->textBrowser_main->setText(str);*/

    QString htmlContent = QString(
            "<!DOCTYPE html>\n"
            "<style>\n"
            "p1 {\n"
            "  font-size: 60px;\n"
            "  color: #f0f;\n"
            "}\n"
            "p2 {\n"
            "    font-size: 30px;\n"
            "    /* background-color: red; */\n"
            "    color: black;\n"
            "}\n"
            "p3 {\n"
            "  font-size: 16px;\n"
            "  color: blue;\n"
            "}\n"
            "</style>\n"
            "<body>\n"
            "  <p1><b>%1</b></p1><br><br>\n"
            "  <p2>%2</p2><br><br>\n"
            "  <p3><i>%3</i></p3><br>\n"
            "  <p3><i>%4</i></p3>\n"
            "</body>\n"
            "</html>"
                ).arg(result.abbre).arg(result.describe).arg(result.doc).arg(result.from);

    ui->textBrowser_main->setHtml(htmlContent);
}


//槽响应：搜索框
void Abbreviation::slot_search()
{
    qDebug() << "slot_search ...";

    searchFilter(QString(ui->lineEdit_search->text()));

    searchResultShow();
}

//搜索筛选
void Abbreviation::searchFilter(QString key)
{
    searchResult.clear();

    QString str;
    for(const auto &elem : abbreviationData)
    {
        str = elem.abbre;
        str.remove(key.length(), str.length()-key.length());
        if(key.toLower() == str.toLower())
        {
            searchResult.push_back(elem) ;
        }
        //qDebug() << "key:" << key << "  str:" << str;
    }

    //排序
    //std::sort(searchResult.begin(), searchResult.end(), [](const  struct AbbreviationData &a, const  struct AbbreviationData &b) {
    //    return a.abbre.toLower() < b.abbre.toLower();
    //});

    /*qDebug() << "-------------内容显示------------";
    for(const auto &elem : searchResult)
    {
        qDebug() << "缩写：" << elem.abbre <<
                    " 描述：" << elem.describe <<
                    " 文档：" << elem.doc <<
                    " 来自：" << elem.from;
    }*/
}


//显示搜索结果
void Abbreviation::searchResultShow()
{
    QPushButton *pushButton;
    int index;
    //清空
    for(auto probe = pushButtonVector.begin(); probe != pushButtonVector.end();)
    {
        QPushButton *button = *probe;
        ui->verticalLayout_abbreButton->removeWidget(button);
        delete button;
        probe = pushButtonVector.erase(probe);
    }

    //搜索结果显示
    //qDebug() <<"---------------搜索结果--------------";
    index = 0;
    QString str = ui->lineEdit_search->text();
    for(const auto &elem : searchResult)
    {
        pushButton = new QPushButton;
        pushButton->setText(elem.abbre);

        //完全匹配的额外操作
        if(str.toLower() == elem.abbre.toLower() && str != QString(""))
        {
            pushButton->setStyleSheet("background-color: red;");
            slot_abbreButtonOnClicked(index);
        }
        ui->verticalLayout_abbreButton->insertWidget(ui->verticalLayout_abbreButton->count() - 1, pushButton);
        pushButtonVector.push_back(pushButton);

        connect(pushButton, &QPushButton::clicked, [this, index](){slot_abbreButtonOnClicked(index);} );

        //qDebug() << "缩写：" << elem.abbre << " index：" << index;
        index++;
    }
}

//槽响应：try按钮
void Abbreviation::slot_try()
{
    if(ui->lineEdit_search->text() != QString("") || pushButtonVector.size() != 0)
    {
        searchResult.clear();
        searchResultShow();
        ui->lineEdit_search->setText(QString(""));
        ui->textBrowser_main->setText(QString(""));
    }
    else
    {
        searchResult.clear();
        for(const auto &elem : abbreviationData)
        {
            searchResult.push_back(elem);
        }
        searchResultShow();
    }


}






