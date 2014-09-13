//GUI and Functions Implementation

#include "../headers/addremtag.h"
#include <QLabel>
#include <QDebug>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDir>
#include <QToolButton>
#include <QFileDialog>
#include <QTextEdit>
#include <QColor>
#include <QMessageBox>
#include <QProgressDialog>
#include <QRadioButton>
#include <QGroupBox>
#include <QCheckBox>
#include <QComboBox>
#include <QScrollArea>
#include <QCompleter>

AddRemTag::AddRemTag(QWidget *parent) :
    QDialog(parent)
{
    dirAdLabel = new QLabel(tr("Directory Address : "));
    dirAddress = new QLineEdit();
    dirAdLabel->setBuddy(dirAddress);

    tagLabel = new QLabel(tr("Tag : "));

    tagName = new QComboBox();
    QCompleter *completer = new QCompleter(tagName->model());
    completer->setCaseSensitivity(Qt::CaseSensitive);
    tagName->setEditable(true);
    tagName->setCompleter(completer);
    tagName->setMaxVisibleItems(10);
    tagName->setInsertPolicy(QComboBox::InsertAlphabetically);
    tagName->setDuplicatesEnabled(false);
    tagName->addItem("");
    tagLabel->setBuddy(tagName);

    searchButton = new QPushButton(tr("Search Files"));
    searchButton->setDefault(true);
    searchButton->setEnabled(false);

    addButton = new QPushButton(tr("Add Tag"));
    addButton->setEnabled(false);

    removeButton = new QPushButton(tr("Remove Tag"));
    removeButton->setEnabled(false);

    settingButton = new QPushButton(tr("Settings"));
    settingButton->setCheckable(true);

    status = new QLabel(tr("Current Status : "));
    value = new QTextEdit(tr(""));
    value->setReadOnly(true);

    folderBox = new QCheckBox(tr("Check Folders also"));
    folderBox->setChecked(false);
    folderBox->setEnabled(false);

    onlyFolder = new QCheckBox(tr("Only Folders"));
    onlyFolder->setChecked(false);
    onlyFolder->setEnabled(false);

    groupBox = new QGroupBox(tr("Select"));

    addStart = new QRadioButton(tr("Add at Start"));
    addEnd = new QRadioButton(tr("Add at End"));
    addEnd->setChecked(true);

    aboutButton = new QPushButton(tr("&About"));
    helpButton = new QPushButton(tr("&Help"));
    more = new QPushButton(tr("&More"));
    more->setCheckable(true);
    extensionMoreOption = new QWidget();

    QVBoxLayout *boxLay = new QVBoxLayout();
    boxLay->addWidget(addStart);
    boxLay->addWidget(addEnd);
    boxLay->addStretch(1);
    groupBox->setLayout(boxLay);
    groupBox->setEnabled(false);
    //groupBox->setFlat(true);

    alwaysTop = new QCheckBox(tr("Always on Top"));
    saveTags = new QCheckBox(tr("Save Tags Used"));
    ok = new QPushButton(tr("Ok"));

    extensionSettingOption = new QWidget();
    dropDownText();

    browseFiles = new QPushButton(tr("browse"));

    closeButton = new QPushButton(tr("Close"));

    connect(browseFiles,SIGNAL(clicked()),this,SLOT(browse()));
    connect(closeButton,SIGNAL(clicked()),this,SLOT(close()));
    connect(dirAddress,SIGNAL(textChanged(QString)),this,SLOT(textChanged(QString)));
    connect(tagName,SIGNAL(currentTextChanged(QString)),this,SLOT(textChanged(QString)));
    connect(addButton,SIGNAL(clicked()),this,SLOT(addTags()));
    connect(removeButton,SIGNAL(clicked()),this,SLOT(removeTags()));
    connect(searchButton,SIGNAL(clicked()),this,SLOT(search()));
    connect(aboutButton,SIGNAL(clicked()),this,SLOT(about()));
    connect(helpButton,SIGNAL(clicked()),this,SLOT(help()));
    connect(settingButton,SIGNAL(toggled(bool)),this,SLOT(extShow2(bool)));
    connect(more,SIGNAL(toggled(bool)),this,SLOT(extShow1(bool)));
    connect(ok,SIGNAL(clicked()),this,SLOT(settings()));

    QHBoxLayout *layoutDir = new QHBoxLayout();
    layoutDir->addWidget(dirAdLabel);
    layoutDir->addWidget(dirAddress);
    layoutDir->addWidget(browseFiles);

    QHBoxLayout *layoutButton = new QHBoxLayout();
    layoutButton->addWidget(addButton);
    layoutButton->addWidget(removeButton);
    layoutButton->addWidget(more);
    layoutButton->addWidget(settingButton);
    //layoutButton->addStretch(15);
    //layoutButton->addWidget(closeButton);

    QHBoxLayout *layoutTag = new QHBoxLayout();
    layoutTag->addWidget(tagLabel);
    layoutTag->addWidget(tagName);
    layoutTag->addWidget(searchButton);

    QHBoxLayout *layoutMoreFolder =new QHBoxLayout();
    layoutMoreFolder->addWidget(folderBox);
    layoutMoreFolder->addWidget(onlyFolder);

    QVBoxLayout *layoutSettingOptions = new QVBoxLayout();
    layoutSettingOptions->addWidget(alwaysTop);
    layoutSettingOptions->addWidget(saveTags);

    QHBoxLayout *layoutSetting = new QHBoxLayout();
    layoutSetting->addLayout(layoutSettingOptions);
    layoutSetting->addWidget(ok);
    extensionSettingOption->setLayout(layoutSetting);

    QVBoxLayout *layoutMore = new QVBoxLayout();
    layoutMore->addLayout(layoutMoreFolder);
    layoutMore->addWidget(groupBox);
    extensionMoreOption->setLayout(layoutMore);

    QVBoxLayout *layoutStatus = new QVBoxLayout();
    layoutStatus->addWidget(status);
    layoutStatus->addWidget(value);

    QHBoxLayout *layoutBottom = new QHBoxLayout();
    layoutBottom->addWidget(aboutButton);
    layoutBottom->addWidget(helpButton);
    layoutBottom->addWidget(closeButton);

    QHBoxLayout *layoutDropDown= new QHBoxLayout();
    layoutDropDown->addWidget(extensionMoreOption);
    layoutDropDown->addWidget(extensionSettingOption);

    QVBoxLayout *layoutOut = new QVBoxLayout();
    layoutOut->addLayout(layoutDir);
    layoutOut->addLayout(layoutTag);
    layoutOut->addLayout(layoutButton);
    layoutOut->addLayout(layoutDropDown);
    layoutOut->addLayout(layoutStatus);
    layoutOut->addLayout(layoutBottom);

    setLayout(layoutOut);

    setWindowTitle(tr("AddRemTag"));
    setWindowIcon(QIcon(":/files/resources/icono.png"));
    setWindowFlags(Qt::WindowMinimizeButtonHint);
    setFixedHeight(sizeHint().height()-30);
    setFixedWidth(sizeHint().width()-130);
    extensionMoreOption->hide();
    extensionSettingOption->hide();

    Qt::WindowFlags flags = this->windowFlags();
}

