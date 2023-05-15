/******************************************************************************
 * Copyright 2023 Qsaker(wuuhaii@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part
 * of QtSwissArmyKnife project.
 *
 * QtSwissArmyKnife is licensed according to the terms in
 * the file LICENCE in the root of the source code directory.
 *****************************************************************************/
#ifndef SAKSTOPBITSCOMBOBOX_HH
#define SAKSTOPBITSCOMBOBOX_HH

#include <QComboBox>

class SAKStopBitsComboBox : public QComboBox
{
    Q_OBJECT
public:
    SAKStopBitsComboBox(QWidget *parent = nullptr);
};

#endif // SAKSTOPBITSCOMBOBOX_HH