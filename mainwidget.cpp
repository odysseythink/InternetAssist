#include "mainwidget.h"



CPeerDesp::CPeerDesp(QHostAddress addr, uint16_t port)
{
    m_Addr = addr;
    m_Port = port;
    qDebug("new CPeerDesp ,addr is %s, port is %d", m_Addr.toString().toLocal8Bit().data(), m_Port);
}

CNetSettingView::CNetSettingView(QVBoxLayout *parent, EN_NET_PROTOCOL_Type type)
{
    m_pParent = parent;
    m_NetProtocolType = type;
    QRegExp regExpIP("((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])[\\.]){3}(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])");
    QRegExp regExpNetPort("((6553[0-5])|[655[0-2][0-9]|65[0-4][0-9]{2}|6[0-4][0-9]{3}|[1-5][0-9]{4}|[1-9][0-9]{3}|[1-9][0-9]{2}|[1-9][0-9]|[0-9])");

    if(EN_NET_PROTOCOL_UDP == type)
    {
        m_pLocalAddrLbl = new QLabel("本地主机地址:");
        m_pLocalAddrLbl->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        m_pLocalAddrLbl->setFixedHeight(20);
        m_pLocalAddrCBox = new QComboBox;
        m_pLocalAddrCBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        m_pLocalAddrCBox->setFixedHeight(20);
        QHostInfo info=QHostInfo::fromName(QHostInfo::localHostName());
        if(QHostInfo::NoError == info.error())
        {
            for (int iLoop = 0; iLoop < info.addresses().size(); iLoop++)
            {
                qDebug() << "Found address:" << info.addresses()[iLoop].toString() << endl;
                if(QAbstractSocket::IPv4Protocol == info.addresses()[iLoop].protocol())
                {
                    m_pLocalAddrCBox->addItem(info.addresses()[iLoop].toString());
                }
            }
        }
        else
        {
            qDebug() << "Lookup failed:" << info.errorString();
        }
        m_pLocalAddrCBox->addItem("0.0.0.0");
        m_pLocalAddrCBox->addItem("127.0.0.1");
        m_pLocalAddrCBox->setCurrentText("127.0.0.1");
        m_pLocalAddrCBox->setValidator(new QRegExpValidator(regExpIP, m_pParent));
        m_pLocalAddrCBox->setEditable(true);
        m_pLocalAddrLbl->setBuddy(m_pLocalAddrCBox);
        m_pParent->addWidget(m_pLocalAddrLbl);
        m_pParent->addWidget(m_pLocalAddrCBox);

        m_pLocalPortLbl = new QLabel("本地主机端口: ");
        m_pLocalPortLbl->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        m_pLocalPortLbl->setFixedHeight(20);
        m_pLocalPortLEdit = new QLineEdit("0");
        m_pLocalPortLEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        m_pLocalPortLEdit->setFixedHeight(20);
        m_pLocalPortLEdit->setValidator(new QRegExpValidator(regExpNetPort, m_pParent));
        m_pLocalPortLbl->setBuddy(m_pLocalPortLEdit);
        m_pParent->addWidget(m_pLocalPortLbl);
        m_pParent->addWidget(m_pLocalPortLEdit);

        m_pOpenBtn = new QPushButton(QIcon("://resources/image/open.png"), "打开");
        m_pOpenBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        m_pOpenBtn->setFixedHeight(40);
        m_pParent->addWidget(m_pOpenBtn);

    }
    else if(EN_NET_PROTOCOL_TCPClient == type)
    {
        m_pRemoteAddrLbl = new QLabel("远程主机地址: ");
        m_pRemoteAddrLbl->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        m_pRemoteAddrLbl->setFixedHeight(20);
        m_pRemoteAddrLEdit = new QLineEdit("127.0.0.1");
        m_pRemoteAddrLEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        m_pRemoteAddrLEdit->setFixedHeight(20);
        m_pRemoteAddrLEdit->setValidator(new QRegExpValidator(regExpIP, m_pParent));
        m_pRemoteAddrLbl->setBuddy(m_pRemoteAddrLEdit);
        m_pParent->addWidget(m_pRemoteAddrLbl);
        m_pParent->addWidget(m_pRemoteAddrLEdit);

        m_pRemotePortLbl = new QLabel("远程主机端口: ");
        m_pRemotePortLbl->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        m_pRemotePortLbl->setFixedHeight(20);
        m_pRemotePortLEdit = new QLineEdit("0");
        m_pRemotePortLEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        m_pRemotePortLEdit->setFixedHeight(20);
        m_pRemotePortLEdit->setValidator(new QRegExpValidator(regExpNetPort, m_pParent));
        m_pRemotePortLbl->setBuddy(m_pRemotePortLEdit);
        m_pParent->addWidget(m_pRemotePortLbl);
        m_pParent->addWidget(m_pRemotePortLEdit);

        m_pConnectBtn = new QPushButton(QIcon("://resources/image/connected.png"), "连接");
        m_pConnectBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        m_pConnectBtn->setFixedHeight(40);
        m_pParent->addWidget(m_pConnectBtn);
    }
    else if(EN_NET_PROTOCOL_TCPServer == type)
    {
        m_pLocalAddrLbl = new QLabel("本地主机地址: ");
        m_pLocalAddrLbl->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        m_pLocalAddrLbl->setFixedHeight(20);
        m_pLocalAddrCBox = new QComboBox;
        m_pLocalAddrCBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        m_pLocalAddrCBox->setFixedHeight(20);
        QHostInfo info=QHostInfo::fromName(QHostInfo::localHostName());
        if(QHostInfo::NoError == info.error())
        {
            for (int iLoop = 0; iLoop < info.addresses().size(); iLoop++)
            {
                qDebug() << "Found address:" << info.addresses()[iLoop].toString() << endl;
                if(QAbstractSocket::IPv4Protocol == info.addresses()[iLoop].protocol())
                {
                    m_pLocalAddrCBox->addItem(info.addresses()[iLoop].toString());
                }
            }
        }
        else
        {
            qDebug() << "Lookup failed:" << info.errorString();
        }
        m_pLocalAddrCBox->addItem("0.0.0.0");
        m_pLocalAddrCBox->addItem("127.0.0.1");
        m_pLocalAddrCBox->setCurrentText("127.0.0.1");
        m_pLocalAddrCBox->setValidator(new QRegExpValidator(regExpIP, m_pParent));
        m_pLocalAddrCBox->setEditable(true);
        m_pLocalAddrLbl->setBuddy(m_pLocalAddrCBox);
        m_pParent->addWidget(m_pLocalAddrLbl);
        m_pParent->addWidget(m_pLocalAddrCBox);

        m_pLocalPortLbl = new QLabel("本地主机端口: ");
        m_pLocalPortLbl->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        m_pLocalPortLbl->setFixedHeight(20);
        m_pLocalPortLEdit = new QLineEdit("0");
        m_pLocalPortLEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        m_pLocalPortLEdit->setFixedHeight(20);
        m_pLocalPortLEdit->setValidator(new QRegExpValidator(regExpNetPort, m_pParent));
        m_pLocalPortLbl->setBuddy(m_pLocalPortLEdit);
        m_pParent->addWidget(m_pLocalPortLbl);
        m_pParent->addWidget(m_pLocalPortLEdit);

        m_pOpenBtn = new QPushButton(QIcon("://resources/image/open.png"), "打开");
        m_pOpenBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        m_pOpenBtn->setFixedHeight(40);
        m_pParent->addWidget(m_pOpenBtn);
    }
}

