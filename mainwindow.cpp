#include "mainwindow.h"
#include "ui_mainwindow.h"

int QStrtoArray(const QString &str, int *arr);
void ArrtoQStr(QString &str, int *arr, int n);
int Partition (int *arr, int low, int high);
int SelectMin(int *arr, int low, int high);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    arr = new int[MAX_ARR];
    InsertArr = new int[MAX_ARR];
    BInsertArr = new int[MAX_ARR];
    ShellArr = new int[MAX_ARR];
    BubbleArr = new int[MAX_ARR];
    QuickArr = new int[MAX_ARR];
    SelectArr = new int[MAX_ARR];
}

MainWindow::~MainWindow()
{
    delete ui;
    delete [] arr;
    delete [] InsertArr;
    delete [] BInsertArr;
    delete [] ShellArr;
    delete [] BubbleArr;
    delete [] QuickArr;
    delete [] SelectArr;
}

void MainWindow::on_SortButton_clicked()
{
    QString strout;
    arrSize = QStrtoArray(ui->InEdit->toPlainText().simplified(), arr);
    if (ui->InEdit->toPlainText().isEmpty()){
        ui->prompt->setText("����Ϊ�գ�����������2-20�����Ǹ����������Կո�ָ�");
        return;
    }
    else if (arrSize <= 1) {
        ui->prompt->setText("�Ƿ����룡����������2-20�����Ǹ����������Կո�ָ�");
        return;
    }
    else {
        ui->prompt->setText("��ʼ�������óɹ���");
    }
    ArrtoQStr(strout, arr, arrSize);

    memcpy(InsertArr, arr, sizeof(int) * unsigned(arrSize));
    memcpy(BInsertArr, arr, sizeof(int) * unsigned(arrSize));
    memcpy(ShellArr, arr, sizeof(int) * unsigned(arrSize));
    memcpy(BubbleArr, arr, sizeof(int) * unsigned(arrSize));
    memcpy(QuickArr, arr, sizeof(int) * unsigned(arrSize));
    memcpy(SelectArr, arr, sizeof(int) * unsigned(arrSize));

    //��ʼ��ֱ�Ӳ�������
    Inserti = 1;

    //��ʼ���۰��������
    BInserti = 1;

    //��ʼ��ϣ������
    Shellt = int(log(arrSize + 1) / log(2));
    Shellk = 0;

    //��ʼ��ð������
    Bubblei = arrSize - 1;
    BubbleChange = true;

    //��ʼ����������
    interval itv;
    while (LHQueue.QueueEmpty() != 1)
        LHQueue.DeQueue(itv);   //��ն���
    itv.low = 0;
    itv.high = arrSize - 1;
    LHQueue.EnQueue(itv);
    //���һ�˵�ĩβ
    itv.low = -1;
    itv.high = -1;
    LHQueue.EnQueue(itv);
    QuickCount = 1;

    //��ʼ����ѡ������
    Selecti = 0;

    InsertStr = "��ʼ����:\t";
    InsertStr.append(strout);
    BInsertStr = "��ʼ����:\t";
    BInsertStr.append(strout);
    ShellStr = "��ʼ����:\t";
    ShellStr.append(strout);
    BubbleStr = "��ʼ����:\t";
    BubbleStr.append(strout);
    QuickStr = "��ʼ����:\t";
    QuickStr.append(strout);
    SelectStr = "��ʼ����:\t";
    SelectStr.append(strout);

//    ui->OutEdit->setPlainText(strout);
    ui->InsertTxt->setPlainText(InsertStr);
    ui->BInsertTxt->setPlainText(InsertStr);
    ui->ShellTxt->setPlainText(InsertStr);
    ui->BubbleTxt->setPlainText(InsertStr);
    ui->QuickTxt->setPlainText(InsertStr);
    ui->SelectTxt->setPlainText(InsertStr);

    ui->InsertBtn->setEnabled(true);
    ui->BInsertBtn->setEnabled(true);
    ui->ShellBtn->setEnabled(true);
    ui->BubbleBtn->setEnabled(true);
    ui->QuickBtn->setEnabled(true);
    ui->SelectBtn->setEnabled(true);
    ui->InsertBtn2->setEnabled(true);
    ui->BInsertBtn2->setEnabled(true);
    ui->ShellBtn2->setEnabled(true);
    ui->BubbleBtn2->setEnabled(true);
    ui->QuickBtn2->setEnabled(true);
    ui->SelectBtn2->setEnabled(true);

    //disable�ı���
//    ui->OutEdit->setEnabled(true);
    ui->InsertTxt->setEnabled(true);
    ui->BInsertTxt->setEnabled(true);
    ui->ShellTxt->setEnabled(true);
    ui->BubbleTxt->setEnabled(true);
    ui->QuickTxt->setEnabled(true);
    ui->SelectTxt->setEnabled(true);

    ui->SortButton->setText("��������");
}

