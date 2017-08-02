/**
 * @file      surfixset.cpp
 * @brief
 * @details
 * @author    ranwei
 * @version
 * @date      2017/8/2 14:41:34:970
 * @copyright R_W
 * @par         (c) COPYRIGHT 2010-2018 by R_W Systems, Inc.
 *                        All rights reserved.
 *
 *       This software is confidential and proprietary to R_W
 *     Systems, Inc.  No part of this software may be reproduced,
 *     stored, transmitted, disclosed or used in any form or by any means
 *     other than as expressly provided by the written license agreement
 *     between R_W Systems and its licensee.
 * @par History
 *         1.Date         -- 2017/8/2 14:41:34:970
 *           Author       -- ranwei
 *           Modification -- Created file
 *
 */

#define  SURFIXSET_GLOBAL

/* includes-------------------------------------------------------------------*/
#include <QRegExpValidator>
#include "surfixconfig.h"

/* Private typedef&macro&definde----------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* External functions --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/

CSurfixConfigDlg::CSurfixConfigDlg(QWidget *parent)
{
    QRegExp regExpHex("([0-9]|[A-E]|[a-e]){2}");

    QGroupBox* pGroup = new QGroupBox("附加位设置");
    QGridLayout* pGrpLayout = new QGridLayout;
    pGrpLayout->setMargin(5);
    pGrpLayout->setSpacing(5);

    m_pNegativeRBtn = new QRadioButton("负校验");
    QLabel* pMsgLbl1 = new QLabel("(附加位字节的值为其他所有字节和的负数)");
    m_pPositiveRBtn =  new QRadioButton("正校验");
    QLabel* pMsgLbl2 = new QLabel("(附加位字节的值为其他所有字节的和)");
    m_pXorRBtn =  new QRadioButton("异或位");
    QLabel* pMsgLbl3 = new QLabel("(附加位字节的值为其他所有字节的异或)");
    m_pCustomRBtn =  new QRadioButton("固定位");
    QLabel* pMsgLbl4 = new QLabel("(附加位字节的值为固定的16进制数：");
    m_pCustomSurfixLEdit = new QLineEdit("0D");
    m_pCustomSurfixLEdit->setValidator(new QRegExpValidator(regExpHex, this));
    m_pCustomSurfixLEdit->setFixedWidth(20);
    QLabel* pMsgLbl5 = new QLabel("H)");
    QHBoxLayout* pLayout = new QHBoxLayout;
    pLayout->addWidget(pMsgLbl4);
    pLayout->addWidget(m_pCustomSurfixLEdit);
    pLayout->addWidget(pMsgLbl5);
    m_pCustomRBtn->setChecked(true);
    connect(m_pNegativeRBtn, SIGNAL(clicked(bool)), this, SLOT(_OnRadioButtonClicked(bool)));
    connect(m_pPositiveRBtn, SIGNAL(clicked(bool)), this, SLOT(_OnRadioButtonClicked(bool)));
    connect(m_pXorRBtn, SIGNAL(clicked(bool)), this, SLOT(_OnRadioButtonClicked(bool)));
    connect(m_pCustomRBtn, SIGNAL(clicked(bool)), this, SLOT(_OnRadioButtonClicked(bool)));


    pGrpLayout->addWidget(m_pNegativeRBtn, 0, 0, 1, 1);
    pGrpLayout->addWidget(pMsgLbl1, 0, 1, 1, 1);
    pGrpLayout->addWidget(m_pPositiveRBtn, 1, 0, 1, 1);
    pGrpLayout->addWidget(pMsgLbl2, 1, 1, 1, 1);
    pGrpLayout->addWidget(m_pXorRBtn, 2, 0, 1, 1);
    pGrpLayout->addWidget(pMsgLbl3, 2, 1, 1, 1);
    pGrpLayout->addWidget(m_pCustomRBtn, 3, 0, 1, 1);
    pGrpLayout->addLayout(pLayout, 3, 1, 1, 1);

    pGroup->setLayout(pGrpLayout);

    QGridLayout* pMainLayout = new QGridLayout;
    pMainLayout->setMargin(5);
    pMainLayout->setSpacing(5);

    m_pOkBtn = new QPushButton("确定");
    m_pOkBtn->setIcon(QIcon("://resources/image/ok.png"));
    m_pOkBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_pOkBtn->setFixedWidth(66);
    connect(m_pOkBtn, SIGNAL(clicked()), this, SLOT(_OnOkBtnClicked()));
    m_pCancelBtn = new QPushButton("取消");
    m_pCancelBtn->setIcon(QIcon("://resources/image/cancel.png"));
    m_pCancelBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_pCancelBtn->setFixedWidth(66);
    connect(m_pCancelBtn, SIGNAL(clicked()), this, SLOT(_OnCancelBtnClicked()));

    pMainLayout->addWidget(pGroup, 0, 0, 1, 2);
    pMainLayout->addWidget(m_pOkBtn, 1, 0, 1, 1);
    pMainLayout->addWidget(m_pCancelBtn, 1, 1, 1, 1);
    pMainLayout->setAlignment(pGroup, Qt::AlignCenter);
    pMainLayout->setAlignment(m_pOkBtn, Qt::AlignCenter);
    pMainLayout->setAlignment(m_pCancelBtn, Qt::AlignCenter);
    setLayout(pMainLayout);

    setWindowIcon(QIcon("://resources/image/config.png"));
    setWindowTitle("附加位设置");
    setFixedSize(326, 146);
    setWindowFlags(Qt::WindowCloseButtonHint);
}

CSurfixConfigDlg::~CSurfixConfigDlg()
{
    if(m_pNegativeRBtn != NULL)
    {
        delete m_pNegativeRBtn;
        m_pNegativeRBtn = NULL;
    }

    if(m_pPositiveRBtn != NULL)
    {
        delete m_pPositiveRBtn;
        m_pPositiveRBtn = NULL;
    }

    if(m_pXorRBtn != NULL)
    {
        delete m_pXorRBtn;
        m_pXorRBtn = NULL;
    }

    if(m_pCustomRBtn != NULL)
    {
        delete m_pCustomRBtn;
        m_pCustomRBtn = NULL;
    }

    if(m_pCustomSurfixLEdit != NULL)
    {
        delete m_pCustomSurfixLEdit;
        m_pCustomSurfixLEdit = NULL;
    }
}

void CSurfixConfigDlg::_OnOkBtnClicked()
{
    if(m_SuffixType == EN_Suffix_Custom)
    {

    }
    QDialog::accept();
}

void CSurfixConfigDlg::_OnCancelBtnClicked()
{
    QDialog::reject();
}

void CSurfixConfigDlg::_OnRadioButtonClicked(bool value)
{
    QRadioButton* pBtn;
    pBtn = qobject_cast<QRadioButton *>(sender());

    if(pBtn == m_pNegativeRBtn)
    {
        m_SuffixType = EN_Suffix_Negative;
    }
    else if(pBtn == m_pPositiveRBtn)
    {
        m_SuffixType = EN_Suffix_Positive;
    }
    else if(pBtn == m_pXorRBtn)
    {
        m_SuffixType = EN_Suffix_Xor;
    }
    else if(pBtn == m_pCustomRBtn)
    {
        m_SuffixType = EN_Suffix_Custom;
    }
}


/****************** (C) COPYRIGHT 2010-2018 TaiF ******END OF FILE*************/