void AddRemTag::textChanged(QString txt)
{
    addButton->setEnabled((!dirAddress->text().isEmpty())&&(!tagName->currentText().isEmpty()));
    removeButton->setEnabled((!dirAddress->text().isEmpty())&&(!tagName->currentText().isEmpty()));
    searchButton->setEnabled((!dirAddress->text().isEmpty())&&(!tagName->currentText().isEmpty()));
    groupBox->setEnabled((!dirAddress->text().isEmpty())&&(!tagName->currentText().isEmpty()));
    folderBox->setEnabled((!dirAddress->text().isEmpty())&&(!tagName->currentText().isEmpty()));
    onlyFolder->setEnabled((!dirAddress->text().isEmpty())&&(!tagName->currentText().isEmpty()));
    if((!dirAddress->text().isEmpty())&&(!tagName->currentText().isEmpty()))
    {
        value->setTextColor(QColor::fromRgb(255,0,0));
        value->setText("Press <Enter> to Search");
    }
    else
        value->setText("");
}

void AddRemTag::changeStatus(const QString & text)
{
    value->clear();
    value->setTextColor(QColor::fromRgb(255,0,80));
    value->setText(text);
}

void AddRemTag::search()
{
    changeStatus("Searching...");  //TODO multithreading

    QStringList tagsList;

    QString tg = tagName->currentText();
    if(tagName->findText(tg, Qt::MatchCaseSensitive)==-1)
    {
        //tagName->setInsertPolicy(QComboBox::InsertAlphabetically);
        tagName->addItem(tg);
        if(saveTags->isChecked())
            saveTagsFile(tg);
    }

    QDir dir(dirAddress->text());
    if(dir.exists())
    {
        tagsList = findTags(dir,tg);
        if(!tagsList.isEmpty())
        {
            value->setTextColor(QColor::fromRgb(255,0,80));
            //value->setTextBackgroundColor(QColor(0,0,180,100));
            if(onlyFolder->isChecked())
            {    value->setText("■■■  FOLDERS WITH "+tg+" TAG  ■■■");}
            else
            {
                if(folderBox->isChecked())
                    value->setText("■■■  FILES/FOLDERS WITH "+tg+" TAG  ■■■");
                else
                    value->setText("■■■  FILES WITH "+tg+" TAG  ■■■");
            }
            value->setTextColor(QColor::fromRgb(0,0,0));
            value->setTextBackgroundColor(QColor(255,255,255));
            foreach(QFileInfo file , tagsList)
            {
                if(file.isFile())
                {
                    value->append("◉ "+file.completeBaseName().simplified());
                }
                if(file.isDir())
                {
                    value->setTextColor(QColor::fromRgb(0,0,255));
                    value->append("◎ "+file.completeBaseName().simplified()+"");
                    value->setTextColor(QColor::fromRgb(0,0,0));
                }
            }
        }
        else
        {
            value->setTextColor(QColor::fromRgb(255,0,80));
            if(onlyFolder->isChecked())
                value->setText("■  NO FOLDER WITH "+tg+" TAG FOUND  ■");
            else
            {
                if(folderBox->isChecked())
                    value->setText("■  NO FILE/FOLDER WITH "+tg+" TAG FOUND  ■");
                else
                    value->setText("■  NO FILE WITH "+tg+" TAG FOUND  ■");
            }
        }
    }
    else
    {
        value->setTextColor(QColor::fromRgb(255,0,0));
        value->setText("☠ Directory doesn't exist ☠");
    }
}

