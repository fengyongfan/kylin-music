#ifndef MUSICDATABASE_H
#define MUSICDATABASE_H
#include <QSqlDatabase>
#include <QObject>
#include <QFile>
#include <QList>
#include <QString>
#include<QThread>
#include<QMutexLocker>

const QString ALLMUSIC = "LocalMusic";              //本地总表
const QString HISTORY = "HistoryPlayList";          //历史记录
const QString FAV = "FavorPlayList";                //我喜欢

enum DB_RETURN_STATUS{              //数据库操作结果返回表
    DB_OP_SUCC          = (0),      //数据库操作成功
    DB_UNCONNECT        = (-1),     //数据库连接失败导致的错误
    INVALID_INPUT       = (-2),     //无效的输入值
    DB_DISORDERD        = (-3),     //数据库与外界顺序不符导致的失败
    DB_EMPTY_TABLE      = (-4),     //数据库中的表格内容为空
    DB_OP_ADD_FAILED    = (-5),     //数据库添加操作失败
    DB_OP_DEL_FAILED    = (-6),     //数据库删除操作失败
    DB_OP_GET_FAILED    = (-7),     //数据库查询操作失败
    DB_OP_ADD_REPEAT    = (-8),     //数据库添加失败，重复添加
    DB_INSIDE_FAILED    = (-9),     //数据库内部错误
    PLAYLIST_UNFOUND    = (-10),    //数据库中播放列表未找到
    PLAYLIST_IS_EMPTY   = (-11),    //数据库中该播放列表为空
    CREATE_TABLE_FAILED = (-12),    //数据库创表失败
    DEL_TABLE_FAILED    = (-13),    //数据库删表失败
    SONG_NOT_FOUND      = (-14),    //数据库中未找到该歌曲
    LIST_NOT_FOUND      = (-15),    //数据库中未找到该歌单
};

typedef struct
{
    QString title;
    QString filepath;
    QString singer;
    QString album;
    QString filetype;
    QString size;
    QString time;
}musicDataStruct;

#define g_db (MusicDataBase::getInstance())
class MusicDataBase : public QObject
{
    Q_OBJECT
public:
    ~MusicDataBase();
    //单例，初始化返回指针，完成数据库文件建立
    static MusicDataBase* getInstance();
    //open数据库，建立本地，历史，我喜欢及三个列表
    int initDataBase();
    //根据新建的播放列表名的title值创建新建歌单
    int createNewPlayList(const QString& playListName);
    //根据播放列表名的title值删除对应歌单
    int delPlayList(const QString& playListName);
    //查询当前已有歌单列表
    int getPlayList(QStringList& playListNameList);


    /**************************新建歌曲增删改查****************************/
    //添加歌曲到新建歌单，使用歌曲filePath,歌单名title值，输入数据必须有效，
    int addMusicToPlayList(const QString& filePath,const QString& playListName);
    //从新建歌单中删除歌曲，使用歌曲filePath,歌单名title值，输入数据必须有效，
    int delMusicFromPlayList(const QString& filePath,const QString& playListName);
    //根据歌曲filePath在指定歌单中查询歌曲信息
    int getSongInfoFromPlayList(musicDataStruct &fileData, const QString& filePath,const QString& playListName);
    //根据歌单名title值查询对应歌单列表
    int getSongInfoListFromPlayList(QList<musicDataStruct>& resList,const QString& playListName);

    /**************************本地歌曲增删改查****************************/
    //添加歌曲到本地歌单，使用musicDataStruct结构,输入数据必须有效，
    int addMusicToLocalMusic(const musicDataStruct& fileData);
    //从本地歌单中删除歌曲，使用key:filePath,输入数据必须有效，同时从其他列表中也删除
    int delMusicFromLocalMusic(const QString& filePath);
    //从本地歌单中获取指定歌曲信息，使用key:filePath,输入数据必须有效，
    int getSongInfoFromLocalMusic(const QString& filePath, musicDataStruct &fileData);
    //从数据库中获取本地歌单列表歌曲信息
    int getSongInfoListFromLocalMusic(QList<musicDataStruct>& resList);

    /**************************历史歌单增删改查****************************/
    //添加歌曲到历史歌单，使用歌曲的path值,输入数据必须有效，
    int addMusicToHistoryMusic(const QString& filePath);
    //从历史歌单中删除歌曲，使用歌曲的path值,输入数据必须有效，
    int delMusicFromHistoryMusic(const QString& filePath);
    //从历史歌单中查询指定歌曲信息，使用歌曲的path值,输入数据必须有效，
    int getSongInfoFromHistoryMusic(const QString& filePath, musicDataStruct &fileData);
    //从数据库中获取历史歌单列表歌曲信息
    int getSongInfoListFromHistoryMusic(QList<musicDataStruct>& resList);

protected:
    explicit MusicDataBase(QObject *parent = nullptr);

signals:

public slots:

private:
    //日志处理函数
    void msgHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg);

    QSqlDatabase m_database;//数据库
    QMutex m_mutex;
    bool m_databaseOpenFlag = false;
    //检查歌曲是否在总表中存在
    int checkIfSongExistsInLocalMusic(const QString& filePath);
    //检查歌曲是否在历史歌单中存在
    int checkIfSongExistsInHistoryMusic(const QString& filePath);
    //检查歌曲是否在我喜欢中存在
    int checkIfSongExistsInFavorMusic(const QString& filePath);
    //检查歌单列表是否存在
    int checkPlayListExist(const QString& playListName);
    //检查歌曲是否在歌单列表中存在
    int checkIfSongExistsInPlayList(const QString& filePath, const QString& playListName);


    /**************************字符串转码接口*******************************/
    QString inPutStringHandle(const QString& input);
    QString outPutStringHandle(const QString& output);
};

#endif // MUSICDATABASE_H
