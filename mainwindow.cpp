#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QString>
#include "xmltojsonconverter.cpp"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
    highlighter = new XMLHighlighter(ui->textEdit->document());
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_actionNew_triggered()
{
    file_path = "";
    ui->textEdit->setText("");
}

void MainWindow::on_actionOpen_triggered()
{
    file_path = QFileDialog::getOpenFileName(this, "Choose a file", "c://", "*.xml");
    QFile file(file_path);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "File not found!");
        return;
    }
    QTextStream in(&file);
    QString text =in.readAll();
    ui->textEdit->setText(text);
}

void MainWindow::on_actionSave_triggered()
{
    QFile file(file_path);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Couldn't access the file");
        return;
    }
    QTextStream out(&file);
    QString text =ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();

}

void MainWindow::on_actionSave_as_triggered()
{
    file_path = QFileDialog::getOpenFileName(this, "Choose a file", "c://", "*.xml");
    QFile file(file_path);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Couldn't access the file");
        return;
    }
    QTextStream out(&file);
    QString text =ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();

}


void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionconvert_to_jason_triggered()
{
    try {
        // Get the XML content from the text edit
        QString xmlContent = ui->textEdit->toPlainText();

        // Check if the text edit is empty
        if (xmlContent.isEmpty()) {
            QMessageBox::warning(this, tr("Warning"),
                                 tr("The text edit is empty. Please enter XML content."));
            return;
        }

        // Create converter instance


        // Convert to JSON
        std::string jsonStr = XmlToJsonConverter::convert(xmlContent.toStdString());

        // Create a new text edit or use existing one for JSON output
        ui->textEdit->clear();
        ui->textEdit->setPlainText(QString::fromStdString(jsonStr));

        // Optional: Show success message
        QMessageBox::information(this, tr("Success"),
                                 tr("XML successfully converted to JSON!"));
    }
    catch (const std::exception& e) {
        QMessageBox::critical(this, tr("Conversion Error"),
                              tr("Failed to convert XML: %1").arg(e.what()));
    }

}

