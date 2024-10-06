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

    //连接
    connect(ui->action_add_button, &QAction::triggered, this, &Abbreviation::slot_addButtonTest);
    connect(ui->action_test, &QAction::triggered, this, &Abbreviation::slot_test);
    connect(ui->action_text_show, &QAction::triggered, this, &Abbreviation::slot_textShow);
    connect(ui->action_set_content, &QAction::triggered, this, &Abbreviation::slot_dirSet);
    connect(dialogUi->pushButton_fileBrowse, &QPushButton::clicked, this, &Abbreviation::slot_fileBrowse);

    connect(dialogUi->buttonBox, &QDialogButtonBox::accepted, this, &Abbreviation::slot_dialogAccept);
    connect(dialogUi->buttonBox, &QDialogButtonBox::rejected, this, &Abbreviation::slot_dialogReject);
    connect(dialogUi->pushButton_apply, &QPushButton::clicked, this, &Abbreviation::slot_dialogApply);

    connect(ui->action_fileProTest, &QAction::triggered, this, &Abbreviation::slot_fileProTest);

    connect(ui->lineEdit_search, &QLineEdit::textEdited, this, &Abbreviation::slot_search);    //搜索框


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
    init_dir();


}









/*=========================================================================================
                                       1、窗口菜单栏
=========================================================================================*/
//测试（菜单栏）：按钮新增
void Abbreviation::slot_addButtonTest()
{
    static int cnt = 1;
    for(int i = 0; i < 5; i++)
    {
        QPushButton *pushButton = new QPushButton(ui->centralWidget);
        pushButton->setText(QString("新增%1,count=%2").arg(cnt++).arg(ui->verticalLayout_abbreButton->count())); //QStringLiteral
        ui->verticalLayout_abbreButton->insertWidget(ui->verticalLayout_abbreButton->count() - 1, pushButton);
        pushButtonVector.push_back(pushButton);
    }
}

//测试（菜单栏）：文本显示
void Abbreviation::slot_textShow()
{
    qDebug() << "slot_textShow start";
    //文本显示
    //ui->textBrowser_main->setText("hello world!");

    //用户目录
    QString userPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation); //用户目录
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
        if(configDataIsOk && getConfigValue(PROPERTY_NAME_HOME_DIR, dirValue))
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
bool Abbreviation::getConfigValue(QString propertyName, QString value)
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
    vector_fileName.clear();
    dirFindAllFile(current_dir_path);


    qDebug() << "-------------文件处理------------";

    for(const auto &elem : vector_fileName)
    {
        qDebug() << "文件" << elem;
        abbreFilePro(elem);
    }



    std::sort(abbreviationData.begin(), abbreviationData.end(), [](const  struct AbbreviationData &a, const  struct AbbreviationData &b) {
        return a.abbre.toLower() < b.abbre.toLower();
    });

    qDebug() << "-------------内容显示------------";
    for(const auto &elem : abbreviationData)
    {
        qDebug() << "缩写：" << elem.abbre <<
                    " 描述：" << elem.describe <<
                    " 文档：" << elem.doc <<
                    " 来自：" << elem.from;
    }

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
        if(QString(bufAbbre) == QString(PROPERTY_DOCUMENT))   //特殊的项，DOCUMENT开头，表示当前文档名
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
    //qDebug() << "slot_test";

#if 0
    static int cnt = 1;
    QPushButton *pushButton = new QPushButton(ui->centralWidget);
    pushButton->setText(QString("按钮%1").arg(cnt));
    ui->verticalLayout_abbreButton->insertWidget(ui->verticalLayout_abbreButton->count() - 1, pushButton);
    pushButtonStackVector.push_back(pushButton);

    connect(pushButton, &QPushButton::clicked, [this](){slot_abbreButtonOnClicked(cnt);} );
    cnt++;
#endif

    searchFilter(QString(ui->lineEdit_search->text()));

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



}

//按钮响应
void Abbreviation::slot_abbreButtonOnClicked(int num)
{
    qDebug() << "按钮"<< searchResult[num].abbre <<" 按钮编号" << num;

    QString str;

    struct AbbreviationData result = *(searchResult.begin() + num);
    str.append("缩写：");
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

    ui->textBrowser_main->setText(str);
}


//槽响应：搜索框
void Abbreviation::slot_search()
{
    qDebug() << "slot_search ...";

    searchFilter(QString(ui->lineEdit_search->text()));
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








