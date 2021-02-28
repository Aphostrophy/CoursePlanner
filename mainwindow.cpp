#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "boolmatrix.h"
#include <bits/stdc++.h>

using namespace std;

string romanNumeralsEncoder(int n){
    int val[13] = {1000,900,500,400,100,90,50,40,10,9,5,4,1};
    string sym[13] = {"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};
    string roman = "";
    for(int i=0;i<13;i++){
        while(n>=val[i]){
            roman.append(sym[i]);
            n -= val[i];
        }
    }
    return roman;
}

int getIndex(vector<string> v, string course){
    for(int i=0;i<v.size();i++){
        if(course==v[i]){
            return i;
        }
    }
    return -1;
}

int findNodeZero(bool **DAG,int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(DAG[i][j]==1){
                break;
            } else if(j==n-1 && DAG[i][j] == 0){
                return i;
            }
        }
    }
    return -1;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open a file", "C://");
    QScrollBar *sBar = new QScrollBar();
    QTextCursor cursor = ui->textEdit->textCursor();
    ui->textEdit->setVerticalScrollBar(sBar);
    fstream courses_file;

    vector<string> courses;

    courses_file.open(filename.toStdString(), ios::in);
    if(!courses_file){
        cout << "File not found\n";
    } else{
        string line;
        string tempString;

        while(getline(courses_file,line)){
            for(char &c: line){
                if(c!=',' && c!='.' && !isspace(c)){
                    tempString.push_back(c);
                } else if(tempString!=""){
                    if(count(courses.begin(),courses.end(),tempString)==0){
                        courses.push_back(tempString);
                    }
                    tempString = "";
                }
            }
        }

        //Deklarasi 2D variable sized matrix
        BoolMatrix DAG(courses.size());

        courses_file.clear();
        courses_file.seekg (0, ios::beg);

        tempString = "";

        while(getline(courses_file,line)){
            vector<int> nodeAdj;
            for(char &c : line){
                if(c!=',' && c!='.' && !isspace(c)){
                    tempString.push_back(c);
                } else if(tempString!=""){
                    nodeAdj.push_back(getIndex(courses,tempString));
                    tempString = "";
                }
            }

            for(int i=1;i<nodeAdj.size();i++){
                DAG.matrix[nodeAdj[0]][nodeAdj[i]] = true;
            }
        }

        stack<vector<string>> reversedplan;
        stack<vector<string>> plan;

        DAG.topologicalsort(reversedplan,courses);

        while(reversedplan.size()){
            plan.push(reversedplan.top());
            reversedplan.pop();
        }
        int x=1;
        while(plan.size()){
            string semester= "Semester ";
            semester.append(romanNumeralsEncoder(x));
            ui->textEdit->append(QString::fromStdString(semester));
            for(int i=0;i<plan.top().size();i++){
                ui->textEdit->append(QString::fromStdString(plan.top()[i]));
            }
            ui->textEdit->append("==================================================");
            plan.pop();
            x++;
        }
    }
    courses_file.close();
    ui->textEdit->selectAll();
    ui->textEdit->setFontPointSize(20);
    ui->textEdit->setTextCursor( cursor );
}
