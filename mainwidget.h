#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <error.h>
#include <QWidget>
#include <QGroupBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QresizeEvent>
#include <QCheckBox>
#include <QSpinBox>
#include <QTextBrowser>
#include <QPlainTextEdit>
#include <QScrollBar>
#include <QTcpSocket>
#include <QHostAddress>
#include <QTcpServer>
#include <QStatusBar>
#include <QSpacerItem>
#include <QMessageBox>
#include <QHostInfo>
#include <QUdpSocket>
#include <QDateTime>
#include <QTime>
#include <QFileDialog>
#include <QFile>
#include <QDialog>
#include "surfixconfig.h"

class CPeerDesp{
public:
    explicit CPeerDesp(QHostAddress addr, uint16_t port);

public:
    QHostAddress m_Addr;
    uint16_t m_Port;
};

typedef enum{
    EN_TCPClient_Connect_Stat_Idle,
    EN_TCPClient_Connect_Stat_Connecting,
    EN_TCPClient_Connect_Stat_Connected,
}EN_TCPClient_Connect_Stat_Type;

typedef enum{
    EN_NET_PROTOCOL_UDP,
    EN_NET_PROTOCOL_TCPClient,
    EN_NET_PROTOCOL_TCPServer
}EN_NET_PROTOCOL_Type;

class CNetSettingView
{
public:
    CNetSettingView(QVBoxLayout *parent, EN_NET_PROTOCOL_Type type);
    ~CNetSettingView();

public:
    QVBoxLayout* m_pParent;
    EN_NET_PROTOCOL_Type m_NetProtocolType;
    QLabel* m_pLocalAddrLbl = NULL;
    QComboBox* m_pLocalAddrCBox = NULL;
    QLabel* m_pLocalPortLbl = NULL;
    QLineEdit* m_pLocalPortLEdit = NULL;
    QLabel* m_pRemoteAddrLbl = NULL;
    QLineEdit* m_pRemoteAddrLEdit = NULL;
    QLabel* m_pRemotePortLbl = NULL;
    QLineEdit* m_pRemotePortLEdit = NULL;
    QPushButton* m_pOpenBtn = NULL;
    QPushButton* m_pConnectBtn = NULL;
    QHBoxLayout* m_pBtnLayout = NULL;
};

class CMainWidget : public QWidget
{
    Q_OBJECT
public:
    CMainWidget(QWidget *parent = 0);
    ~CMainWidget();

private:
    void _CreateUiNetSet();
    void _CreateUiRecvSet();
    void _CreateUiSendSet();
    void _CreateUiMainRight();
    int _InsertPeerDespToUdpHash(QHostAddress addr, uint16_t port);
    void _ClearUdpPeerHash();
    int _GetPeerDespFromUdpHash(int index, QHostAddress* pAddr, uint16_t* pPort);
    int _GetConnectedPeerDespSize();
    int _AnalysisAddrAndPort(QString text, QHostAddress* pAddr, uint16_t* pPort);

private:
    QHBoxLayout* m_pMainLayout = NULL;
    QVBoxLayout* m_pLeftLayout = NULL;
    QGridLayout* m_pRightLayout = NULL;
    QGroupBox* m_pNetSetGBox = NULL;
    QGroupBox* m_pRecvSetGBox = NULL;
    QGroupBox* m_pSendSetGBox = NULL;
    QComboBox* m_pProtocolCBox = NULL;
    CNetSettingView* m_pNetSettingView = NULL;
    QCheckBox* m_pRecvToFileChb = NULL;
    QCheckBox* m_pRecvAutoNewlineChb = NULL;
    QCheckBox* m_pRecvShowTimeChb = NULL;
    QCheckBox* m_pResvShowAsHexChb = NULL;
    QCheckBox* m_pRecvPauseChb = NULL;
    QPushButton* m_pRecvSaveBtn = NULL;
    QPushButton* m_pRecvClearBtn = NULL;
    QCheckBox* m_pSendFileChb = NULL;
    QCheckBox* m_pSendAutoSurfixChb = NULL;
    QCheckBox* m_pSendAckChb = NULL;
    QCheckBox* m_pSendAsHexChb = NULL;
    QCheckBox* m_pSendIntervalChb = NULL;
    QSpinBox* m_pSendIntervalSBox = NULL;
    QPushButton* m_pSendLoadFileBtn = NULL;
    QPushButton* m_pSendClearBtn = NULL;
    QGroupBox* m_pRecvDataGBox = NULL;
    QPlainTextEdit* m_pRecvDataTEdit = NULL;
    QPlainTextEdit* m_pSendDataTEdit = NULL;
    QPushButton* m_pSendBtn = NULL;
    QTcpSocket* m_pTcpSocket = NULL;
    EN_TCPClient_Connect_Stat_Type m_TCPClientConnectStat = EN_TCPClient_Connect_Stat_Idle;
    QTcpServer* m_pTcpServer = NULL;
    QLabel* m_pRxCounterLbl = NULL;
    QLabel* m_pTxCounterLbl = NULL;
    QPushButton* m_pZeroCounterBtn = NULL;
    QStatusBar* m_pStatusBar = NULL;
    QString m_RemoteAddr;
    uint16_t m_RemotePort;
    QString m_LocalAddr;
    uint16_t m_LocalPort;
    QLabel* m_pSessionLbl = NULL;
    QComboBox* m_pSessionCBox = NULL;
    QPushButton* m_pSessionBtn = NULL;
    QList<QTcpSocket *> m_PeerList;
    bool m_bIsTcpServerOpened = false;
    QUdpSocket* m_pUdpSocket = NULL;
    bool m_bIsUdpSessionOpened = false;
    QHash<int, CPeerDesp *> m_UdpPeerHash;
    bool m_bIsSessionEdit = false;
    QString m_CurSessionText;
    bool m_bRecvAutoNewlineChbLastState;
    QFile* m_pRecvStreamFile = NULL;
    int m_iRecvStreamFileFd = -1;

signals:
    void ShowMsgInStatusBar(QString msg);
    void RecvCounterUpdate(uint64_t num);
    void SendCounterUpdate(uint64_t num);
    void TxRxCounterClear();

private slots:
    void _OnProtocolChanged(int index);
    void _OnConnectBtnClicked();
    void _OnOpenBtnClicked();
    void _OnTcpSocketReadReady();
    void _OnTcpSocketErrorOccur(QAbstractSocket::SocketError socketError);
    void _OnTcpSocketConnect();
    void _OnSendDataBtnCliecked();
    void _OnNewConnection();
    void _OnTcpServerReadFromSocket();
    void _OnTcpServerSocketDisconnect();
    void _OnUdpSocketReadyRead();
    void _OnSessionBtnClicked();
    void _OnSessionCBoxCurTextChanged(QString text);
    void _ClearRecvZone();
    void _ClearSendZone();
    void _OnRecvShowTimeChbChecked(bool value);
    void _OnRecvToFileChbChecked(bool value);
    void _SaveReceivedDataToFile();
    void _OnSendAutoSurfixChbChecked(bool value);
};

#endif // MAINWIDGET_H