CNetSettingView::~CNetSettingView()
{
    if(m_pLocalAddrLbl != NULL)
    {
        m_pParent->removeWidget(m_pLocalAddrLbl);
        delete m_pLocalAddrLbl;
        m_pLocalAddrLbl = NULL;
    }
    if(m_pLocalAddrCBox != NULL)
    {
        m_pParent->removeWidget(m_pLocalAddrCBox);
        delete m_pLocalAddrCBox;
        m_pLocalAddrCBox = NULL;
    }
    if(m_pLocalPortLbl != NULL)
    {
        m_pParent->removeWidget(m_pLocalPortLbl);
        delete m_pLocalPortLbl;
        m_pLocalPortLbl = NULL;
    }
    if(m_pLocalPortLEdit != NULL)
    {
        m_pParent->removeWidget(m_pLocalPortLEdit);
        delete m_pLocalPortLEdit;
        m_pLocalPortLEdit = NULL;
    }
    if(m_pRemoteAddrLbl != NULL)
    {
        m_pParent->removeWidget(m_pRemoteAddrLbl);
        delete m_pRemoteAddrLbl;
        m_pRemoteAddrLbl = NULL;
    }
    if(m_pRemoteAddrLEdit != NULL)
    {
        m_pParent->removeWidget(m_pRemoteAddrLEdit);
        delete m_pRemoteAddrLEdit;
        m_pRemoteAddrLEdit = NULL;
    }
    if(m_pRemotePortLbl != NULL)
    {
        m_pParent->removeWidget(m_pRemotePortLbl);
        delete m_pRemotePortLbl;
        m_pRemotePortLbl = NULL;
    }
    if(m_pRemotePortLEdit != NULL)
    {
        m_pParent->removeWidget(m_pRemotePortLEdit);
        delete m_pRemotePortLEdit;
        m_pRemotePortLEdit = NULL;
    }
    if(m_pOpenBtn != NULL)
    {
        m_pParent->removeWidget(m_pOpenBtn);
        delete m_pOpenBtn;
        m_pOpenBtn = NULL;
    }
    if(m_pConnectBtn != NULL)
    {
        m_pParent->removeWidget(m_pConnectBtn);
        delete m_pConnectBtn;
        m_pConnectBtn = NULL;
    }
    if(m_pBtnLayout != NULL)
    {
        m_pParent->removeItem(m_pBtnLayout);
        delete m_pBtnLayout;
        m_pBtnLayout = NULL;
    }

}

CMainWidget::CMainWidget(QWidget *parent) : QWidget(parent)
{
    m_pMainLayout = new QHBoxLayout;
    m_pMainLayout->setContentsMargins(5, 5, 5, 5);
    m_pMainLayout->setSpacing(5);
    setLayout(m_pMainLayout);

    m_pLeftLayout = new QVBoxLayout;
    m_pLeftLayout->setContentsMargins(5, 5, 5, 5);
    m_pLeftLayout->setSpacing(5);

    _CreateUiNetSet();
    m_pLeftLayout->addWidget(m_pNetSetGBox);

    _CreateUiRecvSet();
    m_pLeftLayout->addWidget(m_pRecvSetGBox);

    _CreateUiSendSet();
    m_pLeftLayout->addWidget(m_pSendSetGBox);

    m_pMainLayout->addLayout(m_pLeftLayout);

    _CreateUiMainRight();
    m_pMainLayout->addLayout(m_pRightLayout);

    m_pMainLayout->setStretchFactor(m_pLeftLayout, 1);
    m_pMainLayout->setStretchFactor(m_pRightLayout, 10);

    connect(m_pSendBtn, SIGNAL(clicked()), this, SLOT(_OnSendDataBtnCliecked()));

    qDebug("hint height is %d, hint width is %d", minimumSizeHint().height(), minimumSizeHint().width());
    setGeometry(window()->width()/2, window()->height()/2, 800, 686);
    setFixedHeight(586);
    setFixedWidth(800);

    if(NULL == m_pUdpSocket)
    {
        m_pUdpSocket = new QUdpSocket;
    }
    connect(m_pNetSettingView->m_pOpenBtn, SIGNAL(clicked()), this, SLOT(_OnOpenBtnClicked()));
    connect(m_pUdpSocket, SIGNAL(readyRead()), this, SLOT(_OnUdpSocketReadyRead()));
}

CMainWidget::~CMainWidget()
{
    if(m_pNetSettingView != NULL)
    {
        delete m_pNetSettingView;
        m_pNetSettingView = NULL;
    }
    if(m_pProtocolCBox!= NULL)
    {
        delete m_pProtocolCBox;
        m_pProtocolCBox = NULL;
    }
    if(m_pNetSetGBox != NULL)
    {
        delete m_pNetSetGBox;
        m_pNetSetGBox = NULL;
    }

    if(m_pRecvToFileChb != NULL)
    {
        delete m_pRecvToFileChb;
        m_pRecvToFileChb = NULL;
    }
    if(m_pRecvAutoNewlineChb != NULL)
    {
        delete m_pRecvAutoNewlineChb;
        m_pRecvAutoNewlineChb = NULL;
    }
    if(m_pRecvShowTimeChb != NULL)
    {
        delete m_pRecvShowTimeChb;
        m_pRecvShowTimeChb = NULL;
    }
    if(m_pResvShowAsHexChb != NULL)
    {
        delete m_pResvShowAsHexChb;
        m_pResvShowAsHexChb = NULL;
    }
    if(m_pRecvPauseChb != NULL)
    {
        delete m_pRecvPauseChb;
        m_pRecvPauseChb = NULL;
    }
    if(m_pRecvSaveBtn != NULL)
    {
        delete m_pRecvSaveBtn;
        m_pRecvSaveBtn = NULL;
    }
    if(m_pRecvClearBtn != NULL)
    {
        delete m_pRecvClearBtn;
        m_pRecvClearBtn = NULL;
    }
    if(m_pRecvSetGBox != NULL)
    {
        delete m_pRecvSetGBox;
        m_pRecvSetGBox = NULL;
    }

    if(m_pSendFileChb != NULL)
    {
        delete m_pSendFileChb;
        m_pSendFileChb = NULL;
    }
    if(m_pSendAutoSurfixChb != NULL)
    {
        delete m_pSendAutoSurfixChb;
        m_pSendAutoSurfixChb = NULL;
    }
    if(m_pSendAckChb != NULL)
    {
        delete m_pSendAckChb;
        m_pSendAckChb = NULL;
    }
    if(m_pSendAsHexChb != NULL)
    {
        delete m_pSendAsHexChb;
        m_pSendAsHexChb = NULL;
    }
    if(m_pSendIntervalChb != NULL)
    {
        delete m_pSendIntervalChb;
        m_pSendIntervalChb = NULL;
    }
    if(m_pSendIntervalSBox != NULL)
    {
        delete m_pSendIntervalSBox;
        m_pSendIntervalSBox = NULL;
    }
    if(m_pSendLoadFileBtn != NULL)
    {
        delete m_pSendLoadFileBtn;
        m_pSendLoadFileBtn = NULL;
    }
    if(m_pSendClearBtn != NULL)
    {
        delete m_pSendClearBtn;
        m_pSendClearBtn = NULL;
    }
    if(m_pSendSetGBox != NULL)
    {
        delete m_pSendSetGBox;
        m_pSendSetGBox = NULL;
    }

    if(m_pRecvDataTEdit != NULL)
    {
        delete m_pRecvDataTEdit;
        m_pRecvDataTEdit = NULL;
    }
    if(m_pRecvDataGBox != NULL)
    {
        delete m_pRecvDataGBox;
        m_pRecvDataGBox = NULL;
    }

    if(m_pSendBtn != NULL)
    {
        delete m_pSendBtn;
        m_pSendBtn = NULL;
    }
    if(m_pSendDataTEdit != NULL)
    {
        delete m_pSendDataTEdit;
        m_pSendDataTEdit = NULL;
    }

    if(m_pLeftLayout != NULL)
    {
        delete m_pLeftLayout;
        m_pLeftLayout = NULL;
    }
    if(m_pRightLayout != NULL)
    {
        delete m_pRightLayout;
        m_pRightLayout = NULL;
    }
    if(m_pMainLayout != NULL)
    {
        delete m_pMainLayout;
        m_pMainLayout = NULL;
    }
}

