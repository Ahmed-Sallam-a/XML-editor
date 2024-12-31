#include "mainwindow.h"
#include "compressor.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QString>
#include "xmltojsonconverter.h"
#include "DrawGraph.h"
#include "xml_lib.h"
#include <QInputDialog>
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
QString MainWindow:: opens(QString type){
    QString filter = QString("%1 Files (*.%1);;All Files (*)").arg(type);
    file_path = QFileDialog::getOpenFileName(this, "Choose a file", "c://", filter);
    QFile file(file_path);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "File not found!");
        return "";
    }
    QTextStream in(&file);
    QString text =in.readAll();
    return text;
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
void MainWindow::saveas(QString text, QString type){
QString filter = QString("%1 Files (*.%1);;All Files (*)").arg(type);
QString filePath = QFileDialog::getSaveFileName(
    this,
    tr("Save As"),
    QDir::homePath(), // Starting directory
    filter // File type filters
    );

// Check if the user canceled the dialog
if (filePath.isEmpty()) {
    return; // User canceled; do nothing
}

// Ensure the file has the .xml extension
if (!filePath.endsWith(type, Qt::CaseInsensitive)) {
    filePath += type;
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
//QString text = ui->textEdit->toPlainText();

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
void MainWindow::on_actionCompress_triggered()
{
    QString inputText = ui->textEdit->toPlainText();
    if (inputText.isEmpty()) {
        QMessageBox::warning(this, "Input Required", "Please enter text to compress.");
        return;
    }

    std::string compressed = Compressor::compress(inputText.toStdString());
    QString qCompressed = QString::fromStdString(compressed);
    saveas(qCompressed,"comp");
    qDebug() << "Compression successful.";
}
void MainWindow::on_actionDecompress_triggered()
{   QString compressedText =opens("comp");
    if (compressedText.isEmpty()) {
        QMessageBox::warning(this, "Input Required", "Please enter compressed text to decompress.");
        return;
    }

    std::string decompressed = Compressor::decompress(compressedText.toStdString());
    QString qDecompressed = QString::fromStdString(decompressed);
    ui->textEdit->setPlainText(qDecompressed);

    qDebug() << "Decompression successful.";
}


void MainWindow::on_actionCheck_consistency_triggered()
{
    std::string Text=ui->textEdit->toPlainText().toStdString();
    std::string isfixed = checkXMLConsistencyGUI(Text,'c');
    if(isfixed.compare("The XML File is valid.")){
        QString message = "There are errors in lines: "+QString::fromStdString(isfixed);
        QMessageBox::warning(this, "Fixed errors",message);
    }else{
        QMessageBox::information(this, "No errors to fix", "The XML File is valid!");
    }
}


void MainWindow::on_actionPrettify_triggered()
{
    std::string Text=ui->textEdit->toPlainText().toStdString();
    std::string prettytext= prettifyXML(Text);
    ui->textEdit->setPlainText(QString::fromStdString(prettytext));
}


void MainWindow::on_action_Minify_triggered()
{
    std::string Text=ui->textEdit->toPlainText().toStdString();
    std::string minitext= minifyXMLFile(Text);
    ui->textEdit->setPlainText(QString::fromStdString(minitext));
}


void MainWindow::on_actionMost_Active_user_triggered()
{
    std::string Text=ui->textEdit->toPlainText().toStdString();
    parse_string(Text);
    std::pair<int, std::string> most_active = getMostActiveUser();
    QString mostActive = QString::fromStdString(most_active.second);
    QMessageBox::information(this, "Most Active User", "The most active user is: "+mostActive);


}


void MainWindow::on_actionMost_influencial_triggered()
{
    std::string Text=ui->textEdit->toPlainText().toStdString();
    parse_string(Text);
    std::pair<std::string, std::string> most_influencial = getMostInfluentialUser();
    QString mostinf = QString::fromStdString(most_influencial.second);
    QMessageBox::information(this, "Most Influencial User", "The most influencial user is: "+mostinf);
}


void MainWindow::on_actionMutual_followers_triggered()
{
    std::string Text=ui->textEdit->toPlainText().toStdString();
    parse_string(Text);
    QString userInput = QInputDialog::getText(this, "Mutual followers", "Enter list of users separted by commas: ", QLineEdit::Normal);
    std::vector<int> usersID=parseNumbers(userInput.toStdString());
    std::vector<int> IDS=getMutualFollowers(usersID);
    std::string out = "Mutual followers are: "+ vectorToString(IDS);
    QMessageBox::information(this, "Mutual followers",QString::fromStdString(out));



}
std::vector<int>MainWindow:: parseNumbers(const std::string& str, char delimiter) {
    std::vector<int> numbers;
    std::stringstream ss(str);
    std::string item;
    try {
        while (std::getline(ss, item, delimiter)) {
            // Remove whitespace
            item.erase(std::remove_if(item.begin(), item.end(),
                                      [](unsigned char c) { return std::isspace(c); }),
                       item.end());
            if (!item.empty()) {
                numbers.push_back(std::stoi(item));
            }
        }
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Invalid number format in input string" << std::endl;
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Number out of range in input string" << std::endl;
    }

    return numbers;
}
std::string MainWindow::vectorToString(const std::vector<int>& vec, const std::string& delimiter) {
    std::stringstream ss;
    for (size_t i = 0; i < vec.size(); ++i) {
        if (i != 0) {
            ss << delimiter;
        }
        ss << vec[i];
    }
    return ss.str();
}

void MainWindow::on_actionSuggest_followers_triggered()
{
    std::string Text=ui->textEdit->toPlainText().toStdString();
    parse_string(Text);
    QString userInput = QInputDialog::getText(this, "Suggested followers", "Enter the user id: ", QLineEdit::Normal);
    std::vector<int> usersID=parseNumbers(userInput.toStdString());
    if(usersID.size()>1){
        QMessageBox::warning(this, "Error!","enter one user id");
    }
    else{
    std::vector<int> IDS=suggestUsersToFollow(usersID[0]);
    std::string out = "Suggested users are: "+ vectorToString(IDS);
    QMessageBox::information(this, "Suggested followers",QString::fromStdString(out));
    }
    }


void MainWindow::on_actionWord_search_triggered()
{
    QString userInput = QInputDialog::getText(this, "Word search", "Enter a word:", QLineEdit::Normal);
    std::string searchResult=postSearch(false,
               ui->textEdit->toPlainText().toStdString(),
               userInput.toStdString(),
               true);
    if(!searchResult.substr(0,34).compare("No posts found containing the word")){
        QMessageBox::warning(this, "Warning!",QString::fromStdString(searchResult));
    }
    else
        ui->textEdit->setText(QString::fromStdString(searchResult));

}


void MainWindow::on_actionTopic_search_triggered()
{
    QString userInput = QInputDialog::getText(this, "Topic search", "Enter a topic: ", QLineEdit::Normal);
    std::string searchResult=postSearch(false,
                ui->textEdit->toPlainText().toStdString(),
                userInput.toStdString(),
                false);
    if(!searchResult.substr(0,35).compare("No posts found containing the topic")){
        QMessageBox::warning(this, "Warning!",QString::fromStdString(searchResult));
    }
    else
        ui->textEdit->setText(QString::fromStdString(searchResult));
}


void MainWindow::on_actionFix_errors_triggered()
{
    std::string Text=ui->textEdit->toPlainText().toStdString();
    std::string fixedText=checkXMLConsistencyGUI(Text,'f');
    if(fixedText.compare("The XML File is valid.")){
    ui->textEdit->setPlainText(QString::fromStdString(fixedText));
        QString message = "fixed errors in lines: "+QString::fromStdString(checkXMLConsistencyGUI(Text,'c'));
        QMessageBox::information(this, "Fixed errors",message);
    }else{
         QMessageBox::information(this, "No errors to fix", "The XML File is valid!");
    }
}

