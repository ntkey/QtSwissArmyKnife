/******************************************************************************
 * Copyright 2023 Qsaker(wuuhaii@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part
 * of QtSwissArmyKnife project.
 *
 * QtSwissArmyKnife is licensed according to the terms in
 * the file LICENCE in the root of the source code directory.
 *****************************************************************************/
#include <QNetworkInterface>
#include <QNetworkAddressEntry>

#include "SAKIpComboBox.hh"

SAKIpComboBox::SAKIpComboBox(QWidget *parent)
    : QComboBox(parent)
{
    auto addresses = QNetworkInterface::allAddresses();
    for (auto &address : addresses) {
        addItem(address.toString());
    }
}
