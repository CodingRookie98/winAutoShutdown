/**
 ******************************************************************************
 * @file           : menuTrayIcon.h
 * @author         : hui
 * @brief          : None
 * @attention      : None
 * @date           : 2024/2/22
 ******************************************************************************
 */

#ifndef WINAUTOSHUTDOWN_SRC_UI_MENUTRAYICON_H_
#define WINAUTOSHUTDOWN_SRC_UI_MENUTRAYICON_H_

#include <QMenu>

class MenuTrayIcon : public QMenu {
    Q_OBJECT
public:
    MenuTrayIcon();
    ~MenuTrayIcon() override;
    
signals:
    void sigExit();
    void sigShowMainWindow();

private:
    void init();
    void signalsProcess();

    QAction *actExit;
    QAction *actMainWindow;
};

#endif // WINAUTOSHUTDOWN_SRC_UI_MENUTRAYICON_H_
