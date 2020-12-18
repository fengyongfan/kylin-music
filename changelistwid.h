/*
 * Copyright (C) 2020, KylinSoft Co., Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef CHANGELISTWID_H
#define CHANGELISTWID_H


#include <QWidget>
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QStackedWidget>
#include <QButtonGroup>
#include <QLineEdit>
#include <QTableWidget>
//#include <QScrollBar>
#include <QHeaderView>
#include <QListWidget>
#include <QListWidgetItem>
#include <QToolButton>
#include <QDebug>
#include <QSqlQuery>
#include <QFileDialog>
#include <QProgressDialog>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QAction>
#include <QMenu>
#include <QSqlTableModel>
#include <QCryptographicHash>
#include <QDir>
#include <QFileInfo>
#include <QByteArray>
#include <QString>
#include <QSqlTableModel>

//文件拖拽
#include <QEvent>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDragLeaveEvent>
#include <QDropEvent>
#include <QMimeData>

//taglib
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/tpropertymap.h>
//#include <taglib/toolkit/tpropertymap.h>

#include "widgetstyle.h"

class ChangeListWid : public QWidget
{
    Q_OBJECT
public:
    explicit ChangeListWid(QWidget *parent = nullptr);
    void initStack();
    QLabel *songListLabel;
    QLabel *songNumberLabel;
    QLabel *nullMusicIconLabel;
    QLabel *nullMusicLabel;

    QPushButton *n_addLocalSong;   //null页面的添加歌曲按钮
    QPushButton *n_addLocalFolder;   //null页面的添加文件夹按钮

public:

    void nullWidgetColor();

private:
    QStackedWidget *mpwid;
    QFrame *titleFrame;
    QVBoxLayout *vMainLayout;
    QVBoxLayout *vListWidLayout;

    QHBoxLayout *hTitleLayout;
    QHBoxLayout *hListTitleLayout;

};

class MusicListWid :public QWidget
{
    Q_OBJECT
public:
    explicit MusicListWid(QWidget *parent = nullptr);
    void initMusicListWid();
//    void setTableItem(QString title, QString singal, QString cd, QString time);

    QListWidget *musicInfoWidget;

    QLabel *songNumberLabel;

    QLabel *songListLabel;
    QToolButton *top_addSongBtn;  //播放列表界面的添加歌曲按钮
//    QToolButton *top_playAllSongBtn;  //播放界面的播放全部按钮

    int count = 0;

    QStringList AllDirList;
    QStringList songFiles;
    QString Dir;
    QStringList matchMp3Files;
    QString mp3Name;

    QFileInfo fileInfo;
    QByteArray bytes;
    QString titleStr;
    QString artistStr;
    QString albumStr;
    QString timeStr;
    QString mp3Size;
    QString type;
    QString MD5Str;
    QStringList MD5List;
    QDir matchDir;

    // 本地音乐的所有歌曲id
    QStringList localAllMusicid;
    // 本地音乐的所有歌曲Path
    QStringList allmusic;
    // 本地音乐的播放相关
    QMediaPlaylist *PlayList;
    QMediaPlayer *Music;
    QSqlTableModel *localModel;


    int currentPlayIndex = -1;   //高亮相关
    bool isStartPlay = false;
public:

    void get_localmusic_information();   //获取初始界面的歌曲列表信息
//    void get_listmusic_information(int listindex);  //获取歌单页面歌曲信息

    QStringList get_info_from_db(int musicid);  //从数据库用歌曲id获取歌曲信息
    void musiclistcolor();

//public slots:
    void on_top_addSongBtn_slot();  //添加歌曲
    void addFile();                 //添加文件夹
    void addSong(const QStringList &addsong);
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dropEvent(QDropEvent *event);

private:
    QStackedWidget *mpwid;
//    QFrame *titleFrame;
    QVBoxLayout *vMainLayout;
    QVBoxLayout *vListWidLayout;

    QHBoxLayout *hTitleLayout;
    QHBoxLayout *hTitleListLayout;


    QListWidgetItem *testMusicInfo1;
    QListWidgetItem *testMusicInfo2;


    QLabel *songLabel;
    QLabel *singerLabel;
    QLabel *albumLabel;
    QLabel *timeLabel;

};


#endif // CHANGELISTWID_H