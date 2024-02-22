/**
 ******************************************************************************
 * @file           : optionWidget.h
 * @author         : hui
 * @brief          : None
 * @attention      : None
 * @date           : 2024/2/18
 ******************************************************************************
 */

#ifndef WINAUTOSHUTDOWN_SRC_OPTIONWIDGET_H_
#define WINAUTOSHUTDOWN_SRC_OPTIONWIDGET_H_

#include <QWidget>
#include <QStandardItemModel>
#include <map>
#include <chrono>
#include <QItemSelectionModel>
#include <QDialog>
#include "../components/operationShutdown.h"
#include "../components/operationReboot.h"
#include "../components/operationLogOff.h"
#include "../components/worker.h"
#include "../components/workOneShot.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class OptionWidget;
}
QT_END_NAMESPACE

class OptionWidget : public QWidget {
    Q_OBJECT

public:
    explicit OptionWidget(QWidget *parent = nullptr);
    ~OptionWidget() override;
    
private:
    enum TimeType {
        Timing,
        Countdown
    };
    
    enum TimeUnitType {
        Seconds,
        Minutes,
        Hours,
        Days
    };
    Ui::OptionWidget *ui;
    std::map<std::string, std::shared_ptr<Operation::OperationBase>> operationMap;
    QStandardItemModel *model;
    QItemSelectionModel *selectionModel_;
    std::vector<QList<QStandardItem*>> rows;
    Work::Worker worker_;
    std::vector<std::shared_ptr<Work::WorkBase>> vecWorks;
    
    void init();
    void signalsProcess();
    void on_btnAddTask_clicked();
    void on_btnDeleteTask_clicked();
};

#endif // WINAUTOSHUTDOWN_SRC_OPTIONWIDGET_H_
