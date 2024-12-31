#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QToolBar>
#include <QTextEdit>
#include <QMainWindow>
#include "xmlhighlighter.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_as_triggered();

    void on_actionCopy_triggered();

    void on_actionCut_triggered();

    void on_actionPaste_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionNew_triggered();

    void on_actionconvert_to_jason_triggered();

    void on_actionConvert_to_png_triggered();

    void on_actionCompress_triggered();

    void on_actionDecompress_triggered();
    void saveas( QString text,QString type);
    QString opens(QString type);
    void on_actionCheck_consistency_triggered();

    void on_actionPrettify_triggered();

    void on_action_Minify_triggered();

    void on_actionMost_Active_user_triggered();

    void on_actionMost_influencial_triggered();

    void on_actionMutual_followers_triggered();

    void on_actionSuggest_followers_triggered();

    void on_actionWord_search_triggered();

    void on_actionTopic_search_triggered();

    void on_actionFix_errors_triggered();
    std::vector<int> parseNumbers(const std::string& str, char delimiter = ',');
    std::string vectorToString(const std::vector<int>& vec, const std::string& delimiter=",");
private:
    Ui::MainWindow *ui;
    QString file_path;
    XMLHighlighter *highlighter;
};
#endif // MAINWINDOW_H
