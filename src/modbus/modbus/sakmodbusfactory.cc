﻿/******************************************************************************
 * Copyright 2023 Qsaker(qsaker@foxmail.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part
 * of QtSwissArmyKnife project.
 *
 * QtSwissArmyKnife is licensed according to the terms in
 * the file LICENCE in the root of the source code directory.
 *****************************************************************************/
#include <QCoreApplication>
#include <QModbusTcpClient>
#include <QModbusTcpServer>
#include <QModbusRtuSerialClient>
#include <QModbusRtuSerialServer>

#include "SAKModbusFactory.hh"

SAKModbusFactory::SAKModbusFactory(QObject *parent)
    : QObject(parent)
{

}

SAKModbusFactory::~SAKModbusFactory()
{

}

SAKModbusFactory *SAKModbusFactory::instance()
{
    static SAKModbusFactory f(qApp);
    return &f;
}

const QString SAKModbusFactory::typeName(int type)
{
    if (type == ModbusRtuSerialClient) {
        return tr("RTU Client");
    } else if (type == ModbusRtuSerialServer) {
        return tr("RTU Server");
    } else if (type == ModbusTcpClient) {
        return tr("TCP Client");
    } else if (type == ModbusTcpServer) {
        return tr("TCP Server");
    }

    Q_ASSERT_X(false, __FUNCTION__, "Unknown modebus device type");
    qCWarning(mLoggingCategory) << "Unknown modebus device type";

    return "Unknown";
}

QModbusDevice *SAKModbusFactory::createDevice(int type)
{
    if (type == ModbusRtuSerialClient) {
        qCInfo(mLoggingCategory) << "create rtu serial master";
        return new QModbusRtuSerialClient();
    } else if (type == ModbusRtuSerialServer) {
        qCInfo(mLoggingCategory) << "create rtu serial slave";
        return new QModbusRtuSerialServer();
    } else if (type == ModbusTcpClient) {
        qCInfo(mLoggingCategory) << "create rtu tcp client";
        return new QModbusTcpClient();
    } else if (type == ModbusTcpServer) {
        qCInfo(mLoggingCategory) << "create rtu tcp server";
        return new QModbusTcpServer();
    }

    Q_ASSERT_X(false, __FUNCTION__, "Unknown modebus device type");
    qCWarning(mLoggingCategory) << "Unknown modebus device type";

    return Q_NULLPTR;
}