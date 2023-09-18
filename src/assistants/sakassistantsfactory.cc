﻿/******************************************************************************
 * Copyright 2022-2023 Qsaker(qsaker@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of QtSwissArmyKnife
 * project(https://github.com/qsaker/QtSwissArmyKnife).
 *
 * QtSwissArmyKnife is licensed according to the terms in the file LICENCE in
 * the root of the source code directory.
 *****************************************************************************/

#include "sakassistantsfactory.h"

#include <QCoreApplication>

#ifdef SAK_IMPORT_MODULE_FILECHECKASSISTANT
#include "SAKToolFileCheckAssistant.h"
#endif
#ifdef SAK_IMPORT_MODULE_CRCASSISTANT
#include "SAKToolCRCAssistant.h"
#endif
#ifdef SAK_IMPORT_MODULE_FLOATASSISTANT
#include "SAKToolFloatAssistant.h"
#endif
#ifdef SAK_IMPORT_MODULE_STRINGASSISTANT
#include "SAKToolStringAssistant.h"
#endif
#ifdef SAK_IMPORT_MODULE_ASCIIASSISTANT
#include "sakasciiassistant.h"
#endif
#ifdef SAK_IMPORT_MODULE_BROADCASTASSISTANT
#include "SAKToolBroadcastAssistant.h"
#endif
#ifdef SAK_IMPORT_MODULE_BASE64ASSISTANT
#include "sakbase64assistant.h"
#endif

SAKAssistantsFactory::SAKAssistantsFactory(QObject* parent) : QObject(parent) {
#ifdef SAK_IMPORT_MODULE_FILECHECKASSISTANT
  RegisterAssistantMetaType<SAKToolCRCAssistant>(kCrcAssistant,
                                                 tr("CRC Assistant"));
#endif
#ifdef SAK_IMPORT_MODULE_CRCASSISTANT
  RegisterAssistantMetaType<SAKToolFileCheckAssistant>(
      kFileCheckAssistant, tr("File Check Assistant"));
#endif
#ifdef SAK_IMPORT_MODULE_ASCIIASSISTANT
  RegisterAssistantMetaType<SAKAsciiAssistant>(kAsciiAssistant,
                                                   tr("ASCII Assistant"));
#endif
#ifdef SAK_IMPORT_MODULE_FLOATASSISTANT
  RegisterAssistantMetaType<SAKToolFloatAssistant>(kFileCheckAssistant,
                                                   tr("Number Assistant"));
#endif
#ifdef SAK_IMPORT_MODULE_STRINGASSISTANT
  RegisterAssistantMetaType<SAKToolStringAssistant>(kStringAssistant,
                                                    tr("String Assistant"));
#endif
#ifdef SAK_IMPORT_MODULE_BROADCASTASSISTANT
  RegisterAssistantMetaType<SAKToolBroadcastAssistant>(
      kBroadcastAssistant, tr("Broadcast Assistant"));
#endif
#ifdef SAK_IMPORT_MODULE_BASE64ASSISTANT
  RegisterAssistantMetaType<SAKBase64Assisatnt>(kBase64Assistant,
                                                tr("Base64 Assistant"));
#endif
}

QList<int> SAKAssistantsFactory::SupportedAssistants() {
  return type_name_map_.keys();
}

QString SAKAssistantsFactory::GetAssistantName(int type) const {
  if (type_name_map_.contains(type)) {
    return type_name_map_.value(type);
  }

  QString name = QString("UnknowType(%1)").arg(type);
  return name;
}

SAKAssistantsFactory* SAKAssistantsFactory::Instance() {
  static SAKAssistantsFactory* factory = nullptr;
  if (!factory) {
    factory = new SAKAssistantsFactory(qApp);
  }

  return factory;
}

QWidget* SAKAssistantsFactory::NewAssistant(int type) {
  if (meta_object_map_.contains(type)) {
    const QMetaObject meta_obj = meta_object_map_.value(type);
    QObject* obj = meta_obj.newInstance();
    return qobject_cast<QWidget*>(obj);
  }

  return Q_NULLPTR;
}
