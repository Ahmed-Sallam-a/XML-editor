#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QString>
#include "xmltojsonconverter.h"
#include "DrawGraph.h"
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

void MainWindow::on_actionSave_as_triggered() {
    // Open a "Save As" dialog
    QString filePath = QFileDialog::getSaveFileName(
        this,
        tr("Save As"),
        QDir::homePath(), // Starting directory
        tr("XML Files (*.xml);;All Files (*)") // File type filters
        );

    // Check if the user canceled the dialog
    if (filePath.isEmpty()) {
        return; // User canceled; do nothing
    }

    // Ensure the file has the .xml extension
    if (!filePath.endsWith(".xml", Qt::CaseInsensitive)) {
        filePath += ".xml";
    }

    // Check if the file already exists
    if (QFile::exists(filePath)) {
        // Ask the user for confirmation to overwrite
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(
            this,
            tr("Overwrite File"),
            tr("The file \"%1\" already exists.\nDo you want to overwrite it?")
                .arg(QDir::toNativeSeparators(filePath)),
            QMessageBox::Yes | QMessageBox::No,
            QMessageBox::No
            );

        if (reply != QMessageBox::Yes) {
            return; // User chose not to overwrite; abort saving
        }
    }

    QFile file(filePath);

    // Attempt to open the file for writing
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(
            this,
            tr("Error"),
            tr("Cannot open file for writing:\n%1.").arg(file.errorString())
            );
        return;
    }

    // Create a text stream to write to the file
    QTextStream out(&file);

    // Retrieve text from the QTextEdit widget
    QString text = ui->textEdit->toPlainText();

    // Write the text to the file
    out << text;

    // Flush and close the file
    file.flush();
    file.close();

    // Inform the user that the file was saved successfully
    QMessageBox::information(
        this,
        tr("Success"),
        tr("File \"%1\" has been saved successfully.").arg(QDir::toNativeSeparators(filePath))
        );
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


void MainWindow::on_actionConvert_to_png_triggered() {
    Graph socialNetwork;

    try {
        // Get the XML content from the text edit
        QString xmlContent = ui->textEdit->toPlainText();

        // Check if the text edit is empty
        if (xmlContent.isEmpty()) {
            QMessageBox::warning(this, tr("Warning"),
                                 tr("The text edit is empty. Please enter XML content."));
            return;
         }

        std::string xmlcontent_str = xmlContent.toStdString();
        parseXMLAndBuildGraph(xmlcontent_str, socialNetwork);
        socialNetwork.generateDOTFile("social_network.dot");
        QString filepath_png = QFileDialog::getSaveFileName(this, "Choose a file", "c://", "*.png");
        Graph::generatePNG("social_network.dot", filepath_png);
        }
     catch (const std::exception& e) {
       QMessageBox::critical(this, tr("Conversion Error"),
                                tr("Failed to convert XML: %1").arg(e.what()));
        }
}
