/*
 * Platformer Game Engine by Wohlstand, a free platform for game making
 * Copyright (c) 2014-2020 Vitaly Novichkov <admin@wohlnet.ru>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QMdiSubWindow>
#include <QFile>
#include <QDir>
#include <QSettings>
#include <QDebug>
#include <QMenu>

#include <common_features/app_path.h>
#include <common_features/logger_sets.h>

#include <ui_main_window.h>
#include "main_window.h"

#include "translator.h"

Translator::Translator(QObject *parent) :
    QObject(parent)
{}

Translator::~Translator()
{
    if(m_langsMenu)
    {
        QObject::disconnect(m_langsMenu, SIGNAL(triggered(QAction *)),
                            this, SLOT(slotLanguageChanged(QAction *)));
        m_langsMenu = nullptr;
    }
}

void Translator::initWidget(QMenu *menu)
{
    m_langsMenu = menu;
    QObject::connect(m_langsMenu, SIGNAL(triggered(QAction *)),
                     this, SLOT(slotLanguageChanged(QAction *)));
}


static QString makeLangFilePath(const QString &langPath, const QString &lang)
{
    return langPath + QString("/maintainer_%1.qm").arg(lang);
}

static QString makeQtLangFilePath(const QString &langPath, const QString &lang)
{
    return langPath + QString("/qt_%1.qm").arg(lang);
}

static bool langFileExists(const QString &langPath, const QString &lang)
{
    QString p = makeLangFilePath(langPath, lang);
    return QFile::exists(p);
}

static QString getLangName(const QString &fname)
{
    QString locale;
    locale = fname;                             // "TranslationExample_de.qm"
    locale.truncate(locale.lastIndexOf('.'));   // "TranslationExample_de"
    locale.remove(0, locale.indexOf('_') + 1);  // "de"
    return locale;
}

static QString getStdLangName(const QString &fname)
{
    QString locale;
    locale = fname;                             // "TranslationExample_de.qm"
    locale.truncate(locale.lastIndexOf('.'));   // "TranslationExample_de"
    locale.remove(0, locale.indexOf('_') + 1);  // "de"
    locale = locale.replace('-', '_');
    return locale;
}

void Translator::initTranslator()
{
    /*
     * //Small test from https://qt-project.org/wiki/How_to_create_a_multi_language_application
     */
    QString defaultLocale = QLocale::system().name();

    defaultLocale = defaultLocale.replace('_', '-').toLower();
    if(!langFileExists(m_langPath, defaultLocale))
        defaultLocale.truncate(defaultLocale.lastIndexOf('-'));

    QString inifile = AppPathManager::settingsFile();
    QSettings settings(inifile, QSettings::IniFormat);

    settings.beginGroup("Main");
    {
        m_currLangSetup = settings.value("language", defaultLocale).toString();
    }
    settings.endGroup();

    m_langPath = AppPathManager::languagesDir();

    langListSync();

    m_currLang = m_currLangSetup;
    QLocale locale = QLocale(m_currLang);
    QLocale::setDefault(locale);

    bool ok = m_translator.load(makeLangFilePath(m_langPath, m_currLang));
    if(ok)
        qApp->installTranslator(&m_translator);
    else
    {
        m_currLang = "en"; //set to English if no other translations are found
        QLocale locale = QLocale(m_currLang);
        QLocale::setDefault(locale);
        ok = m_translator.load(makeLangFilePath(m_langPath, m_currLang));
        if(ok)
            qApp->installTranslator(&m_translator);
        langListSync();
    }

    ok = m_translatorQt.load(makeQtLangFilePath(m_langPath, m_currLang));
    if(ok)
        qApp->installTranslator(&m_translatorQt);

    qApp->setLayoutDirection(QObject::tr("LTR") == "RTL" ? Qt::RightToLeft : Qt::LeftToRight);

    emit languageSwitched();
}

void Translator::langListSync()
{
    // format systems language
    m_langsMenu->clear();

    QDir dir(m_langPath);
    QStringList fileNames = dir.entryList(QStringList("maintainer_*.qm"));
    for(int i = 0; i < fileNames.size(); ++i)
    {
        // get locale extracted by filename
        QString locale = getLangName(fileNames[i]);
        QString localeStd = getStdLangName(fileNames[i]);
        QString lang;
        if(locale == "en")
            lang = "English";
        else
        {
            QLocale loc(localeStd);
            lang = QString("%1 (%2)")
                    .arg(loc.nativeLanguageName())
                    .arg(loc.nativeCountryName());
            if(!lang.isEmpty())
                lang[0] = lang[0].toUpper();
        }
        QIcon ico(QString("%1/%2.png").arg(m_langPath).arg(locale));

        QAction *action = new QAction(ico, lang, this);
        action->setCheckable(true);
        action->setData(locale);

        m_langsMenu->addAction(action);

        if(m_currLangSetup == locale)
        {
            action->setChecked(true);
        }
    }

    if(fileNames.size() == 0)
    {
        QAction *action = m_langsMenu->addAction("[translations not found]");
        action->setCheckable(false);
        action->setDisabled(true);
    }
}

void Translator::slotLanguageChanged(QAction *action)
{
    if(nullptr != action)
    {
        // load the language depending on the action content
        loadLanguage(action->data().toString());

        QString inifile = AppPathManager::settingsFile();
        QSettings settings(inifile, QSettings::IniFormat);
        settings.beginGroup("Main");
        {
            settings.setValue("language", m_currLangSetup);
        }
        settings.endGroup();
        settings.sync();
    }
}

bool Translator::switchTranslator(QTranslator &translator, const QString &filename)
{
    // remove the old translator
    qApp->removeTranslator(&translator);
    // load the new translator
    bool ok = translator.load(filename);

    if(ok)
    {
        qApp->installTranslator(&translator);
    }
    return ok;
}

void Translator::loadLanguage(const QString &rLanguage)
{
    if(m_currLang != rLanguage)
    {
        m_currLang = rLanguage;
        QLocale locale = QLocale(m_currLang);
        QLocale::setDefault(locale);
        QString languageName = QLocale::languageToString(locale.language());

        bool ok  = switchTranslator(m_translatorQt, makeQtLangFilePath(m_langPath, m_currLang));
        if(ok)
            qApp->installTranslator(&m_translatorQt);
        ok  = switchTranslator(m_translator, makeLangFilePath(m_langPath, m_currLang));

        if(ok)
        {
            m_currLangSetup = m_currLang;
            emit languageSwitched();
        }

        langListSync();
    }
}