void AddRemTag::addTags()
{
    changeStatus("⌛ Adding...");

    QStringList tagsList;

    QString tg = tagName->currentText();
    if(tagName->findText(tg)==-1)
    {
        tagName->addItem(tg);
        if(saveTags->isChecked())
            saveTagsFile(tg);
    }

    QDir dir(dirAddress->text());
    if(dir.exists())
    {
        tagsList = allFiles(dir,tg);
        if(!tagsList.isEmpty())
        {
            value->setTextColor(QColor::fromRgb(255,0,80));
            if(onlyFolder->isChecked())
                value->setText("■■■  FOLDERS ADDED WITH "+tg+" TAG  ■■■");
            else
            {
                if(folderBox->isChecked())
                    value->setText("■■■  FILES/FOLDERS ADDED WITH "+tg+" TAG  ■■■");
                else
                    value->setText("■■■  FILES ADDED WITH "+tg+" TAG  ■■■");
            }
            value->setTextColor(QColor::fromRgb(0,0,0));
            foreach(QFileInfo file , tagsList)
            {                
                if(file.isFile())
                {
                    value->append("◉ "+file.completeBaseName().simplified());

                    int f= file.suffix().size()+1;
                    if(addEnd->isChecked())
                        dir.rename(file.absoluteFilePath(), (file.absolutePath()+"/"+file.fileName().remove(file.fileName().size()-f,f)+(tg)+"."+file.suffix()));
                    else
                        dir.rename(file.absoluteFilePath(), (file.absolutePath()+"/"+(tg)+file.fileName().remove(file.fileName().size()-f,f)+"."+file.suffix()));
                }
                if(file.isDir())
                {
                    value->setTextColor(QColor::fromRgb(0,0,125));
                    value->append("◎ "+file.completeBaseName().simplified()+"");
                    value->setTextColor(QColor::fromRgb(0,0,0));

                    if(addEnd->isChecked())
                        dir.rename(file.absoluteFilePath(), (file.absolutePath()+"/"+file.fileName()+(tg)));
                    else
                        dir.rename(file.absoluteFilePath(), (file.absolutePath()+"/"+(tg)+file.fileName()));
                }
            }
        }
        else
        {
            value->setTextColor(QColor::fromRgb(255,0,80));
            if(onlyFolder->isChecked())
                value->setText("■  NO FOLDER WITH "+tg+" TAG FOUND  ■");
            else
            {
                if(folderBox->isChecked())
                    value->setText("■  NO FILE/FOLDER WITH "+tg+" TAG FOUND  ■");
                else
                    value->setText("■  NO FILE WITH "+tg+" TAG FOUND  ■");
            }
        }
    }
    else
    {
        value->setTextColor(QColor::fromRgb(255,0,0));
        value->setText("☠ Directory doesn't exist ☠");
    }
}

