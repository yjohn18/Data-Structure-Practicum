#pragma execution_character_set("utf-8")
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sqstack.h"

namespace Ui {
class MainWindow;
}

const int MAX_ARR = 20;

struct interval{
    int low;
    int high;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int *arr;           //初始数据
    int *InsertArr;
    int *BInsertArr;
    int *ShellArr;
    int *BubbleArr;
    int *QuickArr;
    int *SelectArr;

    int arrSize;        //数据个数

    //各排序输出框中的内容
    QString InsertStr;
    QString BInsertStr;
    QString ShellStr;
    QString BubbleStr;
    QString QuickStr;
    QString SelectStr;

    //直接插入排序内部变量
    int Inserti;
    int InsertTemp;     //“哨兵”

    //折半插入排序内部变量
    int BInserti;
    int BInsertTemp;     //“哨兵”

    //希尔排序内部变量
    int Shellk;
    int Shellt;
    int ShellTemp;      //“哨兵”

    //冒泡排序内部变量
    int Bubblei;
    bool BubbleChange;

    //快速排序内部变量
    SqQueue<interval> LHQueue;
    int QuickCount;     //趟数计数器

    //简单选择排序内部变量
    int Selecti;


private slots:
    void on_SortButton_clicked();
    void on_InsertBtn_clicked();
    void on_BInsertBtn_clicked();
    void on_ShellBtn_clicked();
    void on_BubbleBtn_clicked();
    void on_QuickBtn_clicked();
    void on_SelectBtn_clicked();
    void on_InsertBtn2_clicked();
    void on_BInsertBtn2_clicked();
    void on_ShellBtn2_clicked();
    void on_BubbleBtn2_clicked();
    void on_QuickBtn2_clicked();
    void on_SelectBtn2_clicked();
};

#endif // MAINWINDOW_H
