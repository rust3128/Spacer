#include "mainwindow.h"
#include "GlobalSettings/globalsettings.h"
#include "LogginCategories/loggincategories.h"
#include "Settings/settingsdialog.h"
#include "Settings/userdatadialog.h"
#include "Settings/edituserdata.h"
#include "Settings/userdata.h"
#include "Database/database.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QFile>
#include <QDateTime>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

// Умный указатель на файл логирования
static QScopedPointer<QFile>   m_logFile;

// Объявление обработчика
void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Устанавливаем файл логирования
    m_logFile.reset(new QFile(GlobalSettings::LOG_FILE_NAME));
    // Открываем файл логирования
    m_logFile.data()->open(QFile::Append | QFile::Text);
    // Устанавливаем обработчик
    qInstallMessageHandler(messageHandler);



    QTranslator *trans = new QTranslator();
    QTranslator *guiTrans = new QTranslator();

    if(trans->load(":/Spacer_RU_ua.qm"))
        a.installTranslator(trans);
    if(guiTrans->load(":/Translations/qtbase_uk.qm"))
        a.installTranslator(guiTrans);


    // Загруска файла настроек
    QFile configFile;
    configFile.setFileName(GlobalSettings::CONFIG_FILE_NAME);
    if(!configFile.exists()) {
        qCritical(logCritical()) << QApplication::tr("Не найден конфигурационный файл!");
        auto result = QMessageBox::question(nullptr,QApplication::tr("Ошибка"),QApplication::tr("Не найден файл настроек!\nВыполнить настройку приложения?"));
        if(result == QMessageBox::Yes){
            SettingsDialog *settDlg = new SettingsDialog(true);
            settDlg->exec();
        } else {
            return 1;
        }
    }

    Database *db = new Database();
    if(!db->getIsOpen()) return 1;

    //Определение пользователя
    QString qUsername = QString::fromLocal8Bit (qgetenv ("USERNAME").constData ()).toUtf8 ();
    QSqlQuery q;
    q.prepare("EXECUTE PROCEDURE get_user_id(:username)");
    q.bindValue(":username", qUsername);
    if(!q.exec()){
        qCritical(logCritical()) << q.lastError().text();
        return 1;
    }
    q.next();
    bool isNew = q.value(1).toBool();
    int userID = q.value(0).toInt();
    q.exec("commit work");

    if(isNew){
        //Новый пользователь
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(nullptr, QApplication::tr("Новый пользователь"),
                                        QApplication::tr("Вы первый раз запустили программу. Необходимо заполнить ваши данные.\nСогласны?"),
                                        QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes){
            //Диалог редактирования пользователя
            UserDataDialog *usData = new UserDataDialog(userID, false);
            usData->exec();
        }
    }

    EditUserData *editUserData = new EditUserData(userID);
    UserData *userData = editUserData->getUserData();
    switch (userData->getUiLang()) {
    case 1:
        if(trans->load(":/Spacer_RU_ua.qm"))
            a.installTranslator(trans);
        if(guiTrans->load(":/Translations/qtbase_uk.qm"))
            a.installTranslator(guiTrans);
        break;
    case 2:
        if(trans->load(":/Spacer_RU_en.qm"))
            a.installTranslator(trans);
        if(guiTrans->load(":/Translations/qtbase_en.qm"))
            a.installTranslator(guiTrans);
        break;
    default:
        if(guiTrans->load(":/Translations/qtbase_ru.qm"))
            a.installTranslator(guiTrans);
        break;
    }


    MainWindow w{userID};
    qInfo(logInfo()) << QApplication::tr("Запуск гланого окна приложения.");
    w.show();
    return a.exec();
}

void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // Открываем поток записи в файл
    QTextStream out(m_logFile.data());
    QTextStream console(stdout);
    // Записываем дату записи
    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");
    // По типу определяем, к какому уровню относится сообщение
    switch (type)
    {
#ifdef QT_DEBUG
    case QtInfoMsg:
        out << "[INF] ";
        console << "Info:     " << msg << " ***[" << context.function << " File: " << context.file << " Line: " << context.line << "] " << Qt::endl;
        break;
    case QtDebugMsg:
        out << "[DBG] " ;
        console << "Debug:    " << msg << " ***[" << context.function << " File: " << context.file << " Line: " << context.line << "] " << Qt::endl;
        break;
    case QtWarningMsg:
        out << "[WRN] ";
        console << "Warning:  " << msg << " ***[" << context.function << " File: " << context.file << " Line: " << context.line << "] "  << Qt::endl;
        break;
    case QtCriticalMsg:
        out << "[CRT] ";
        console << "Critical: " << msg << " ***[" << context.function << " File: " << context.file << " Line: " << context.line << "] " << Qt::endl;
        break;
    case QtFatalMsg:
        out << "[FTL] ";
        console << "Fatality: " << msg << " ***[" << context.function << " File: " << context.file << " Line: " << context.line << "] " << Qt::endl;
        break;
#else
    case QtInfoMsg:     out << "[INF] "; break;
    case QtDebugMsg:    out << "[DBG] "; break;
    case QtWarningMsg:  out << "[WRN] "; break;
    case QtCriticalMsg: out << "[CRT] "; break;
    case QtFatalMsg:    out << "[FTL] "; break;
#endif

    }

    // Записываем в вывод категорию сообщения и само сообщение
    out << context.category << ": " << msg;
    out << "  ***[" << context.function << " File: " << context.file << " Line: " << context.line << "]***" << Qt::endl;
    // Очищаем буферизированные данные
    out.flush();
    console.flush();
}