void CMainWidget::_CreateUiNetSet()
{
    m_pProtocolCBox = new QComboBox;
    m_pProtocolCBox->setFixedHeight(20);
    m_pProtocolCBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_pProtocolCBox->addItems(QStringList() << "UDP" << "TCP Client" << "TCP Server");
    m_pProtocolCBox->setCurrentIndex(0);
    QLabel *pProtocolLbl = new QLabel("协议类型: ");
    pProtocolLbl->setFixedHeight(20);
    pProtocolLbl->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    pProtocolLbl->setBuddy(m_pProtocolCBox);
    m_pNetSetGBox = new QGroupBox("网络设置");
    QVBoxLayout* pNetSetLayout = new QVBoxLayout;
    //pNetSetLayout->setSizeConstraint(QLayout::SetMinimumSize);
    pNetSetLayout->setContentsMargins(5, 5, 5, 5);
    pNetSetLayout->setSpacing(5);
    pNetSetLayout->addWidget(pProtocolLbl);
    pNetSetLayout->addWidget(m_pProtocolCBox);
    m_pNetSetGBox->setLayout(pNetSetLayout);

    m_pNetSettingView = new CNetSettingView(pNetSetLayout, EN_NET_PROTOCOL_UDP);
    connect(m_pProtocolCBox, SIGNAL(currentIndexChanged(int)), this, SLOT(_OnProtocolChanged(int)));
}

void CMainWidget::_CreateUiRecvSet()
{
    m_pRecvSetGBox = new QGroupBox("接收设置", this);
    QVBoxLayout* pRecvSetLayout = new QVBoxLayout(this);
    pRecvSetLayout->setContentsMargins(5, 5, 5, 5);
    pRecvSetLayout->setSpacing(5);

    m_pRecvToFileChb = new QCheckBox("接收转向文件......", this);
    m_pRecvToFileChb->setFixedHeight(20);
    m_pRecvToFileChb->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    pRecvSetLayout->addWidget(m_pRecvToFileChb);
    connect(m_pRecvToFileChb, SIGNAL(clicked(bool)), this, SLOT(_OnRecvToFileChbChecked(bool)));
    m_pRecvAutoNewlineChb =  new QCheckBox("自动换行显示", this);
    m_pRecvAutoNewlineChb->setFixedHeight(20);
    m_pRecvAutoNewlineChb->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    pRecvSetLayout->addWidget(m_pRecvAutoNewlineChb);
    m_pRecvShowTimeChb = new QCheckBox("显示接收时间", this);
    m_pRecvShowTimeChb->setFixedHeight(20);
    m_pRecvShowTimeChb->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    pRecvSetLayout->addWidget(m_pRecvShowTimeChb);
    connect(m_pRecvShowTimeChb, SIGNAL(clicked(bool)), this, SLOT(_OnRecvShowTimeChbChecked(bool)));
    m_pResvShowAsHexChb = new QCheckBox("16进制显示", this);
    m_pResvShowAsHexChb->setFixedHeight(20);
    m_pResvShowAsHexChb->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    pRecvSetLayout->addWidget(m_pResvShowAsHexChb);
    m_pRecvPauseChb = new QCheckBox("暂停接收显示", this);
    m_pRecvPauseChb->setFixedHeight(20);
    m_pRecvPauseChb->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    pRecvSetLayout->addWidget(m_pRecvPauseChb);
    QHBoxLayout* pLayout = new QHBoxLayout(this);
    pLayout->setContentsMargins(5, 5, 5, 5);
    pLayout->setSpacing(5);
    m_pRecvSaveBtn = new QPushButton("保存数据", this);
    m_pRecvSaveBtn->setStyleSheet(":!hover{border:none;color:blue;text-decoration:underline;}"
                                  ":hover{border:none;color:red;text-decoration:none;}");
    connect(m_pRecvSaveBtn, SIGNAL(clicked()), this, SLOT(_SaveReceivedDataToFile()));
    m_pRecvClearBtn = new QPushButton("清除接收", this);
    m_pRecvClearBtn->setStyleSheet(":!hover{border:none;color:blue;text-decoration:underline;}"
                                  ":hover{border:none;color:red;text-decoration:none;}");
    connect(m_pRecvClearBtn, SIGNAL(clicked()), this, SLOT(_ClearRecvZone()));

    pLayout->addWidget(m_pRecvSaveBtn);
    pLayout->addWidget(m_pRecvClearBtn);
    pRecvSetLayout->addLayout(pLayout);

    m_pRecvSetGBox->setLayout(pRecvSetLayout);
}

