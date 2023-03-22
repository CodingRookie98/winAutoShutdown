#ifndef SHUTDOWN_H
#define SHUTDOWN_H

#include <QWidget>
namespace Ui {
    class shutdown;
}

class shutdown: public QWidget {
    Q_OBJECT

public:
    explicit shutdown(QWidget* parent = nullptr);
    ~shutdown();

protected:
    // 重写窗口大小变化事件
    virtual void resizeEvent(QResizeEvent* event);
private:
    Ui::shutdown* ui;

    int button_height; // 按钮高度
    int bottomMargin;// 底部按钮距离底部距离
    int leftMargin;// 底部按钮左边距

    void onButtonConfirmClicked(); // 执行定时关机命令
    void interfaceInitialization(); // 界面初始化
    // 信息输出, false表示背景色为红色，true为绿色
    void informationDisplay(const QString labelMessage, bool color);
    // 界面组件信号检测及激活设置
    void singnalDetect();
    // 执行命令
    QString excuteCommand(const QString& command);
};

#endif // SHUTDOWN_H
