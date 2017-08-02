#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include "mainwidget.h"

class CMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    CMainWindow(QWidget *parent = 0);
    ~CMainWindow();
    void resizeEvent ( QResizeEvent * event )
    {
        qDebug("the height is %d, the width is %d", height(), width());
#if 0
        QMessageBox msg;
        msg.setText("The size has been modified.");
        msg.exec();
#endif
    }

private:
    CMainWidget* m_pMainWidget = NULL;

    QLabel* m_pRxCounterLbl = NULL;
    QLabel* m_pTxCounterLbl = NULL;
    QPushButton* m_pZeroCounterBtn = NULL;
    QStatusBar* m_pStatusBar;
    uint64_t m_llRxCounter = 0;
    uint64_t m_llTxCounter = 0;

private:
    void _CreateStatusBar();

private slots:
    void _ShowMsgInStatusBar(QString msg);
    void _ShowRxCounterInStatusBar(uint64_t num);
    void _ShowTxCounterInStatusBar(uint64_t num);
    void _ClearAllCouterInStatusBar();
};

#endif // MAINWINDOW_H
