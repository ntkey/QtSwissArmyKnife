﻿/***************************************************************************************************
 * Copyright 2018-2023 Qsaker(qsaker@foxmail.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of QtSwissArmyKnife project.
 *
 * QtSwissArmyKnife is licensed according to the terms in the file LICENCE in the root of the source
 * code directory.
 **************************************************************************************************/
#include "sak.h"
#include "sakapplication.h"
#include "saklog.h"

int main(const int argc, char *argv[])
{
    QString appName = QString("QtSwissArmyKnife");
#ifndef SAK_IMPORT_MODULE_PRIVATE
    appName += QObject::tr("(Community)");
#endif
    sakDoSomethingBeforeAppCreated(argv, appName);

    SAKLog::instance()->start();
    SAKApplication app(argc, argv);
    int ret = SAKApplication::exec();
    sakShutdownGoogleLogging();
    return ret;
}