void CMainWidget::_CreateUiSendSet()
{
    m_pSendSetGBox = new QGroupBox("发送设置", this);
    QVBoxLayout* pSendSetLayout = new QVBoxLayout(this);
    pSendSetLayout->setContentsMargins(5, 5, 5, 5);
    pSendSetLayout->setSpacing(5);

    m_pSendFileChb = new QCheckBox("启用文件数据源......", this);
    m_pSendFileChb->setFixedHeight(20);
    m_pSendFileChb->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    pSendSetLayout->addWidget(m_pSendFileChb);
    m_pSendAutoSurfixChb =  new QCheckBox("自动发送附加位", this);
    m_pSendAutoSurfixChb->setFixedHeight(20);
    m_pSendAutoSurfixChb->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    pSendSetLayout->addWidget(m_pSendAutoSurfixChb);
    connect(m_pSendAutoSurfixChb, SIGNAL(clicked(bool)), this, SLOT(_OnSendAutoSurfixChbChecked(bool)));
    m_pSendAckChb = new QCheckBox("自动发送应答包", this);
    m_pSendAckChb->setFixedHeight(20);
    m_pSendAckChb->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    pSendSetLayout->addWidget(m_pSendAckChb);
    m_pSendAsHexChb = new QCheckBox("16进制发送", this);
    m_pSendAsHexChb->setFixedHeight(20);
    m_pSendAsHexChb->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    pSendSetLayout->addWidget(m_pSendAsHexChb);
    connect(m_pSendAsHexChb, SIGNAL(clicked(bool)), this, SLOT(_OnSendAsHexChbChecked(bool)));
    m_pSendIntervalChb = new QCheckBox("发送周期", this);
    m_pSendIntervalChb->setFixedHeight(20);
    m_pSendIntervalChb->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_pSendIntervalSBox = new QSpinBox();
    m_pSendIntervalSBox->setFixedHeight(20);
    m_pSendIntervalSBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_pSendIntervalSBox->setMinimum(0);
    m_pSendIntervalSBox->setMaximum(1000000);
    m_pSendIntervalSBox->setValue(1000);
    m_pSendIntervalSBox->setSuffix("ms");
    QHBoxLayout* pIntervalLayout = new QHBoxLayout;
    pIntervalLayout->addWidget(m_pSendIntervalChb);
    pIntervalLayout->addWidget(m_pSendIntervalSBox);
    pSendSetLayout->addLayout(pIntervalLayout);
    QHBoxLayout* pLayout = new QHBoxLayout(this);
    pLayout->setContentsMargins(5, 5, 5, 5);
    pLayout->setSpacing(5);
    m_pSendLoadFileBtn = new QPushButton("文件载入", this);
    m_pSendLoadFileBtn->setStyleSheet(":!hover{border:none;color:blue;text-decoration:underline;}"
                                  ":hover{border:none;color:red;text-decoration:none;}");
    m_pSendClearBtn = new QPushButton("清除输入", this);
    m_pSendClearBtn->setStyleSheet(":!hover{border:none;color:blue;text-decoration:underline;}"
                                  ":hover{border:none;color:red;text-decoration:none;}");
    connect(m_pSendClearBtn, SIGNAL(clicked()), this, SLOT(_ClearSendZone()));

    pLayout->addWidget(m_pSendLoadFileBtn);
    pLayout->addWidget(m_pSendClearBtn);
    pSendSetLayout->addLayout(pLayout);

    m_pSendSetGBox->setLayout(pSendSetLayout);
}

void CMainWidget::_CreateUiMainRight()
{
    QRegExp regExpSession("((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])[\\.]){3}(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])[\\:]((6553[0-5])|[655[0-2][0-9]|65[0-4][0-9]{2}|6[0-4][0-9]{3}|[1-5][0-9]{4}|[1-9][0-9]{3}|[1-9][0-9]{2}|[1-9][0-9]|[0-9])");

    m_pRecvDataGBox = new QGroupBox("发送设置", this);
    m_pRecvDataGBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_pRecvDataTEdit = new QPlainTextEdit;
    m_pRecvDataTEdit->setVerticalScrollBar(new QScrollBar());
    m_pRecvDataTEdit->setHorizontalScrollBar(new QScrollBar());
    m_pRecvDataTEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QHBoxLayout* pGroupLayout = new QHBoxLayout;
    pGroupLayout->setContentsMargins(5, 5, 5, 5);
    pGroupLayout->setSpacing(5);
    pGroupLayout->addWidget(m_pRecvDataTEdit);
    m_pRecvDataGBox->setLayout(pGroupLayout);

    m_pSendDataTEdit = new QPlainTextEdit;
    m_pSendDataTEdit->setVerticalScrollBar(new QScrollBar());
    m_pSendDataTEdit->setHorizontalScrollBar(new QScrollBar());
    m_pSendDataTEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_pSendDataTEdit->setFixedHeight(40);
    m_pSendBtn = new QPushButton(QIcon("://resources/image/send.png") ,"发送");
    m_pSendBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_pSendBtn->setFixedHeight(40);
    m_pSendBtn->setFixedWidth(80);

    m_pSessionLbl = new QLabel("远程主机：");
    m_pSessionLbl->setFixedWidth(64);
    m_pSessionCBox = new QComboBox;
    m_pSessionCBox->setEditable(true);
    m_pSessionCBox->insertItem(0, QString("All Connections"));
    m_pSessionCBox->setValidator(new QRegExpValidator(regExpSession, this));
    connect(m_pSessionCBox, SIGNAL(currentTextChanged(QString)), this, SLOT(_OnSessionCBoxCurTextChanged(QString)));
    m_pSessionLbl->setBuddy(m_pSessionCBox);
    m_pSessionBtn = new QPushButton("清除");
    m_pSessionBtn->setIcon(QIcon("://resources/image/delete.png"));
    m_pSessionBtn->setFixedWidth(80);
    m_pSessionBtn->setEnabled(false);
    connect(m_pSessionBtn, SIGNAL(clicked()), this, SLOT(_OnSessionBtnClicked()));


    m_pRightLayout = new QGridLayout;
    m_pRightLayout->setContentsMargins(5, 5, 5, 5);
    m_pRightLayout->setSpacing(5);
    m_pRightLayout->addWidget(m_pRecvDataGBox, 0, 0, 1, 3);
    m_pRightLayout->addWidget(m_pSessionLbl, 1, 0, 1, 1);
    m_pRightLayout->addWidget(m_pSessionCBox, 1, 1, 1, 1);
    m_pRightLayout->addWidget(m_pSessionBtn, 1, 2, 1, 1);
    m_pRightLayout->addWidget(m_pSendDataTEdit, 2, 0, 1, 2);
    m_pRightLayout->addWidget(m_pSendBtn, 2, 2, 1, 1);

    //m_pRightLayout->setStretchFactor(m_pRecvDataGBox, 28);
    //m_pRightLayout->setStretchFactor(m_pSessionWidget, 1);
   // m_pRightLayout->setStretchFactor(pLayout, 1);
}

int CMainWidget::_InsertPeerDespToUdpHash(QHostAddress addr, uint16_t port)
{
    int key;
    CPeerDesp* pPeerDesp = NULL;
    if(EN_NET_PROTOCOL_UDP == m_pNetSettingView->m_NetProtocolType)
    {
        qDebug("insert peer addr is %s, port is %d", addr.toString().toLocal8Bit().data(), port);
        QHash<int, CPeerDesp *>::iterator iterator = m_UdpPeerHash.begin();
        while(iterator != m_UdpPeerHash.end())
        {
            pPeerDesp = iterator.value();
            if((pPeerDesp->m_Addr == addr) && (pPeerDesp->m_Port == port))
            {
                qDebug("the (addr %s , port %d) already in udp list", addr.toString().toLocal8Bit().data(), port);
                return 0;
            }
            ++iterator;
        }

        pPeerDesp = new CPeerDesp(addr, port);
        if(NULL == pPeerDesp)
        {
            qFatal("not enough space to new a ST_Peer_Desp_Type struct");
            return -2;
        }

        key = m_UdpPeerHash.size() + 1;
        m_UdpPeerHash.insert(key, pPeerDesp);
        return key;
    }

    return -1;
}

