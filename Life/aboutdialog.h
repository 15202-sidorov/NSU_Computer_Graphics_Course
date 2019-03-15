#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class AboutDialog : public QWidget
{
    Q_OBJECT
public:
    explicit AboutDialog(QWidget *parent = nullptr);
    ~AboutDialog();

signals:

public slots:

private:
    QLabel *about = new QLabel("Created by Sidorov Ilia, gr. 15202, year 2018");
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
};

#endif // ABOUTDIALOG_H
