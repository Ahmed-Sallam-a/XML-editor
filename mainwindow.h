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

private:
    Ui::MainWindow *ui;
    QString file_path;
    XMLHighlighter *highlighter;
};
#endif // MAINWINDOW_H