void CMainWidget::_ClearUdpPeerHash()
{
    CPeerDesp* pPeerDesp = NULL;

    if(EN_NET_PROTOCOL_UDP == m_pNetSettingView->m_NetProtocolType)
    {
        qDebug("%s:%d, item size is %d", __FUNCTION__, __LINE__, m_UdpPeerHash.size());
        if(m_UdpPeerHash.size() <= 0)
        {
            qDebug("udp peer map has no item to clear");
            return;
        }

        QHash<int, CPeerDesp *>::iterator iterator = m_UdpPeerHash.begin();
        while(iterator != m_UdpPeerHash.end())
        {
            pPeerDesp = iterator.value();
            if(pPeerDesp != NULL)
            {
                delete pPeerDesp;
                pPeerDesp = NULL;
            }
            ++iterator;
        }

        m_UdpPeerHash.clear();
    }
}

int CMainWidget::_GetPeerDespFromUdpHash(int index, QHostAddress* pAddr, uint16_t* pPort)
{
    CPeerDesp* pPeerDesp = NULL;

    if(index <= 0)
    {
        qDebug("index must greater than zero");
        return -1;
    }

    if(EN_NET_PROTOCOL_UDP == m_pNetSettingView->m_NetProtocolType)
    {
        if(m_UdpPeerHash.size() <= 0)
        {
            qDebug("udp peer map has no item to clear");
            return -1;
        }

        pPeerDesp = m_UdpPeerHash.value(index);
        if(NULL == pPeerDesp)
        {
            qDebug("can't get the key(%d) corresponded value", index);
            return -1;
        }
        qDebug("key %d corresponded addr is %s , port is %d", index, pPeerDesp->m_Addr.toString().toLocal8Bit().data(), pPeerDesp->m_Port);
        *pAddr = pPeerDesp->m_Addr;
        *pPort = pPeerDesp->m_Port;
        return 0;
    }

    return -1;
}

int CMainWidget::_GetConnectedPeerDespSize()
{
    return m_UdpPeerHash.size();
}

int CMainWidget::_AnalysisAddrAndPort(QString text, QHostAddress *pAddr, uint16_t *pPort)
{
    QRegExp regExpSession("((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])[\\.]){3}(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])[\\:]((6553[0-5])|[655[0-2][0-9]|65[0-4][0-9]{2}|6[0-4][0-9]{3}|[1-5][0-9]{4}|[1-9][0-9]{3}|[1-9][0-9]{2}|[1-9][0-9]|[0-9])");

    if((text.isEmpty()) || (NULL == pAddr) || (NULL == pPort))
    {
        qFatal("can't analysis ip addr and Port");
        return -1;
    }

    QStringList textList = text.split(QRegExp("[\\:]"));
    if(textList.length() != 2)
    {
        qFatal("invalid text format");
        return -1;
    }
    QString addrText = textList.at(0);
    QString portText = textList.at(1);
    QHostAddress addr(addrText);

    *pAddr = addr;
    *pPort = portText.toInt();

    qDebug() << "_AnalysisAddrAndPort : addr is " <<  addrText << ", port is " << portText;
    return 0;
}

void CMainWidget::_OnProtocolChanged(int index)
{
    delete m_pNetSettingView;
    m_pNetSettingView = new CNetSettingView((QVBoxLayout*)m_pNetSetGBox->layout(), (EN_NET_PROTOCOL_Type)index);

    if(EN_NET_PROTOCOL_TCPClient == index)
    {
        if(m_pTcpServer != NULL)
        {
            delete m_pTcpServer;
            m_pTcpServer = NULL;
        }

        if(m_pUdpSocket != NULL)
        {
            m_bIsUdpSessionOpened = false;
            m_pUdpSocket->close();
            delete m_pUdpSocket;
            m_pUdpSocket = NULL;
        }
        if(m_UdpPeerHash.size() > 0)
        {
            _ClearUdpPeerHash();
        }

        m_pRecvDataTEdit->clear();
        m_pSessionLbl->setVisible(false);
        m_pSessionCBox->setVisible(false);
        m_pSessionBtn->setVisible(false);
        connect(m_pNetSettingView->m_pConnectBtn, SIGNAL(clicked()), this, SLOT(_OnConnectBtnClicked()));

        if(NULL == m_pTcpSocket)
        {
            m_pTcpSocket = new QTcpSocket(this);
        }

        connect(m_pTcpSocket, SIGNAL(readyRead()), this, SLOT(_OnTcpSocketReadReady()));
        connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
                this, SLOT(_OnTcpSocketErrorOccur(QAbstractSocket::SocketError)));
        connect(m_pTcpSocket, SIGNAL(connected()), this, SLOT(_OnTcpSocketConnect()));
    }
    else if(EN_NET_PROTOCOL_UDP == index)
    {
        if(m_pTcpServer != NULL)
        {
            delete m_pTcpServer;
            m_pTcpServer = NULL;
        }
        if(m_pTcpSocket != NULL)
        {
            delete m_pTcpSocket;
            m_pTcpSocket = NULL;
        }
        if(m_UdpPeerHash.size() > 0)
        {
            _ClearUdpPeerHash();
        }

        m_pSessionLbl->setText("远程主机：");
        m_pSessionCBox->clear();
        m_pSessionCBox->insertItem(0, QString("All Connections"));
        connect(m_pSessionCBox, SIGNAL(currentTextChanged(QString)), this, SLOT(_OnSessionCBoxCurTextChanged(QString)));
        m_pSessionBtn->setText("清除");
        m_pSessionBtn->setIcon(QIcon("://resources/image/delete.png"));
        m_pSessionBtn->setEnabled(false);
        connect(m_pSessionBtn, SIGNAL(clicked()), this, SLOT(_OnSessionBtnClicked()));
        m_pSessionLbl->setVisible(true);
        m_pSessionCBox->setVisible(true);
        m_pSessionBtn->setVisible(true);

        if(NULL == m_pUdpSocket)
        {
            m_pUdpSocket = new QUdpSocket;
        }
        connect(m_pNetSettingView->m_pOpenBtn, SIGNAL(clicked()), this, SLOT(_OnOpenBtnClicked()));
        connect(m_pUdpSocket, SIGNAL(readyRead()), this, SLOT(_OnUdpSocketReadyRead()));
    }
    else if(EN_NET_PROTOCOL_TCPServer == index)
    {

        if(m_pTcpSocket != NULL)
        {
            delete m_pTcpSocket;
            m_pTcpSocket = NULL;
        }
        if(m_pUdpSocket != NULL)
        {
            m_bIsUdpSessionOpened = false;
            m_pUdpSocket->close();
            delete m_pUdpSocket;
            m_pUdpSocket = NULL;
        }
        if(m_UdpPeerHash.size() > 0)
        {
            _ClearUdpPeerHash();
        }
        m_pRecvDataTEdit->clear();
        m_pSessionLbl->setText("客户端：");
        m_pSessionCBox->clear();
        m_pSessionCBox->addItem("All Connections");
        m_pSessionBtn->setText("断开");
        m_pSessionLbl->setVisible(true);
        m_pSessionCBox->setVisible(true);
        m_pSessionBtn->setVisible(true);

        connect(m_pNetSettingView->m_pOpenBtn, SIGNAL(clicked()), this, SLOT(_OnOpenBtnClicked()));
        if(NULL == m_pTcpServer)
        {
            m_pTcpServer = new QTcpServer();
        }

        connect(m_pTcpServer, SIGNAL(newConnection()), this, SLOT(_OnNewConnection()));
    }
}

