/**
 * @file      surfixset.hh
 * @brief
 * @details
 * @author    ranwei
 * @version
 * @date      2017/8/2 14:43:47:578
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
 *         1.Date         -- 2017/8/2 14:43:47:578
 *           Author       -- ranwei
 *           Modification -- Created file
 *
 */
#ifndef __SURFIXSET_HH__
#define __SURFIXSET_HH__

#ifdef  SURFIXSET_GLOBAL
#define SURFIXSET_EXT
#else
#define SURFIXSET_EXT extern
#endif /* SURFIXSET_GLOBAL */

/*============================================================================*/
/*                                  @INCLUDES                                 */
/*============================================================================*/
#include <QDialog>
#include <QGroupBox>
#include <QRadioButton>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>

/*============================================================================*/
/*                              @MACROS & @TYPEDEFS                           */
/*============================================================================*/
typedef enum{
    EN_Suffix_Negative,
    EN_Suffix_Positive,
    EN_Suffix_Xor,
    EN_Suffix_Custom,
}EN_Suffix_Type;


/*============================================================================*/
/*                               @GLOBAL VIRIABLES                            */
/*============================================================================*/

/*============================================================================*/
/*                                    @FUNCS                                  */
/*============================================================================*/

/*============================================================================*/
/*                                     @CLASS                                 */
/*============================================================================*/
class CSurfixConfigDlg : public QDialog
{
    Q_OBJECT

public:
    CSurfixConfigDlg(QWidget *parent = 0);
    ~CSurfixConfigDlg();

public:
    EN_Suffix_Type m_SuffixType;
    uint8_t m_cCustomSuffix = 0x00;

private:
    QRadioButton* m_pNegativeRBtn = NULL;
    QRadioButton* m_pPositiveRBtn = NULL;
    QRadioButton* m_pXorRBtn = NULL;
    QRadioButton* m_pCustomRBtn = NULL;
    QLineEdit* m_pCustomSurfixLEdit = NULL;
    QPushButton* m_pOkBtn = NULL;
    QPushButton* m_pCancelBtn = NULL;

private slots:
    void _OnOkBtnClicked();
    void _OnCancelBtnClicked();
    void _OnRadioButtonClicked(bool value);
};


#endif /* __SURFIXSET_H__ */
/****************** (C) COPYRIGHT 2010-2018 TaiF ******END OF FILE*************/
