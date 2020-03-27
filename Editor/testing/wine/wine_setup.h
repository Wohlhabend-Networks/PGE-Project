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

#ifndef WINE_SETUP_H
#define WINE_SETUP_H

#include <QDialog>
#include <QProcessEnvironment>

namespace Ui {
class wine_setup;
}

class wine_setup : public QDialog
{
    Q_OBJECT

public:
    explicit wine_setup(QWidget *parent = nullptr);
    ~wine_setup();

    void fetchPlayOnLinux();

    static QProcessEnvironment getEnv(const QString &profile);

private:
    Ui::wine_setup *ui;
};

#endif // WINE_SETUP_H