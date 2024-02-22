/**
 ******************************************************************************
 * @file           : optionWidget.cpp
 * @author         : hui
 * @brief          : None
 * @attention      : None
 * @date           : 2024/2/18
 ******************************************************************************
 */

// You may need to build the project (run Qt uic code generator) to get "ui_OptionWidget.h" resolved

#include <QMessageBox>
#include <QDateTime>
#include <QTimeZone>
#include <iostream>
#include <iomanip>
#include "optionWidget.h"
#include "ui_OptionWidget.h"

OptionWidget::OptionWidget(QWidget *parent) :
    QWidget(parent), ui(new Ui::OptionWidget) {
    ui->setupUi(this);
    model           = new QStandardItemModel();
    selectionModel_ = new QItemSelectionModel(model);

    init();
    signalsProcess();
    worker_.startWorking();
}

OptionWidget::~OptionWidget() {
    delete ui;
    for (auto &list : rows) {
        for (auto &item : list) {
            delete item;
        }
    }
    delete selectionModel_;
    delete model;
}

void OptionWidget::init() {
    ui->operationTypes->addItem("关机");
    ui->operationTypes->addItem("重启");
    ui->operationTypes->addItem("注销");

    operationMap["关机"] = std::make_shared<Operation::OperationShutdown>(Operation::OperationShutdown());
    operationMap["重启"] = std::make_shared<Operation::OperationReboot>(Operation::OperationReboot());
    operationMap["注销"] = std::make_shared<Operation::OperationLogOff>(Operation::OperationLogOff());

    ui->timeTypes->addItem("定时", QVariant(TimeType::Timing));
    ui->timeTypes->addItem("倒计时", QVariant(TimeType::Countdown));

    ui->countdownTimeUnitTypes->addItem("s/秒", QVariant(TimeUnitType::Seconds));
    ui->countdownTimeUnitTypes->addItem("m/分", QVariant(TimeUnitType::Minutes));
    ui->countdownTimeUnitTypes->addItem("h/时", QVariant(TimeUnitType::Hours));
    ui->countdownTimeUnitTypes->addItem("d/天", QVariant(TimeUnitType::Days));

    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->countdownTimeUnitTypes->setEnabled(false);
    ui->countdownTime->setEnabled(false);

    model->setHorizontalHeaderLabels(QStringList({"任务类型", "时间类型", "执行时间"}));
    ui->planTableView->setModel(model);
    ui->planTableView->setSelectionModel(selectionModel_);
}

void OptionWidget::signalsProcess() {
    connect(ui->timeTypes, &QComboBox::currentIndexChanged, ui->dateTimeEdit, [&]() {
        switch (ui->timeTypes->currentData().toInt()) {
        case TimeType::Timing:
            ui->dateTimeEdit->setEnabled(true);
            ui->countdownTimeUnitTypes->setEnabled(false);
            ui->countdownTime->setEnabled(false);
            break;
        case TimeType::Countdown:
            ui->dateTimeEdit->setEnabled(false);
            ui->countdownTimeUnitTypes->setEnabled(true);
            ui->countdownTime->setEnabled(true);
            break;
        }
    });

    connect(ui->btnAddTask, &QPushButton::clicked, this, &OptionWidget::on_btnAddTask_clicked);
    connect(ui->btnDeleteTask, &QPushButton::clicked, this, &OptionWidget::on_btnDeleteTask_clicked);
}

void OptionWidget::on_btnAddTask_clicked() {
    QList<QStandardItem *> rowItems;
    auto *item = new QStandardItem(ui->operationTypes->currentText());
    rowItems.emplace_back(item);

    item = new QStandardItem(ui->timeTypes->currentText());
    rowItems.emplace_back(item);

    QDateTime dateTime = QDateTime::currentDateTime();
    if (ui->dateTimeEdit->isEnabled()) {
        item     = new QStandardItem(ui->dateTimeEdit->dateTime().toLocalTime().toString("yyyy:MM:dd hh:mm:ss"));
        dateTime = ui->dateTimeEdit->dateTime();
    } else {
        switch (ui->countdownTimeUnitTypes->currentData().toInt()) {
        case TimeUnitType::Seconds:
            dateTime = dateTime.addSecs(ui->countdownTime->value());
            break;
        case TimeUnitType::Minutes:
            dateTime = dateTime.addSecs(ui->countdownTime->value() * 60);
            break;
        case TimeUnitType::Hours:
            dateTime = dateTime.addSecs(ui->countdownTime->value() * pow(60, 2));
            break;
        case TimeUnitType::Days:
            dateTime = dateTime.addDays(ui->countdownTime->value());
            break;
        default:
            break;
        }
        item = new QStandardItem(dateTime.toString("yyyy:MM:dd hh:mm:ss"));
    }
    rowItems.emplace_back(item);

    for (auto &i : rowItems) {
        i->setTextAlignment(Qt::AlignCenter);
        i->setEditable(false);
    }

    model->appendRow(rowItems);
    rows.emplace_back(rowItems);

//    auto getUTCTimeOffset = []() -> int {
//        // 获取系统时间
//        time_t _rt = time(nullptr);
//        // 系统时间转换为GMT时间
//        tm _gtm = *gmtime(&_rt);
//        // 再将GMT时间重新转换为系统时间
//        time_t _gt = mktime(&_gtm);
//        // 这时的_gt已经与实际的系统时间_rt有时区偏移了,计算两个值的之差就是时区偏的秒数,除60就是分钟
//        int offset = _rt - _gt;
//        return offset;
//    };
    auto operationBase                              = operationMap[ui->operationTypes->currentText().toStdString()];
    std::chrono::system_clock::time_point startTime = std::chrono::system_clock::from_time_t(dateTime.toSecsSinceEpoch());
//    startTime += std::chrono::seconds(getUTCTimeOffset());
    Work::WorkOneShot workOneShot(operationBase, startTime);
    
//    auto time_t = std::chrono::system_clock::to_time_t(startTime);
//    // 使用 std::put_time 格式化时间
//    std::stringstream ss;
//    ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
//    std::string str = ss.str();
//    ui->labelDebug->setText(str.c_str());
    
    std::shared_ptr<Work::WorkBase> work = std::make_shared<Work::WorkOneShot>(workOneShot);
    vecWorks.emplace_back(work);
    worker_.addWork(work);
}

void OptionWidget::on_btnDeleteTask_clicked() {
    if (selectionModel_->hasSelection()) {
        auto index = selectionModel_->currentIndex();
        model->removeRow(index.row());
        vecWorks.at(index.row())->stopWork();
        vecWorks.erase(vecWorks.begin() + index.row());
    } else {
        QMessageBox messageBox(this);
        messageBox.setModal(true);
        messageBox.setText("请选择一个任务");
        messageBox.exec();
    }
}