void CMainWidget::_OnConnectBtnClicked()
{
    if(EN_NET_PROTOCOL_TCPClient == m_pNetSettingView->m_NetProtocolType)
    {
        if(EN_TCPClient_Connect_Stat_Idle == m_TCPClientConnectStat)
        {
            m_pNetSettingView->m_pConnectBtn->setEnabled(false);
            m_pNetSettingView->m_pConnectBtn->setText("连接中......");
            m_pTcpSocket->abort();
            m_pTcpSocket->connectToHost(m_pNetSettingView->m_pRemoteAddrLEdit->text(), m_pNetSettingView->m_pRemotePortLEdit->text().toInt());

            m_TCPClientConnectStat = EN_TCPClient_Connect_Stat_Connecting;
            emit ShowMsgInStatusBar(QString("Connecting......"));
        }
        else if(EN_TCPClient_Connect_Stat_Connected == m_TCPClientConnectStat)
        {
            m_TCPClientConnectStat = EN_TCPClient_Connect_Stat_Idle;
            m_pTcpSocket->close();
            m_pNetSettingView->m_pConnectBtn->setText("连接");
            m_pNetSettingView->m_pConnectBtn->setIcon(QIcon("://resources/image/connected.png"));
            emit ShowMsgInStatusBar(QString("close connection"));
        }
    }
    else if(EN_NET_PROTOCOL_UDP == m_pNetSettingView->m_NetProtocolType)
    {

    }
    else if(EN_NET_PROTOCOL_TCPServer == m_pNetSettingView->m_NetProtocolType)
    {

    }
}

void CMainWidget::_OnOpenBtnClicked()
{
    qDebug("%s:%d", __FUNCTION__, __LINE__);
    if(EN_NET_PROTOCOL_TCPClient == m_pNetSettingView->m_NetProtocolType)
    {

    }
    else if(EN_NET_PROTOCOL_UDP == m_pNetSettingView->m_NetProtocolType)
    {
        qDebug("%s:%d", __FUNCTION__, __LINE__);
        if(false == m_bIsUdpSessionOpened)
        {
            qDebug("%s:%d", __FUNCTION__, __LINE__);
            if(!m_pUdpSocket->bind(QHostAddress(m_pNetSettingView->m_pLocalAddrCBox->currentText()), m_pNetSettingView->m_pLocalPortLEdit->text().toInt()))
            {
                m_pUdpSocket->close();
                emit ShowMsgInStatusBar(QString("udp socket bind erro"));
                return;
            }
            m_bIsUdpSessionOpened = true;
            m_pNetSettingView->m_pOpenBtn->setText("断开");
            m_pNetSettingView->m_pOpenBtn->setIcon(QIcon("://resources/image/opened.png"));
            emit TxRxCounterClear();
        }
        else
        {
            m_pSessionCBox->clear();
            m_pSessionCBox->addItem("All Connections");
            m_pNetSettingView->m_pOpenBtn->setText("打开");
            m_pNetSettingView->m_pOpenBtn->setIcon(QIcon("://resources/image/open.png"));
            m_pUdpSocket->close();
            m_bIsUdpSessionOpened = false;
            emit TxRxCounterClear();
        }
    }
    else if(EN_NET_PROTOCOL_TCPServer == m_pNetSettingView->m_NetProtocolType)
    {
        if(false == m_bIsTcpServerOpened)
        {
            quint16 port = m_pNetSettingView->m_pLocalPortLEdit->text().toInt();
            if(!m_pTcpServer->listen(QHostAddress::LocalHost, port))
            {
                m_pTcpServer->close();
                emit ShowMsgInStatusBar(QString("listen erro"));
                return;
            }
            m_bIsTcpServerOpened = true;
            m_pNetSettingView->m_pOpenBtn->setText("断开");
            m_pNetSettingView->m_pOpenBtn->setIcon(QIcon("://resources/image/opened.png"));
        }
        else
        {
            QListIterator<QTcpSocket *> iterator(m_PeerList);
            while(iterator.hasNext())
            {
                iterator.next()->close();
            }
            m_PeerList.clear();
            m_pSessionCBox->clear();
            m_pNetSettingView->m_pOpenBtn->setText("打开");
            m_pNetSettingView->m_pOpenBtn->setIcon(QIcon("://resources/image/open.png"));
            m_pTcpServer->close();
            m_bIsTcpServerOpened = false;
        }
    }
}

void CMainWidget::_OnTcpSocketReadReady()
{
    int64_t recvLen = m_pTcpSocket->bytesAvailable();

    if(recvLen < 0)
    {
        emit ShowMsgInStatusBar(QString("receive error"));
        return;
    }

    if(EN_TCPClient_Connect_Stat_Connected == m_TCPClientConnectStat)
    {
        QString readText = m_pTcpSocket->readAll();

        m_pRecvDataTEdit->insertPlainText(readText);
        //m_pRecvDataTEdit->appendPlainText(readText);

        emit ShowMsgInStatusBar(QString("receive %1 bytes").arg(recvLen));
        emit RecvCounterUpdate(recvLen);
    }
}

void CMainWidget::_OnTcpSocketErrorOccur(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        emit ShowMsgInStatusBar(QString("Remote Host Closed Error -_-"));
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, tr("TCP Client"),
                                 tr("The host was not found. Please check the "
                                    "host name and port settings."));
        emit ShowMsgInStatusBar(QString("Host Not Found Error -_-"));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, tr("TCP Client"),
                                 tr("The connection was refused by the peer. "
                                    "Make sure the fortune server is running, "
                                    "and check that the host name and port "
                                    "settings are correct."));
        emit ShowMsgInStatusBar(QString("Connection Refused Error -_-"));
        break;
    default:
        QMessageBox::information(this, tr("TCP Client"),
                                 tr("The following error occurred: %1.")
                                 .arg(m_pTcpSocket->errorString()));
        emit ShowMsgInStatusBar(QString("The following error occurred: %1.").arg(m_pTcpSocket->errorString()));
    }
    m_pNetSettingView->m_pConnectBtn->setText("连接");
    m_pNetSettingView->m_pConnectBtn->setIcon(QIcon("://resources/image/connected.png"));
    m_pNetSettingView->m_pConnectBtn->setEnabled(true);
}

void CMainWidget::_OnTcpSocketConnect()
{
    if(EN_TCPClient_Connect_Stat_Connecting == m_TCPClientConnectStat)
    {
        m_pNetSettingView->m_pConnectBtn->setEnabled(true);
        m_pNetSettingView->m_pConnectBtn->setText("断开连接");
        m_pNetSettingView->m_pConnectBtn->setIcon(QIcon("://resources/image/disconnected.png"));
        m_TCPClientConnectStat = EN_TCPClient_Connect_Stat_Connected;
        emit ShowMsgInStatusBar(QString("connect ok ~~~"));
    }
}

