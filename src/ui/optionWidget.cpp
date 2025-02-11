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

#include "optionWidget.h"
#include "ui_OptionWidget.h"
#include <chrono>
#include <QMessageBox>
#include <QDialog>

#include "worker.h"
#include "work.h"
#include "power_action.h"

OptionWidget::OptionWidget(QWidget *parent) :
    QWidget(parent), ui(new Ui::OptionWidget) {
    ui->setupUi(this);
    model_          = new QStandardItemModel();
    selectionModel_ = new QItemSelectionModel(model_);
    worker_         = std::make_unique<work::Worker>();

    init();
    signalsProcess();
    worker_->StartWork();
}

OptionWidget::~OptionWidget() {
    delete ui;
    for (auto &list : rows_) {
        for (auto &item : list) {
            delete item;
        }
    }
    delete selectionModel_;
    delete model_;
}

bool OptionWidget::event(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }

    return QWidget::event(event);
}

void OptionWidget::init() {
    ui->operationTypes->addItem(tr("锁定"), QVariant::fromValue(operation::type::PowerActions::Lock));
    ui->operationTypes->addItem(tr("睡眠"), QVariant::fromValue(operation::type::PowerActions::Sleep));
    ui->operationTypes->addItem(tr("休眠"), QVariant::fromValue(operation::type::PowerActions::Hibernate));
    ui->operationTypes->addItem(tr("关机"), QVariant::fromValue(operation::type::PowerActions::Shutdown));
    ui->operationTypes->addItem(tr("重启"), QVariant::fromValue(operation::type::PowerActions::Restart));

    ui->timeTypes->addItem(tr("定时"), QVariant(TimeType::Timing));
    ui->timeTypes->addItem(tr("倒计时"), QVariant(TimeType::Countdown));

    ui->countdownTimeUnitTypes->addItem(tr("s/秒"), QVariant(TimeUnitType::Seconds));
    ui->countdownTimeUnitTypes->addItem(tr("m/分"), QVariant(TimeUnitType::Minutes));
    ui->countdownTimeUnitTypes->addItem(tr("h/时"), QVariant(TimeUnitType::Hours));
    ui->countdownTimeUnitTypes->addItem(tr("d/天"), QVariant(TimeUnitType::Days));

    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->countdownTimeUnitTypes->setEnabled(false);
    ui->countdownTime->setEnabled(false);

    model_->setHorizontalHeaderLabels(QStringList({tr("任务类型"), tr("时间类型"), tr("执行时间")}));
    ui->planTableView->setModel(model_);
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
        default: break; ;
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

    for (const auto &i : rowItems) {
        i->setTextAlignment(Qt::AlignCenter);
        i->setEditable(false);
    }

    model_->appendRow(rowItems);
    rows_.emplace_back(rowItems);

    std::shared_ptr<operation::OperationBase> operation_base = GetOperation(ui->operationTypes->currentData().value<operation::type::PowerActions>());
    std::chrono::system_clock::time_point start_time         = std::chrono::system_clock::from_time_t(dateTime.toSecsSinceEpoch());

    auto work = std::make_shared<work::Work>(std::list{operation_base});
    works_.emplace_back(work);
    worker_->AddWork(work, start_time);
}

void OptionWidget::on_btnDeleteTask_clicked() {
    if (selectionModel_->hasSelection()) {
        const auto index = selectionModel_->currentIndex();
        model_->removeRow(index.row());
        works_.at(index.row())->StopOperate();
        works_.erase(works_.begin() + index.row());
    } else {
        QMessageBox messageBox(this);
        messageBox.setModal(true);
        messageBox.setText(tr("请选择一个任务"));
        messageBox.exec();
    }
}

std::shared_ptr<operation::OperationBase> OptionWidget::GetOperation(const operation::type::PowerActions &power_action_type) {
    if (operations_.contains(power_action_type)) {
        return operations_[power_action_type];
    }
    using namespace operation;
    std::shared_ptr<operation::OperationBase> operation_base = nullptr;
    switch (power_action_type) {
    case operation::type::PowerActions::Lock:
        operation_base = std::make_shared<PowerAction>(type::PowerActions::Lock);
        break;
    case operation::type::PowerActions::Sleep:
        operation_base = std::make_shared<PowerAction>(type::PowerActions::Sleep);
        break;
    case operation::type::PowerActions::Hibernate:
        operation_base = std::make_shared<PowerAction>(type::PowerActions::Hibernate);
        break;
    case operation::type::PowerActions::Shutdown:
        operation_base = std::make_shared<PowerAction>(type::PowerActions::Shutdown);
        break;
    case operation::type::PowerActions::Restart:
        operation_base = std::make_shared<PowerAction>(type::PowerActions::Restart);
        break;
    default:
        operation_base = nullptr;
    }
    if (operation_base) {
        operations_[power_action_type] = operation_base;
    }
    return operation_base;
}
