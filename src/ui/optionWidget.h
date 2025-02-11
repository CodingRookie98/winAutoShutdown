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
#include <QItemSelectionModel>

namespace work {
class Work;
class Worker;
} // namespace work
namespace operation {
class OperationBase;
class PowerAction;
namespace type {
enum class PowerActions;
}
} // namespace operation

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

protected:
    bool event(QEvent *event) override;

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
    QStandardItemModel *model_;
    QItemSelectionModel *selectionModel_;
    std::vector<QList<QStandardItem *>> rows_;
    std::unique_ptr<work::Worker> worker_;
    std::vector<std::shared_ptr<work::Work>> works_;
    std::unordered_map<operation::type::PowerActions, std::shared_ptr<operation::OperationBase>> operations_;

    void init();
    void signalsProcess();
    void on_btnAddTask_clicked();
    void on_btnDeleteTask_clicked();
    std::shared_ptr<operation::OperationBase> GetOperation(const operation::type::PowerActions &power_action_type);
};

#endif // WINAUTOSHUTDOWN_SRC_OPTIONWIDGET_H_
