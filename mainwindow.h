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
    int *arr;           //��ʼ����
    int *InsertArr;
    int *BInsertArr;
    int *ShellArr;
    int *BubbleArr;
    int *QuickArr;
    int *SelectArr;

    int arrSize;        //���ݸ���

    //������������е�����
    QString InsertStr;
    QString BInsertStr;
    QString ShellStr;
    QString BubbleStr;
    QString QuickStr;
    QString SelectStr;

    //ֱ�Ӳ��������ڲ�����
    int Inserti;
    int InsertTemp;     //���ڱ���

    //�۰���������ڲ�����
    int BInserti;
    int BInsertTemp;     //���ڱ���

    //ϣ�������ڲ�����
    int Shellk;
    int Shellt;
    int ShellTemp;      //���ڱ���

    //ð�������ڲ�����
    int Bubblei;
    bool BubbleChange;

    //���������ڲ�����
    SqQueue<interval> LHQueue;
    int QuickCount;     //����������

    //��ѡ�������ڲ�����
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
