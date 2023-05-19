/******************************************************************************
 * Copyright 2023 Qsaker(wuuhaii@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part
 * of QtSwissArmyKnife project.
 *
 * QtSwissArmyKnife is licensed according to the terms in
 * the file LICENCE in the root of the source code directory.
 *****************************************************************************/
#include <QTcpSocket>
#include "SAKTcpServerTool.hh"

SAKTcpServerTool::SAKTcpServerTool(QObject *parent)
    : SAKSocketServerTool{"SAK.TcpServerTool", parent}
{

}

bool SAKTcpServerTool::initialize()
{
    mTcpServer = new QTcpServer();
    if (!mTcpServer->listen(QHostAddress(mServerIp), mServerPort)) {
        outputMessage(QtWarningMsg, mTcpServer->errorString());
        return false;
    }

    mBindingIpPort = QString("%1:%2").arg(mServerIp).arg(mServerPort);
    outputMessage(QtInfoMsg, mBindingIpPort);

    connect(mTcpServer, &QTcpServer::newConnection, mTcpServer, [=](){
        QTcpSocket *client = mTcpServer->nextPendingConnection();
        mTcpSocketList.append(client);

        QString ip = client->peerAddress().toString();
        quint16 port = client->peerPort();
        QString ipPort = QString("%1:%2").arg(ip).arg(port);
        mClients.append(ipPort);
        outputMessage(QtInfoMsg, "New connection:" + ipPort);
        emit clientsChanged();

        connect(client, &QTcpSocket::readyRead, client, [=](){
            QByteArray bytes = client->readAll();
            QString hex = bytes.toHex();
            outputMessage(QtInfoMsg, QString("%1<-%2:%3").arg(mBindingIpPort,
                                                              ipPort,
                                                              hex));
            emit bytesOutputted(bytes, QVariant());
        });

        connect(client, &QTcpSocket::disconnected, client, [=](){
            this->mTcpSocketList.removeOne(client);
            this->mClients.removeOne(ipPort);
            outputMessage(QtInfoMsg, QString("Connection(%1) disconnect:")
                                         .arg(ipPort, client->errorString()));
            emit clientsChanged();
        });

        connect(client, &QTcpSocket::errorOccurred, client, [=](){
            this->mTcpSocketList.removeOne(client);
            this->mClients.removeOne(ipPort);
            outputMessage(QtInfoMsg, QString("Error occurred:")
                                         .arg(client->errorString()));
            emit clientsChanged();
        });
    });

    return true;
}

void SAKTcpServerTool::writeBytes(const QByteArray &bytes, const QVariant &context)
{
    Q_UNUSED(context);
    if (mClientIndex >= 0 && mClientIndex < mTcpSocketList.length()) {
        QTcpSocket *client = mTcpSocketList.at(mClientIndex);
        writeBytesInner(client, bytes, context);
    } else {
        for (auto client : mClients) {
            writeBytesInner(client, bytes, context);
        }
    }
}

void SAKTcpServerTool::uninitialize()
{
    mTcpServer->close();
    mTcpServer->deleteLater();
    mTcpServer = nullptr;
}

void SAKTcpServerTool::writeBytesInner(QTcpSocket *client,
                                       const QByteArray &bytes,
                                       const QVariant &context)
{
    qint64 ret = client->write(bytes);
    if (ret == -1) {
        outputMessage(QtWarningMsg, mTcpServer->errorString());
    } else {
        QString ip = client->peerAddress().toString();
        quint16 port = client->peerPort();
        QString ipPort = QString("%1:%2").arg(ip).arg(port);
        QString hex = bytes.toHex();
        outputMessage(QtInfoMsg, QString("%1->%2:%3").arg(mBindingIpPort,
                                                          ipPort,
                                                          hex));
        emit bytesInputted(bytes, context);
    }
}
