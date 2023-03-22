#include "ui_shutdown.h"
#include "shutdown.h"
#include <QDebug>
#include <QProcess>
#include <QPropertyAnimation>

QString timeUnitSecond = "秒/s";
QString timeUnitMinute = "分/m";
QString timeUnitHour = "小时/h";
QString taskName = "自动关机";

shutdown::shutdown(QWidget* parent):
    QWidget(parent),
    ui(new Ui::shutdown) {
    ui->setupUi(this);

    this->setWindowTitle(taskName);

    button_height = 30;
    bottomMargin = 30;
    leftMargin = 30;

    this->interfaceInitialization();
    this->singnalDetect();
}

shutdown::~shutdown() {
    delete ui;
}

// 重写窗口大小变化事件
void shutdown::resizeEvent(QResizeEvent* event) {
    Q_UNUSED(event);
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

    if (ui->radioButton_timeIntelval->isChecked()) {    // 如果倒计时选项被选中
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
    } else if (ui->radioButton_timePoint->isChecked()) {    // 如果时间点选项被选中
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
    // 界面可扩展
//    ui->verticalLayout->stretch(1);

    // 固定底部按钮高度
    ui->pushButton_confirm->setFixedHeight(button_height);
    ui->pushButton_cancel->setFixedHeight(button_height);
    ui->pushButton_exit->setFixedHeight(button_height);

    // 固定两个时间输入组的组件高度
    ui->radioButton_timeIntelval->setFixedHeight(button_height);
    ui->radioButton_timePoint->setFixedHeight(button_height);
    ui->comboBox_timeUnit->setFixedHeight(button_height);
    ui->doubleSpinBox_timeNum->setFixedHeight(button_height);
    ui->label_timeUnit->setFixedHeight(button_height);
    ui->label_timeNum->setFixedHeight(button_height);
    ui->timeEdit->setFixedHeight(button_height);

    //固定窗口大小
    this->resize(ui->pushButton_exit->pos().x() + ui->pushButton_exit->width(),
        ui->pushButton_exit->pos().x() + ui->pushButton_exit->height());
    this->setMaximumWidth(ui->pushButton_exit->pos().x() + ui->pushButton_exit->width());
    this->setMaximumHeight(ui->pushButton_exit->pos().x() + ui->pushButton_exit->height());

    // 设置时间单位选择
    QList timeUnitList = { timeUnitSecond, timeUnitMinute, timeUnitHour };
    ui->comboBox_timeUnit->addItems(timeUnitList);

    // 设置时间点输入框最小值
    QDateTime currentDateTime = QDateTime::currentDateTime();
    ui->dateEdit->setMinimumDate(currentDateTime.date());
    ui->timeEdit->setMinimumTime(currentDateTime.time());

    // 设置信息展示窗口默认信息
    this->informationDisplay("点击查询计划按钮查询当前自动关机计划\n"
                             "点击查询计划时显示\"错误: 系统找不到指定的文件。\"表示无计划，"
                             "取消计划时显示则表示无计划可以取消", true);

    // 设置输入窗口初始为不可输入, 只有当前面的单选按钮选中之后才能输入
    ui->comboBox_timeUnit->setEnabled(false);
    ui->doubleSpinBox_timeNum->setEnabled(false);
    ui->dateEdit->setEnabled(false);
    ui->timeEdit->setEnabled(false);
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
    // 激活输入组, 只有当前面的单选框被选中才能输入数据
    connect(ui->radioButton_timeIntelval, &QRadioButton::toggled, [&](){
        ui->comboBox_timeUnit->setEnabled(true);
        ui->doubleSpinBox_timeNum->setEnabled(true);

        if (!ui->radioButton_timeIntelval->isChecked()) {
            ui->comboBox_timeUnit->setEnabled(false);
            ui->doubleSpinBox_timeNum->setEnabled(false);
        }
    });
    connect(ui->radioButton_timePoint, &QRadioButton::toggled, [&](){
        // 输入组激活时设置当前时间为最小值
        QDateTime currentDateTime = QDateTime::currentDateTime();
        ui->dateEdit->setMinimumDate(currentDateTime.date());
        ui->timeEdit->setMinimumTime(currentDateTime.time());

        ui->timeEdit->setEnabled(true);
        ui->dateEdit->setEnabled(true);

        if (!ui->radioButton_timePoint->isChecked()) {
            ui->timeEdit->setEnabled(false);
            ui->dateEdit->setEnabled(false);
        }
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