//Ϊָ��arr����ռ䣬�����ַ���strת��Ϊ��������
//�����г����ֺͿո�������ַ�������ֹ��������false
int QStrtoArray(const QString &str, int *arr)
{
    int i, j;
//    int temp = 0;
    QString tempstr;
    bool ok;
    for (i = 0, j = 0; i < str.size(); ++i) {
        if (str[i].toLatin1() >= '0' && str[i].toLatin1() <= '9')
//            temp = temp * 10 + int(str[i].unicode() - '0');
            tempstr.append(str[i].toLatin1());
        else if (str[i].toLatin1() == ' ') {
            arr[j++] = tempstr.toInt(&ok);
//            temp = 0;
            if (!ok || j >= MAX_ARR)    //ת��ʧ�ܻ����ֹ��࣬����0
                return 0;
            tempstr.clear();
        }
        else
            return 0;   //�����г����ֺͿո�������ַ����򷵻�0
    }
//    arr[j++] = temp;
    arr[j++] = tempstr.toInt(&ok);
    return j;
}

//����ת��Ϊ�ַ���
void ArrtoQStr(QString &str, int *arr, int n)
{
    QString temp;
    str.clear();
    for (int i = 0; i < n; ++i) {
        temp = QString::number(arr[i],10);
        str.append(temp);
        str.append(' ');
    }
}

//��һ��ֱ�Ӳ�������
#if 0   //ԭ������ֻ��ʾ��һ�˺͵�ǰ���
void MainWindow::on_InsertBtn_clicked()
{
    int j;
    QString str, tempstr;
    ArrtoQStr(tempstr, InsertArr, arrSize);
    str = "��һ��:\t";
    str.append(tempstr);
    str.append("\n��ǰ:\t");

    if(InsertArr[Inserti] < InsertArr[Inserti - 1]){
        InsertTemp = InsertArr[Inserti];
        InsertArr[Inserti] = InsertArr[Inserti - 1];
        for (j = Inserti - 2; InsertTemp < InsertArr[j]; --j) {
            InsertArr[j + 1] = InsertArr[j];
        }
        InsertArr[j + 1] = InsertTemp;
    }

    ArrtoQStr(tempstr, InsertArr, arrSize);
    str.append(tempstr);
    if (++Inserti >= arrSize){
        ui->InsertBtn->setEnabled(false);
        str.append("\n������ɣ�");
    }
    ui->InsertTxt->setPlainText(str);
}
#else   //�·�����������ʾ������ʷ
void MainWindow::on_InsertBtn_clicked()
{
    int j;
    QString tempstr;
    ArrtoQStr(tempstr, InsertArr, arrSize);

    if(InsertArr[Inserti] < InsertArr[Inserti - 1]){
        InsertTemp = InsertArr[Inserti];
        InsertArr[Inserti] = InsertArr[Inserti - 1];
        for (j = Inserti - 2; InsertTemp < InsertArr[j]; --j) {
            InsertArr[j + 1] = InsertArr[j];
        }
        InsertArr[j + 1] = InsertTemp;
    }

    InsertStr.append("\n��");
    InsertStr.append(QString::number(Inserti));
    InsertStr.append("��:\t");
    ArrtoQStr(tempstr, InsertArr, arrSize);
    InsertStr.append(tempstr);
    if (++Inserti >= arrSize){
        ui->InsertBtn->setEnabled(false);
        ui->InsertBtn2->setEnabled(false);
        InsertStr.append("\n������ɣ�");
    }
    ui->InsertTxt->setPlainText(InsertStr);
}
#endif

