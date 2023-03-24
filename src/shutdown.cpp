#include "ui_shutdown.h"
#include "shutdown.h"
#include <QDebug>
#include <QProcess>
#include <QFont>

QString timeUnitSecond = "秒/s";
QString timeUnitMinute = "分/m";
QString timeUnitHour = "小时/h";
QString taskName = "自动关机 winAutoShutdown By CodingRookie";

shutdown::shutdown(QWidget* parent):
    QWidget(parent),
    ui(new Ui::shutdown) {
    ui->setupUi(this);

    this->setWindowTitle(taskName);
    qDebug() << "test output";

    this->interfaceInitialization();
    this->singnalDetect();
}

shutdown::~shutdown() {
    delete ui;
}

QString shutdown::excuteCommand(const QString& command){
    QProcess* process = new QProcess(this);
//    QString program = "powershell";
//    process->setProgram(program);
    process->setProcessChannelMode(QProcess::MergedChannels);   //设置读取标准输出模式
    process->start("powershell", QStringList()<< command);

    process->waitForStarted();
    process->waitForFinished();
    QString strTemp=QString::fromLocal8Bit(process->readAllStandardOutput());
//    qDebug() << strTemp;
//    this->informationDisplay(strTemp, false);
    return strTemp;
}

// 当确认按钮被单击时
void shutdown::onButtonConfirmClicked() {
    // 检查系统是否有关机计划

    // 存储关机时间
    QDateTime currentDateTime = QDateTime::currentDateTime();
    unsigned int time = 0;

    if (ui->tabWidget->tabText(ui->tabWidget->currentIndex()) == "倒计时") {    // 如果倒计时选项被选中
        ui->textBrowser->append("倒计时\n");
        if (ui->comboBox_timeUnit->currentText() == timeUnitSecond) {
            time = ui->doubleSpinBox_timeNum->value();
            currentDateTime = currentDateTime.addSecs(time);
        } else if (ui->comboBox_timeUnit->currentText() == timeUnitMinute) {
            time = ui->doubleSpinBox_timeNum->value();
            currentDateTime = currentDateTime.addSecs(time * 60);
        } else if (ui->comboBox_timeUnit->currentText() == timeUnitHour) {
            time = ui->doubleSpinBox_timeNum->value();
            currentDateTime = currentDateTime.addSecs(time * 3600);
        }
    } else if (ui->tabWidget->tabText(ui->tabWidget->currentIndex()) == "时间点") {    // 如果时间点选项被选中
        ui->textBrowser->append("倒计时");
        int year = ui->dateEdit->date().year();
        int month = ui->dateEdit->date().month();
        int day = ui->dateEdit->date().day();
        currentDateTime.date().setDate(year, month, day);
        currentDateTime.setTime(ui->timeEdit->time());
    }

    QString s_longTime = currentDateTime.time().toString();
    QString s_day = QString::number(currentDateTime.date().day());
    QString s_month = QString::number(currentDateTime.date().month());
    QString s_year = QString::number(currentDateTime.date().year());

    if (s_day.toInt() < 10) {
        s_day.insert(0, '0');
    }
    if (s_month.toInt() < 10) {
        s_month.insert(0, '0');
    }

    QString shortDate = s_year + "/" + s_month + "/" + s_day;

//    qDebug().noquote().nospace() << s_longTime << " date is " << s_year << "/" << s_month << "/" << s_day;

    // 利用schtasks创建计划任务
    QString Command = "schtasks /create /tn 自动关机 /tr \"shutdown /s\" /sc once /st " +
            s_longTime + " /sd " + shortDate;
    QString output = this->excuteCommand(Command);
//    qDebug().noquote().nospace() << Command;
    this->informationDisplay(output, false);
    this->informationDisplay(QString("关机计划时间为 ") + shortDate + " " + s_longTime
                                    , false);
}

// 界面初始设置
void shutdown::interfaceInitialization() {

    // 设置时间单位选择
    QList timeUnitList = { timeUnitSecond, timeUnitMinute, timeUnitHour };
    ui->comboBox_timeUnit->addItems(timeUnitList);

    // 设置时间点输入框最小值
    QDateTime currentDateTime = QDateTime::currentDateTime();
    ui->dateEdit->setMinimumDate(currentDateTime.date());
    ui->timeEdit->setMinimumTime(currentDateTime.time());

    // 设置字体大小
    ui->textBrowser->setFontPointSize(13);
    // 设置信息展示窗口默认信息
    this->informationDisplay("点击查询计划按钮查询当前自动关机计划\n"
                             "点击查询计划时显示\"错误: 系统找不到指定的文件。\"表示无计划，"
        "取消计划时显示则表示无计划可以取消", true);

    QFont ft;
    ft.setPointSize(15);
    ui->label->setFont(ft);
    ui->label->setOpenExternalLinks(true);
    ui->label->setText("By [CodingRookie](https://github.com/CodingRookie98)<br/>"
        "[项目地址：https://github.com/CodingRookie98/winAutoShutdown](https://github.com/CodingRookie98/winAutoShutdown)");

    QPalette pal = this->palette();
}

// 信息输出, false表示背景色为红色，true为绿色
void shutdown::informationDisplay(const QString labelMessage, bool color) {
    if (color) {
        ui->textBrowser->setTextColor(Qt::green);
    } else {
        ui->textBrowser->setTextColor(Qt::red);
    }
    ui->textBrowser->append(labelMessage);
}

void shutdown::singnalDetect()
{
    connect(ui->tabWidget->tabBar(), &QTabBar::tabBarClicked, [&]() {
        // 输入组激活时设置当前时间为最小值
        QDateTime currentDateTime = QDateTime::currentDateTime();
        ui->dateEdit->setMinimumDate(currentDateTime.date());
        ui->timeEdit->setMinimumTime(currentDateTime.time());

        ui->comboBox_timeUnit->setEnabled(true);
        ui->doubleSpinBox_timeNum->setEnabled(true);

        ui->timeEdit->setEnabled(true);
        ui->dateEdit->setEnabled(true);
    });

    // 处理确认按钮被单击
    connect(ui->pushButton_confirm, &QPushButton::clicked, [&]() {
        this->onButtonConfirmClicked();
    });

    // 查询计划按钮被单击
    connect(ui->pushButton_searchPlan, &QPushButton::clicked, [&](){
        auto output = this->excuteCommand(QString("schtasks /query /tn 自动关机"));
        this->informationDisplay(output, false);
    });
    // 取消定时关机命令
    connect(ui->pushButton_cancel, &QPushButton::clicked, [&]() {
        auto output = this->excuteCommand(QString("schtasks /delete /tn 自动关机 /f"));
        this->informationDisplay(output, false);
    });

    // 退出窗口
    connect(ui->pushButton_exit, &QPushButton::clicked, [&](){
        this->close();
    });
}