void CMainWidget::_OnSendDataBtnCliecked()
{
    qDebug("%s:%d", __FUNCTION__, __LINE__);
    if(EN_NET_PROTOCOL_TCPClient == m_pNetSettingView->m_NetProtocolType)
    {
        if(NULL == m_pTcpSocket)
        {
            emit ShowMsgInStatusBar(QString("tcp socket is null"));
            return;
        }

        if(m_TCPClientConnectStat != EN_TCPClient_Connect_Stat_Connected)
        {
            emit ShowMsgInStatusBar(QString("tcp socket is not connected"));
            return;
        }

        m_pTcpSocket->write(m_pSendDataTEdit->toPlainText().toLocal8Bit());
        emit SendCounterUpdate(m_pSendDataTEdit->toPlainText().toLocal8Bit().length());
    }
    else if(EN_NET_PROTOCOL_UDP == m_pNetSettingView->m_NetProtocolType)
    {
        QHostAddress addr;
        uint16_t port;

        if(!m_bIsUdpSessionOpened)
        {
            qDebug("udp shuld be opened first");
            emit ShowMsgInStatusBar(QString("udp shuld be opened first"));
            return;
        }

        QString curIndexText = m_pSessionCBox->currentText();
        if(0 == curIndexText.compare("All Connections", Qt::CaseInsensitive))
        {
            if(1 == m_pSessionCBox->count())
            {
                qDebug("there is no given addr and port to send data to");
                emit ShowMsgInStatusBar(QString("there is no given addr and port to send data to"));
                return;
            }
            for(int iLoop = 1; iLoop < m_pSessionCBox->count(); iLoop++)
            {
                QString despText = m_pSessionCBox->itemText(iLoop);
                if(_AnalysisAddrAndPort(despText, &addr, &port) < 0)
                {
                    qFatal("can't get the index %d corresponded ip addr and port", iLoop);
                    emit ShowMsgInStatusBar(QString("can't get the index %1 corresponded ip addr and port").arg(iLoop));
                    continue;
                }

                qDebug("current peer addr is %s , peer port is %d", addr.toString().toLocal8Bit().data(), port);
                m_pUdpSocket->writeDatagram(m_pSendDataTEdit->toPlainText().toLocal8Bit().data(), m_pSendDataTEdit->toPlainText().toLocal8Bit().size(), addr, port);
                emit ShowMsgInStatusBar(QString("send to %1:%2 %3 bytes").arg(addr.toString()).arg(port).arg(m_pSendDataTEdit->toPlainText().toLocal8Bit().length()));
                emit SendCounterUpdate(m_pSendDataTEdit->toPlainText().toLocal8Bit().length());
            }
        }
        else
        {
            if(_AnalysisAddrAndPort(curIndexText, &addr, &port) < 0)
            {
                qFatal("can't _Analysis Addr And Port");
                emit ShowMsgInStatusBar(QString("can't _Analysis Addr And Port"));
                return;
            }
            qDebug("current peer addr is %s , peer port is %d", addr.toString().toLocal8Bit().data(), port);
            m_pUdpSocket->writeDatagram(m_pSendDataTEdit->toPlainText().toLocal8Bit().data(), m_pSendDataTEdit->toPlainText().toLocal8Bit().size(), addr, port);
            emit ShowMsgInStatusBar(QString("send to %1:%2 %3 bytes").arg(addr.toString()).arg(port).arg(m_pSendDataTEdit->toPlainText().toLocal8Bit().length()));
            emit SendCounterUpdate(m_pSendDataTEdit->toPlainText().toLocal8Bit().length());
        }
    }
    else if(EN_NET_PROTOCOL_TCPServer == m_pNetSettingView->m_NetProtocolType)
    {
        qDebug("%s:%d", __FUNCTION__, __LINE__);
        if(NULL == m_pTcpServer)
        {
            emit ShowMsgInStatusBar(QString("tcp server is null"));
            return;
        }
        if(false == m_bIsTcpServerOpened)
        {
            emit ShowMsgInStatusBar(QString("tcp server is not opened"));
            return;
        }

        QTcpSocket* pCurrentPeer = m_PeerList.at(m_pSessionCBox->currentIndex());
        if(NULL == pCurrentPeer)
        {
            emit ShowMsgInStatusBar(QString("can't find current peer session"));
            return;
        }
        pCurrentPeer->write(m_pSendDataTEdit->toPlainText().toLocal8Bit());
        emit SendCounterUpdate(m_pSendDataTEdit->toPlainText().toLocal8Bit().length());
    }
}

void CMainWidget::_OnNewConnection()
{
    QTcpSocket* pNewPeer = m_pTcpServer->nextPendingConnection();

    m_PeerList.append(pNewPeer);
    m_pSessionCBox->addItem(QString("%1:%2").arg(pNewPeer->localAddress().toString()).arg(pNewPeer->localPort()));

    connect(pNewPeer, SIGNAL(readyRead()), this, SLOT(_OnTcpServerReadFromSocket()));
    connect(pNewPeer, SIGNAL(disconnected()), pNewPeer, SLOT(deleteLater()));
    connect(pNewPeer, SIGNAL(disconnected()),this,SLOT(_OnTcpServerSocketDisconnect()));
}

void CMainWidget::_OnTcpServerReadFromSocket()
{
    QTcpSocket* pSocket = qobject_cast<QTcpSocket *>(sender());

    int64_t recvLen = pSocket->bytesAvailable();

    if(recvLen < 0)
    {
        emit ShowMsgInStatusBar(QString("receive error"));
        return;
    }

        QString readText = pSocket->readAll();

        m_pRecvDataTEdit->insertPlainText(readText);
        //m_pRecvDataTEdit->appendPlainText(readText);

        emit ShowMsgInStatusBar(QString("receive %1 bytes").arg(recvLen));
        emit RecvCounterUpdate(recvLen);
}

void CMainWidget::_OnTcpServerSocketDisconnect()
{

}

