/******************************************************************************
 * Copyright 2023 Qsaker(wuuhaii@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part
 * of QtSwissArmyKnife project.
 *
 * QtSwissArmyKnife is licensed according to the terms in
 * the file LICENCE in the root of the source code directory.
 *****************************************************************************/
#ifndef SAKTRANSLATOR_HH
#define SAKTRANSLATOR_HH

#include <QMap>
#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include <QTranslator>
#include <QVariantList>
#include <QLoggingCategory>

class SAKTranslator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList languanges READ languanges CONSTANT)
private:
    explicit SAKTranslator(QObject *parent = nullptr);

public:
    static SAKTranslator* instance();
    Q_INVOKABLE void installTranslator(const QString &name);
    Q_INVOKABLE void setConfigurationFile(const QString &conf);

private:
    QList<QJsonObject> mLanguageContextList;
    QList<QTranslator*> mTranslators;
    QString mCurrentName;
    QString mConf;
    const QLoggingCategory mLoggingCategory{"SAK.Translator"};
    QMap<QString, QString> mFlagNameMap;

private:
    void uninstallTranslator();
    void installTranslator(const QJsonArray &packets);

private:
    QStringList languanges();

signals:
    void languageChanged();
};

#endif // SAKTRANSLATOR_HH