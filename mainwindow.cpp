#include "mainwindow.h"


CMainWindow::CMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_pMainWidget = new CMainWidget;
    m_pMainWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setCentralWidget(m_pMainWidget);

    _CreateStatusBar();

    connect(m_pMainWidget, SIGNAL(ShowMsgInStatusBar(QString)), this, SLOT(_ShowMsgInStatusBar(QString)));
    connect(m_pMainWidget, SIGNAL(RecvCounterUpdate(uint64_t)), this, SLOT(_ShowRxCounterInStatusBar(uint64_t)));
    connect(m_pMainWidget, SIGNAL(SendCounterUpdate(uint64_t)), this, SLOT(_ShowTxCounterInStatusBar(uint64_t)));
    connect(m_pZeroCounterBtn, SIGNAL(clicked()), this, SLOT(_ClearAllCouterInStatusBar()));
    connect(m_pMainWidget, SIGNAL(TxRxCounterClear()), this, SLOT(_ClearAllCouterInStatusBar()));
    //qDebug("mainwindows height is %d, width is %d", height(), width());
    setFixedHeight(614);
    setFixedWidth(800);
}



CMainWindow::~CMainWindow()
{
    if(m_pMainWidget != NULL)
    {
        delete m_pMainWidget;
        m_pMainWidget = NULL;
    }
}

void CMainWindow::_CreateStatusBar()
{
    QWidget *pWidget = new QWidget();
    m_pRxCounterLbl = new QLabel("RX : 0");
    m_pRxCounterLbl->setFrameShape(QFrame::Box);
    m_pRxCounterLbl->setFrameShadow(QFrame::Raised);
    m_pRxCounterLbl->setFixedWidth(160);
    m_pTxCounterLbl = new QLabel("TX : 0");
    m_pTxCounterLbl->setFrameShape(QFrame::Box);
    m_pTxCounterLbl->setFrameShadow(QFrame::Raised);
    m_pTxCounterLbl->setFixedWidth(160);
    m_pZeroCounterBtn = new QPushButton("复位计数");
    m_pStatusBar = statusBar();

    QHBoxLayout* pLayout = new QHBoxLayout;
    pLayout->setContentsMargins(0, 0, 0, 0);
    pLayout->setSpacing(5);


    pLayout->addWidget(m_pRxCounterLbl);
    pLayout->addWidget(m_pTxCounterLbl);
    pLayout->addWidget(m_pZeroCounterBtn);
    pLayout->addSpacing(20);
    pWidget->setLayout(pLayout);
    statusBar()->addPermanentWidget(pWidget);
    statusBar()->setStyleSheet(QString("QStatusBar::item{border:0px}"));
    statusBar()->setSizeGripEnabled(false); //设置是否显示右边的大小控制点
}

void CMainWindow::_ShowMsgInStatusBar(QString msg)
{
    qDebug("%s:%d", __FUNCTION__, __LINE__);
    statusBar()->showMessage(msg, 5000);
}

void CMainWindow::_ShowRxCounterInStatusBar(uint64_t num)
{
    m_llRxCounter += num;
    m_pRxCounterLbl->setText(QString("RX : %1").arg(m_llRxCounter));
}

void CMainWindow::_ShowTxCounterInStatusBar(uint64_t num)
{
    m_llTxCounter += num;
    m_pTxCounterLbl->setText(QString("TX : %1").arg(m_llTxCounter));
}

void CMainWindow::_ClearAllCouterInStatusBar()
{
    m_llRxCounter = 0;
    m_llTxCounter = 0;
    m_pRxCounterLbl->setText(QString("RX : 0"));
    m_pTxCounterLbl->setText(QString("TX : 0"));
}