void AddRemTag::removeTags()
{
    changeStatus("⌛ Removing...");

    QStringList tagsList;

    QString tg = tagName->currentText();
    if(tagName->findText(tg)==-1)
    {
        tagName->addItem(tg);
        if(saveTags->isChecked())
            saveTagsFile(tg);
    }

    QDir dir(dirAddress->text());
    if(dir.exists())
    {
        tagsList = findTags(dir,tg);

        if(!tagsList.isEmpty())
        {
            value->setTextColor(QColor::fromRgb(255,0,0));
            if(onlyFolder->isChecked())
                value->setText("■■■  FOLDERS WITH REMOVED "+tg+" TAG  ■■■");
            else
            {
                if(folderBox->isChecked())
                    value->setText("■■■  FILES/FOLDERS WITH REMOVED "+tg+" TAG  ■■■");
                else
                    value->setText("■■■  FILES WITH REMOVED "+tg+" TAG  ■■■");
            }
            value->setTextColor(QColor::fromRgb(0,0,0));
            foreach(QFileInfo file , tagsList)
            {
                if(file.isFile())
                {
                    value->append("◉ "+file.completeBaseName().simplified());

                    int f = file.suffix().size()+1;
                    dir.rename(file.absoluteFilePath(), (file.absolutePath()+"/"+file.fileName().remove(file.fileName().size()-f,f).remove(tg)+"."+file.suffix()));
                }
                if(file.isDir())
                {
                    value->setTextColor(QColor::fromRgb(0,0,125));
                    value->append("◎ "+file.completeBaseName().simplified()+"");
                    value->setTextColor(QColor::fromRgb(0,0,0));

                    dir.rename(file.absoluteFilePath(), (file.absolutePath()+"/"+file.fileName().remove(tg)));
                }
            }
        }
        else
        {
            value->setTextColor(QColor::fromRgb(255,0,80));
            if(onlyFolder->isChecked())
                value->setText("■  NO FOLDER WITH "+tg+" TAGS FOUND  ■");
            else
            {
                if(folderBox->isChecked())
                    value->setText("■  NO FILE/FOLDER WITH "+tg+" TAG FOUND  ■");
                else
                    value->setText("■  NO FILE WITH "+tg+" TAG FOUND  ■");
            }
        }
    }
    else
    {
        value->setTextColor(QColor::fromRgb(255,0,0));
        value->setText("☠ Directory doesn't exist ☠");
    }
}

