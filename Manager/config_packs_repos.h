#pragma once
#ifndef CONFPACKREPOS_H
#define CONFPACKREPOS_H

#include <QDialog>
#include <QListWidgetItem>
#include <QNetworkReply>
#include "config_packs.h"

namespace Ui {
class ConfPacksRepos;
}

class ConfPacksRepos : public QDialog
{
Q_OBJECT

public:
    explicit ConfPacksRepos(QWidget *parent=0);
    ~ConfPacksRepos();

private slots:
    void on_add_clicked();
    void on_checkRepo_clicked();
    void on_remove_clicked();
    void clearList();
    void on_repoList_itemChanged(QListWidgetItem *item);
    void replyFinished(QNetworkReply* reply);

private:
    bool lockAdd;
    void addItemToList(ConfigPackRepo &rp);
    Ui::ConfPacksRepos *ui;
};

#endif // CONFPACKREPOS_H