void CMainWidget::_OnUdpSocketReadyRead()
{
    bool isOutTimePrefix = false;
    qint64 recvLen, writeLen = 0;
    QHostAddress sender;
    uint16_t senderPort;
    QString timePrefix;
    QString outReadData;
    QString outText;
    while(m_pUdpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(m_pUdpSocket->pendingDatagramSize());
        recvLen = m_pUdpSocket->readDatagram(datagram.data(), datagram.size(),&sender, &senderPort);
        if(recvLen < 0)
        {
            qFatal("readDatagram error");
            return;
        }

        QString destText(QString("%1:%2").arg(sender.toString()).arg(senderPort));
        if(m_pSessionCBox->findText(destText) < 0) /// unkown addr and port, insert to the QComoBox
        {
             m_pSessionCBox->insertItem(m_pSessionCBox->count(), destText);
        }

        if(m_pRecvPauseChb->isChecked())
        {
            emit ShowMsgInStatusBar(QString("receive %1 bytes").arg(recvLen));
            emit RecvCounterUpdate(recvLen);            
            return;
        }

        if(m_pRecvShowTimeChb->isChecked())
        {
            QDateTime currentDateTime = QDateTime::currentDateTime();
            QString currentDate = currentDateTime.toString("yyyy-MM-dd");
            QTime currentTime = QTime::currentTime();
            int hour = currentTime.hour();
            int minute = currentTime.minute();
            int second = currentTime.second();
            int msec = currentTime.msec();
            timePrefix = QString("[%1 %2:%3:%4:%5] ").arg(currentDate).arg(hour).arg(minute).arg(second).arg(msec);

            isOutTimePrefix = true;
        }

        if(m_pResvShowAsHexChb->isChecked())
        {
            QString s;
            QString buf;
            for(int iLoop = 0; iLoop < datagram.count(); iLoop++)
            {
                s.sprintf("%02x ", datagram.at(iLoop));
                //s.asprintf("%02x ", readText.at(iLoop));
                //s.sprintf("%02x, ", (unsigned char)readText.at(iLoop));
                outReadData += s;
            }
        }
        else
        {
            outReadData = QString(datagram);
        }

        if(isOutTimePrefix)
        {
            outText += timePrefix;
        }
        outText += outReadData;

        if(m_pRecvToFileChb->isChecked())
        {
            if(m_iRecvStreamFileFd > 0)
            {
                writeLen = write(m_iRecvStreamFileFd, outText.toLocal8Bit().data(), outText.toLocal8Bit().length());
                qDebug("write to stream file %d bytes", writeLen);
                if(m_pRecvAutoNewlineChb->isChecked())
                {
                    writeLen = write(m_iRecvStreamFileFd, "\r\n", 2);
                    qDebug("write to stream file \\r\\n %d bytes", writeLen);
                }                
            }
        }
        else
        {
            if(m_pRecvAutoNewlineChb->isChecked())
            {
                m_pRecvDataTEdit->appendPlainText(outText);
            }
            else
            {
                m_pRecvDataTEdit->insertPlainText(outText);
            }            
        }

        emit ShowMsgInStatusBar(QString("receive %1 bytes").arg(recvLen));
        emit RecvCounterUpdate(recvLen);
    }
}

void CMainWidget::_OnSessionBtnClicked()
{
    if(EN_NET_PROTOCOL_UDP == m_pNetSettingView->m_NetProtocolType)
    {
        if(QMessageBox::Yes == QMessageBox::question(this, "删除会话", "是否删除当前会话？？？", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes))
        {
            qDebug() << "remove session " << m_pSessionCBox->currentText() << " from session combobox";
            emit ShowMsgInStatusBar(QString("remove session %1 from session combobox").arg(m_pSessionCBox->currentText()));
            m_pSessionCBox->removeItem(m_pSessionCBox->currentIndex());
            return;
        }
        else
        {
            return;
        }
    }
    else if(EN_NET_PROTOCOL_TCPServer == m_pNetSettingView->m_NetProtocolType)
    {

    }
}

void CMainWidget::_OnSessionCBoxCurTextChanged(QString text)
{
    if(text.compare("All Connections", Qt::CaseInsensitive) != 0)
    {
        m_pSessionBtn->setEnabled(true);
    }
    else
    {
        m_pSessionBtn->setEnabled(false);
    }
}

void CMainWidget::_ClearRecvZone()
{
    m_pRecvDataTEdit->clear();
}

void CMainWidget::_ClearSendZone()
{
    m_pSendDataTEdit->clear();
}

void CMainWidget::_OnRecvShowTimeChbChecked(bool value)
{
    if(value)
    {
        m_bRecvAutoNewlineChbLastState = m_pRecvAutoNewlineChb->isChecked();
        m_pRecvAutoNewlineChb->setChecked(true);
        m_pRecvAutoNewlineChb->setEnabled(false);
    }
    else
    {
        m_pRecvAutoNewlineChb->setEnabled(true);
        m_pRecvAutoNewlineChb->setChecked(m_bRecvAutoNewlineChbLastState);
    }
}

void CMainWidget::_OnRecvToFileChbChecked(bool value)
{
    if(value)
    {
        QString fileName = QFileDialog::getOpenFileName(this, tr("select a file to save receive stream"), ".", tr("data Files(*.txt *.log)"));
        if(fileName.length() == 0)
        {
            QMessageBox::information(NULL, tr("filename"), tr("You didn't select any files."));
        }
        else
        {
            QMessageBox::information(NULL, tr("filename"), tr("You selected fileName is ") + fileName);

            char* pFileName = fileName.toLocal8Bit().data();

            if(access(pFileName, 0) != 0)
            {
                qFatal("can't access %s file, errno is %d, reason is %s", pFileName, errno, strerror(errno));
                return;
            }

            m_iRecvStreamFileFd = open(pFileName, O_RDWR | O_APPEND);
            if(m_iRecvStreamFileFd < 0)
            {
                qFatal("can't access %s file, errno is %d, reason is %s", pFileName, errno, strerror(errno));
                return;                
            }

            m_pRecvDataTEdit->setEnabled(false);
        }
    }
    else
    {
        m_pRecvDataTEdit->setEnabled(true);
        if(m_iRecvStreamFileFd > 0)
        {
            ::close(m_iRecvStreamFileFd);
            m_iRecvStreamFileFd = -1;
        }
    }
}

int NormalStringToHexString(QString src, QString dest)
{

}

int HexStringToNormalString(QString src, QString dest)
{

}

void CMainWidget::_OnSendAsHexChbChecked(bool value)
{
    if(value)
    {
        QByteArray sendText = m_pSendDataTEdit->document()->toPlainText().toLocal8Bit();
        qDebug("string len is %d", sendText.length());
        m_pSendDataTEdit->clear();
        QString s;
        QString hexText;
        for(int iLoop = 0; iLoop < sendText.length(); iLoop++)
        {
            hexText += s.sprintf("%02x", sendText.at(iLoop));
        }
        m_pSendDataTEdit->appendPlainText(hexText);
    }
    else
    {

    }
}

void CMainWidget::_SaveReceivedDataToFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("select a file to save already received data"), ".", tr("data Files(*.txt *.log)"));
    if(fileName.length() == 0)
    {
        QMessageBox::information(NULL, tr("filename"), tr("You didn't select any files."));
    }
    else
    {
        QMessageBox::information(NULL, tr("filename"), tr("You selected fileName is ") + fileName);

        char* pFileName = fileName.toLocal8Bit().data();

        if(access(pFileName, 0) != 0)
        {
            qFatal("can't access %s file, errno is %d, reason is %s", pFileName, errno, strerror(errno));
            return;
        }

        int iFileFd = open(pFileName, O_RDWR | O_APPEND);
        if(iFileFd < 0)
        {
            qFatal("can't access %s file, errno is %d, reason is %s", pFileName, errno, strerror(errno));
            return;
        }

        write(iFileFd, m_pRecvDataTEdit->document()->toPlainText().toLocal8Bit().data(), m_pRecvDataTEdit->document()->toPlainText().toLocal8Bit().length());

        ::close(iFileFd);
    }
}

void CMainWidget::_OnSendAutoSurfixChbChecked(bool value)
{
    if(value)
    {
        CSurfixConfigDlg* pSurfixSet = new CSurfixConfigDlg;
        if(pSurfixSet->exec() == QDialog::Accepted)
        {
            qDebug("surfix type is %d, custom byte is 0x%02x", CSurfixConfigDlg::m_SuffixType, CSurfixConfigDlg::m_cCustomSuffix);
        }
        delete pSurfixSet;
    }
    else
    {
    }
}