void MainWindow::on_BInsertBtn_clicked()
{
    int j, low, high, mid;
    QString tempstr;
    ArrtoQStr(tempstr, BInsertArr, arrSize);

    BInsertTemp = BInsertArr[BInserti];
    low = 0;
    high = BInserti - 1;
    while (low <= high) {   //�۰����
        mid = (low + high) / 2;
        if (BInsertTemp < BInsertArr[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }
    for (j = BInserti - 1; j >= high + 1; --j) {
        BInsertArr[j + 1] = BInsertArr[j];
    }
    BInsertArr[high + 1] = BInsertTemp;

    BInsertStr.append("\n��");
    BInsertStr.append(QString::number(BInserti));
    BInsertStr.append("��:\t");
    ArrtoQStr(tempstr, BInsertArr, arrSize);
    BInsertStr.append(tempstr);
    if (++BInserti >= arrSize){
        ui->BInsertBtn->setEnabled(false);
        ui->BInsertBtn2->setEnabled(false);
        BInsertStr.append("\n������ɣ�");
    }
    ui->BInsertTxt->setPlainText(BInsertStr);
}

void MainWindow::on_ShellBtn_clicked()
{
    QString tempstr;
    int dk = int(pow(2, Shellt - Shellk)) - 1;
    int i, j;
    for (i = dk; i < arrSize; i++)
        if (ShellArr[i] < ShellArr[i - dk]) {
            ShellTemp = ShellArr[i];
            for (j = i - dk; j >= 0 && ShellTemp < ShellArr[j]; j -= dk)
                ShellArr[j + dk] = ShellArr[j];
            ShellArr[j + dk] = ShellTemp;
        }

    ShellStr.append("\n��");
    ShellStr.append(QString::number(Shellk + 1));
    ShellStr.append("��:\t");
    ArrtoQStr(tempstr, ShellArr, arrSize);
    ShellStr.append(tempstr);
    ShellStr.append("  ����: ");
    ShellStr.append(QString::number(dk));

    if (++Shellk >= Shellt){
        ui->ShellBtn->setEnabled(false);
        ui->ShellBtn2->setEnabled(false);
        ShellStr.append("\n������ɣ�");
    }
    ui->ShellTxt->setPlainText(ShellStr);

}

void MainWindow::on_BubbleBtn_clicked()
{
    QString tempstr;
    int j, t;
    BubbleChange = false;
    for (j = 0; j < Bubblei; ++j) {
        if (BubbleArr[j] > BubbleArr[j + 1]){
            t = BubbleArr[j];
            BubbleArr[j] = BubbleArr[j + 1];
            BubbleArr[j + 1] = t;
            BubbleChange = true;
        }
    }

    BubbleStr.append("\n��");
    BubbleStr.append(QString::number(arrSize - Bubblei));
    BubbleStr.append("��:\t");
    ArrtoQStr(tempstr, BubbleArr, arrSize);
    BubbleStr.append(tempstr);
    if (--Bubblei < 1 || !BubbleChange){
        ui->BubbleBtn->setEnabled(false);
        ui->BubbleBtn2->setEnabled(false);
        BubbleStr.append("\n������ɣ�");
    }
    ui->BubbleTxt->setPlainText(BubbleStr);
}

void MainWindow::on_QuickBtn_clicked()
{
    int pivot;
    interval itv, itv2;
    QString tempstr;
    while (1) {
        LHQueue.DeQueue(itv);
        if (itv.low == -1 && itv.high == -1)
            break;
        else {
            pivot = Partition(QuickArr, itv.low, itv.high);
            itv2.low = itv.low;
            itv2.high = pivot - 1;
            if (itv2.low < itv2.high)
                LHQueue.EnQueue(itv2);
            itv2.low = pivot + 1;
            itv2.high = itv.high;
            if (itv2.low < itv2.high)
                LHQueue.EnQueue(itv2);
        }
    }//while

    QuickStr.append("\n��");
    QuickStr.append(QString::number(QuickCount++));
    QuickStr.append("��:\t");
    ArrtoQStr(tempstr, QuickArr, arrSize);
    QuickStr.append(tempstr);

    if (LHQueue.QueueEmpty() == 1){
        ui->QuickBtn->setEnabled(false);
        ui->QuickBtn2->setEnabled(false);
        QuickStr.append("\n������ɣ�");
    }
    ui->QuickTxt->setPlainText(QuickStr);

    itv.low = -1;
    itv.high = -1;
    LHQueue.EnQueue(itv);

}

void MainWindow::on_SelectBtn_clicked()
{
    int j = SelectMin(SelectArr, Selecti, arrSize - 1);
    int temp;
    QString tempstr;
    if (Selecti != j) {
        temp = SelectArr[Selecti];
        SelectArr[Selecti] = SelectArr[j];
        SelectArr[j] = temp;
    }

    SelectStr.append("\n��");
    SelectStr.append(QString::number(Selecti + 1));
    SelectStr.append("��:\t");
    ArrtoQStr(tempstr, SelectArr, arrSize);
    SelectStr.append(tempstr);

    if (++Selecti >= arrSize - 1){
        ui->SelectBtn->setEnabled(false);
        ui->SelectBtn2->setEnabled(false);
        SelectStr.append("\n������ɣ�");
    }
    ui->SelectTxt->setPlainText(SelectStr);
}

int Partition (int *arr, int low, int high)
{
    int temp = arr[low];    //���ڱ���
    int pivot = arr[low];   //����
    while (low < high) {
        while (low < high && arr[high] >= pivot)
            --high;
        arr[low] = arr[high];
        while (low < high && arr[low] <= pivot)
            ++low;
        arr[high] = arr[low];
    }
    arr[low] = temp;
    return low;
}

//��arr[low:high]������Сֵ���±�
int SelectMin(int *arr, int low, int high)
{
    int minindex = low ;
    int i;
    for (i = low + 1; i <= high; ++i) {
        if (arr[i] < arr[minindex])
            minindex = i;
    }
    return minindex;
}


void MainWindow::on_InsertBtn2_clicked()
{
    while (ui->InsertBtn->isEnabled()) {
        on_InsertBtn_clicked();
    }
    ui->InsertBtn2->setEnabled(false);
}

void MainWindow::on_BInsertBtn2_clicked()
{
    while (ui->BInsertBtn->isEnabled()) {
        on_BInsertBtn_clicked();
    }
    ui->BInsertBtn2->setEnabled(false);
}

void MainWindow::on_ShellBtn2_clicked()
{
    while (ui->ShellBtn->isEnabled()) {
        on_ShellBtn_clicked();
    }
    ui->ShellBtn2->setEnabled(false);
}

void MainWindow::on_BubbleBtn2_clicked()
{
    while (ui->BubbleBtn->isEnabled()) {
        on_BubbleBtn_clicked();
    }
    ui->BubbleBtn2->setEnabled(false);
}

void MainWindow::on_QuickBtn2_clicked()
{
    while (ui->QuickBtn->isEnabled()) {
        on_QuickBtn_clicked();
    }
    ui->QuickBtn2->setEnabled(false);
}

void MainWindow::on_SelectBtn2_clicked()
{
    while (ui->SelectBtn->isEnabled()) {
        on_SelectBtn_clicked();
    }
    ui->SelectBtn2->setEnabled(false);
}