QStringList AddRemTag::findTags(QDir dir,QString tg)
{
    QStringList tagsList;

    QFileInfoList ls =dir.entryInfoList();
    for(int i=2; i< ls.size();i++)
    {
        QFileInfo file = ls.at(i);
        if((file.isFile())&&(!onlyFolder->isChecked()))
        if(((file.completeBaseName().simplified().contains(tg,Qt::CaseSensitive))))
        {            
            tagsList.append(file.canonicalFilePath());
        }

        if(file.isDir())
        {
            if(file.canonicalFilePath()==file.filePath())
                  tagsList.append(findTags(QDir(file.canonicalFilePath()),tg));

            if(folderBox->isChecked()||onlyFolder->isChecked())
            if(((file.completeBaseName().simplified().contains(tg,Qt::CaseSensitive))))
            {
                tagsList.append(file.canonicalFilePath());
            }
        }
    }
    return tagsList;
}

QStringList AddRemTag::allFiles(QDir dir,QString tg)
{
    QStringList tagsList;

    //dir.setFilter(QDir::NoDotAndDotDot);
    QFileInfoList ls =dir.entryInfoList();
    for(int i=2; i< ls.size();i++)
    {
        QFileInfo file = ls.at(i);
        if((file.isFile())&&(!onlyFolder->isChecked()))
        {
           tagsList.append(file.canonicalFilePath());
        }
        if(file.isDir())
        {
            if(file.canonicalFilePath()==file.filePath())
                  tagsList.append(allFiles(QDir(file.canonicalFilePath()),tg));

            if(folderBox->isChecked()||onlyFolder->isChecked())
            {
                tagsList.append(file.canonicalFilePath());
            }
        }
    }
    return tagsList;
}

void AddRemTag::browse()
{
    browseFiles->setEnabled(false);
    if(dirAddress->text().isEmpty())
        dirAddress->setText("\\home");
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),dirAddress->text(),QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
    if(!dir.isEmpty())
        dirAddress->setText(dir);
    browseFiles->setEnabled(true);
}

void AddRemTag::about()
{
    QDialog *msgBox = new QDialog(this);
    QLabel *aboutText = new QLabel(tr("<h3>AddRemTag</h3>"
                                "Version 1.1"
                                "<p>AddRemTag is a Qt based app for easy <b>adding and removing tags</b><br> to large number of files instantly.</p>"
                                "<p>Author - Sourabh Deokar<br>"
                                "Send your feedbacks - <a href='mailto:sourabhdeokar@gmail.com'>sourabhdeokar@gmail.com</a></p>"),msgBox);
    QPushButton *close = new QPushButton(tr("Close"),msgBox);
    close->setMinimumWidth(1);

    QLabel *img = new QLabel(msgBox);
    QPixmap ig;
    ig = QPixmap(":/files/resources/ws_creations.png");
    img->setPixmap(ig.scaledToWidth(220));

    connect(close,SIGNAL(clicked()),msgBox,SLOT(close()));

    QHBoxLayout *lj =new QHBoxLayout();
    lj->addSpacing(100);
    lj->addWidget(close);
    lj->addSpacing(300);

    QVBoxLayout *layoutRightSide = new QVBoxLayout();
    layoutRightSide->addWidget(aboutText);
    layoutRightSide->addLayout(lj);

    QHBoxLayout *layoutAbout = new QHBoxLayout();
    layoutAbout->addWidget(img);
    layoutAbout->addLayout(layoutRightSide);

    msgBox->setLayout(layoutAbout);
    msgBox->setWindowTitle(tr("About AddRemTag"));
    msgBox->setFixedHeight(230);
    msgBox->setFixedWidth(sizeHint().width()+400);

    msgBox->exec();
}

