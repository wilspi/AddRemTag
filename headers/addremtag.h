// AddRemTag Class Defination

#ifndef ADDREMTAG_H
#define ADDREMTAG_H

#include <QDialog>

class QLabel;
class QLineEdit;
class QPushButton;
class QString;
class QDir;
class QToolButton;
class QTextEdit;
class QRadioButton;
class QGroupBox;
class QFile;
class QCheckBox;
class QComboBox;

class AddRemTag : public QDialog
{
    Q_OBJECT

public :
    explicit AddRemTag(QWidget *parent =0);

signals :

private slots :
    void textChanged(QString txt);
    void search();
    void addTags();
    void removeTags();
    void browse();
    void about();
    void settings();
    void extShow1(bool);
    void extShow2(bool);
    void help();

private :
    QLabel *dirAdLabel;
    QPushButton * addButton;
    QPushButton *searchButton;
    QLineEdit *dirAddress;
    QLabel *tagLabel;
    QPushButton * removeButton;
    //QLineEdit *tagName;
    QComboBox *tagName;
    QPushButton *closeButton;
    QPushButton *browseFiles;
    QGroupBox *groupBox;
    QRadioButton *addStart;
    QRadioButton *addEnd;
    QCheckBox *folderBox;
    QCheckBox *onlyFolder;
    QPushButton *aboutButton;
    QPushButton *more;
    QPushButton *settingButton;
    QWidget *extensionMoreOption;
    QWidget *extensionSettingOption;
    QCheckBox *alwaysTop;
    QCheckBox *saveTags;
    QPushButton *ok;
    QPushButton *helpButton;

    QLabel *status;
    QTextEdit *value;

    QStringList findTags(QDir dir,QString tg);
    QStringList allFiles(QDir dir,QString tg);
    void dropDownText();
    void saveTagsFile(QString tg);
    void changeStatus(const QString & text);
    void addToTagList(const QString & tag);

    Qt::WindowFlags flags;
};


#endif // ADDREMTAG_H
