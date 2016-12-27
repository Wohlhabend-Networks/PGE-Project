/*
 * Platformer Game Engine by Wohlstand, a free platform for game making
 * Copyright (c) 2016 Vitaly Novichkov <admin@wohlnet.ru>
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

#ifndef CONFIG_MANAGER_PRIVATE_H
#define CONFIG_MANAGER_PRIVATE_H

#include <QString>
#include <QStringList>

namespace ConfigManager
{
    void   checkForImage(QString &imgPath, QString root);

    //special paths
    extern QString imgFile, imgFileM;
    extern QString tmpstr;
    extern QStringList tmp;

    extern QString bgoPath;
    extern QString BGPath;
    extern QString blockPath;
    extern QString npcPath;
    extern QString npcScriptPath;
    extern QString effectPath;
    extern QString playerLvlPath;
    extern QString playerWldPath;
    extern QString playerScriptPath;

    extern QString tilePath;
    extern QString scenePath;
    extern QString pathPath;
    extern QString wlvlPath;

    extern QString commonGPath;

    extern QString scriptPath;

    void    refreshPaths();
    bool    loadEngineSettings(); //!< Load engine.ini file
}

#endif // CONFIG_MANAGER_PRIVATE_H