void AddRemTag::settings()
{
    if(alwaysTop->isChecked())
    {
         this->setWindowFlags(flags |  Qt::WindowStaysOnTopHint);
         this->show();
    }
    else
    {
        this->setWindowFlags(flags);
        this->show();
    }

    if(saveTags->isChecked())
    {
        QFile fl (QDir::currentPath().append("/user/preferences.sett"));
        if(fl.open(QFile::Append|QFile::Text))
        {
            QTextStream out(&fl);
            out<< "6541" << "\n";
            fl.flush();
            fl.close();
        }
    }
    else
    {
        QFile fl (QDir::currentPath().append("/user/preferences.sett"));
        fl.remove();
        fl.close();
        QFile file (QDir::currentPath().append("/user/tgList.sett"));
        file.remove();
        file.close();
    }

}

void AddRemTag::extShow1(bool)
{
    if (more->isChecked())
    {
        settingButton->setChecked(false);
        extensionMoreOption->setVisible(true);
        extensionSettingOption->setVisible(false);
    }
    else
    {
        extensionMoreOption->setVisible(false);
        extensionSettingOption->setVisible(false);
    }
}

void AddRemTag::extShow2(bool)
{
        if (settingButton->isChecked())
        {
            more->setChecked(false);
            extensionMoreOption->setVisible(false);
            extensionSettingOption->setVisible(true);
        }
        else
        {
            extensionMoreOption->setVisible(false);
            extensionSettingOption->setVisible(false);
        }

}

void AddRemTag::help()
{
     QDialog *msgBox =  new QDialog(this);
     QLabel *lb1 = new QLabel(tr("<h2>AddRemTag - v1.1</h2>"),msgBox);
     QLabel *lb3 = new QLabel(tr("\n"
                                 "For any more queries/suggestions mail me @ <a href='mailto:sourabhdeokar@gmail.com'>sourabhdeokar@gmail.com</a>"),msgBox);
     QPushButton *close = new QPushButton(tr("Close"),msgBox);
     connect(close,SIGNAL(clicked()),msgBox,SLOT(close()));
     //close->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
     //close->adjustSize();

     QLabel *img = new QLabel(msgBox);
     img->setPixmap(QPixmap(":/files/resources/help.jpg"));

     QScrollArea *scroll = new QScrollArea();
     //scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded); //if Image doesnt fit in width
     scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
     scroll->setParent(msgBox);
     scroll->setWidget(img);
     scroll->setVisible(true);

     QHBoxLayout *lj =new QHBoxLayout();
     lj->addSpacing(250);
     lj->addWidget(close);
     lj->addSpacing(250);

     QVBoxLayout *layoutHelp = new QVBoxLayout();
     layoutHelp->addWidget(lb1);
     layoutHelp->addWidget(scroll);
     layoutHelp->addWidget(lb3);
     layoutHelp->addLayout(lj);

     msgBox->setLayout(layoutHelp);
     msgBox->setWindowTitle(tr("Help"));
     msgBox->setFixedHeight(600);
     //msgBox->setFixedWidth(sizeHint().width()+270);
     msgBox->setFixedWidth(620);

     msgBox->exec();
}

void AddRemTag::dropDownText()
{
    QFile file (QDir::currentPath().append("/user/tgList.sett"));
    if(file.open(QFile::ReadOnly|QFile::Text))
    {
        //QTextStream in(&file);
        if(!file.atEnd())
        {
            QTextStream in(&file);
            while(!in.atEnd())
            {
                QString fil(in.readLine());
                tagName->addItem(fil);
            }
        }
        file.close();        
    }

    QFile fl (QDir::currentPath().append("/user/preferences.sett"));
    if(fl.open(QFile::ReadOnly|QFile::Text))
    {
        //QTextStream in(&file);
        if(!fl.atEnd())
        {
            QTextStream in(&fl);
            QString fil(in.readLine());
            if(fil=="6541")
                saveTags->setChecked(true);
        }
        fl.close();
    }
}

void AddRemTag::saveTagsFile(QString tg)
{
    QFile fl (QDir::currentPath().append("/user/tgList.sett"));
    if(fl.open(QFile::Append|QFile::Text))
    {
        QTextStream out(&fl);
        out<< tg << "\n";
        fl.flush();
        fl.close();
    }
}
