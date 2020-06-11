﻿/*
 * Copyright 2020 Qter(qsak@foxmail.com). All rights reserved.
 *
 * The file is encoding with utf-8 (with BOM). It is a part of QtSwissArmyKnife
 * project(https://www.qsak.pro). The project is an open source project. You can
 * get the source of the project from: "https://github.com/qsak/QtSwissArmyKnife"
 * or "https://gitee.com/qsak/QtSwissArmyKnife". Also, you can join in the QQ
 * group which number is 952218522 to have a communication.
 */
#include <QDebug>
#include <QEventLoop>
#include <QHostAddress>
#include <QApplication>

#include "SAKDebugPage.hh"
#include "SAKWebSocketServerDevice.hh"
#include "SAKWebSocketServerDebugPage.hh"
#include "SAKWebSocketServerDeviceController.hh"

SAKWebSocketServerDevice::SAKWebSocketServerDevice(SAKWebSocketServerDebugPage *debugPage, QObject *parent)
    :SAKDevice(parent)
    ,debugPage(debugPage)
    ,webSocketServer(Q_NULLPTR)
{

}

void SAKWebSocketServerDevice::run()
{
    QEventLoop eventLoop;
    SAKWebSocketServerDeviceController *deviceController = debugPage->controllerInstance();
    serverHost = deviceController->serverHost();
    serverPort = deviceController->serverPort();
    QString serverName = QString("%1:%2").arg(serverHost).arg(serverPort);

    QList<QWebSocket*> clientList;
    webSocketServer = new QWebSocketServer(serverName, QWebSocketServer::NonSecureMode);
    if (!webSocketServer->listen(QHostAddress(serverHost), serverPort)){
        emit deviceStateChanged(false);
        emit messageChanged(tr("服务器监听地址、端口失败：")+webSocketServer->errorString(), false);
        return;
    }else{
        emit deviceStateChanged(true);
    }

    while (true){
        /// @brief 响应中断
        if (isInterruptionRequested()){
            break;
        }

        /// @brief 处理接入
        while (webSocketServer->hasPendingConnections()){
            QWebSocket *socket = webSocketServer->nextPendingConnection();
            if (socket){
                clientList.append(socket);
                deviceController->addClient(socket->peerAddress().toString(), socket->peerPort(), socket);
            }
        }

        /// @brief 检查链接状态，移除已断开的链接
        for (auto var : clientList){
            QList<QWebSocket*> offLineClientList;
            if (var->state() != QTcpSocket::ConnectedState){
                offLineClientList.append(var);
            }

            for (auto var : offLineClientList){
                /// @brief socket（127.0.0.1）断开链接后无法获取：peerAddress及eerPort
                deviceController->removeClient(var);
                clientList.removeOne(var);
            }
        }

        /// @brief 读取数据
        for (auto var : clientList){
            innerReadBytes(var, deviceController);
        }

        /// @brief 写数据
        while (true){
            QByteArray bytes = takeWaitingForWrittingBytes();
            if (bytes.length()){
                for (auto var : clientList){
                    innerWriteBytes(var, bytes, deviceController);
                }
            }else{
                break;
            }
        }

        /// @brief 处理线程事件
        eventLoop.processEvents();

        /// @brief 线程睡眠
        threadMutex.lock();
        threadWaitCondition.wait(&threadMutex, debugPage->readWriteParameters().runIntervalTime);
        threadMutex.unlock();
    }

    webSocketServer->close();
    delete webSocketServer;
    emit deviceStateChanged(false);
}

void SAKWebSocketServerDevice::innerReadBytes(QWebSocket *socket, SAKWebSocketServerDeviceController *deviceController)
{        
//    socket->waitForReadyRead(debugPage->readWriteParameters().waitForReadyReadTime);
//    QByteArray bytes = socket->readAll();
//    QString currentClientHost = deviceController->currentClientHost();
//    QString peerHost = socket->peerAddress().toString();
//    quint16 currentClientPort = deviceController->currentClientPort();
//    quint16 peerPort = socket->peerPort();

//    if (bytes.length()){
//        if ((currentClientHost == peerHost) && (currentClientPort == peerPort)){
//            emit bytesRead(bytes);
//        }
//    }
}

void SAKWebSocketServerDevice::innerWriteBytes(QWebSocket *socket, QByteArray bytes, SAKWebSocketServerDeviceController *deviceController)
{    
//    QString currentClientHost = deviceController->currentClientHost();
//    QString peerHost = socket->peerAddress().toString();
//    quint16 currentClientPort = deviceController->currentClientPort();
//    quint16 peerPort = socket->peerPort();
//    if ((currentClientHost == peerHost) && (currentClientPort == peerPort)){
//        qint64 ret = socket->write(bytes);
//        socket->waitForBytesWritten(debugPage->readWriteParameters().waitForBytesWrittenTime);
//        if (ret == -1){
//            emit messageChanged(tr("无法写入数据:(%1)%2").arg(socket->peerAddress().toString().arg(socket->error())), false);
//        }else{
//            emit bytesWritten(bytes);
//        }
//    }
}
