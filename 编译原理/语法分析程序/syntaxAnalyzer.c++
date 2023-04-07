#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>
#define MAXN 99
using namespace std;
ifstream inFile; //输入文件
int n;           // token序列的长度
struct Token     // token结构体
{
    string str;
    string type;
};
Token tokenStream[MAXN]; //读入数据存入其中
char stack[MAXN];        //栈
char top;                //栈顶字符
int tail, pos, step;     //栈尾，输入串位置，步数
//初始化
void init()
{
    n = 0;
    string str_in, type_in;
    while (inFile >> str_in >> type_in)
    {
        tokenStream[n].str = str_in;
        tokenStream[n].type = type_in;
        n++;
    }
    tokenStream[n].str = "#";
    tokenStream[n].type = "END";
}
//输出
void show()
{
    cout << setw(5) << step << setw(10); //<<“步骤"
    for (int i = 0; i < tail; i++)       // << ": 栈内: ";
    {
        cout << stack[i];
    }
    cout << setw(10) << "\t";
    for (int i = pos; i <= n; i++)
    {
        cout << tokenStream[i].str;
    }
    cout << setw(10) << "\t";
}
//处理
void process()
{
    tail = 0;
    pos = 0, step = 0;
    stack[tail++] = '#';
    stack[tail++] = 'S';
    bool flag = true;
    while (flag)
    {
        show();
        top = stack[tail - 1];
        step++;
        switch (top)
        {
        case '#':
            if (tokenStream[pos].str == "#")
            {
                cout << "分析成功！\n";
                flag = false;
                break;
            }
        case 'S':
            if (tokenStream[pos].type == "Identifier")
            {
                cout << "推导 S->R=E; \n";
                tail--;
                stack[tail++] = ';';
                stack[tail++] = 'E';
                stack[tail++] = '=';
                stack[tail++] = 'R';
                break;
            }
        case 'R':
            if (tokenStream[pos].type == "Identifier")
            {
                cout << "推导 R->Identifier \n";
                tail--;
                stack[tail++] = 'i';
                break;
            }
        case 'E':
            if (tokenStream[pos].type == "Identifier" || tokenStream[pos].type == "Constant" || tokenStream[pos].str == "(")
            {
                cout << "推导 E->TD \n";
                tail--;
                stack[tail++] = 'D';
                stack[tail++] = 'T';
                break;
            }
        case 'D':
            if (tokenStream[pos].str == "+")
            {
                cout << "推导 D->+TD \n";
                tail--;
                stack[tail++] = 'D';
                stack[tail++] = 'T';
                stack[tail++] = '+';
                break;
            }
            if (tokenStream[pos].str == ")" || tokenStream[pos].str == ";")
            {
                cout << "推导 D->epsilon \n";
                tail--;
                break;
            }
        case 'T':
            if (tokenStream[pos].type == "Identifier" || tokenStream[pos].type == "Constant" || tokenStream[pos].str == "(")
            {
                cout << "推导 T->FH \n";
                tail--;
                stack[tail++] = 'H';
                stack[tail++] = 'F';
                break;
            }
        case 'H':
            if (tokenStream[pos].str == "*")
            {
                cout << "推导 H->*FH \n";
                tail--;
                stack[tail++] = 'H';
                stack[tail++] = 'F';
                stack[tail++] = '*';
                break;
            }
            if (tokenStream[pos].str == "+" || tokenStream[pos].str == ")" || tokenStream[pos].str == ";")
            {
                cout << "推导 H->epsilon \n";
                tail--;
                break;
            }
        case 'F':
            if (tokenStream[pos].type == "Identifier")
            {
                cout << "推导 F->Identifier \n";
                tail--;
                stack[tail++] = 'i';
                break;
            }
            if (tokenStream[pos].type == "Constant")
            {
                cout << "推导 F->Constant \n";
                tail--;
                stack[tail++] = 'c';
                break;
            }
            if (tokenStream[pos].str == "(")
            {
                cout << "推导 F->(E) \n";
                tail--;
                stack[tail++] = ')';
                stack[tail++] = 'E';
                stack[tail++] = '(';
                break;
            }
        case 'i':
            if (tokenStream[pos].type == "Identifier")
            {
                cout << "匹配 Identifier \n";
                tail--;
                pos++;
                break;
            }
        case 'c':
            if (tokenStream[pos].type == "Constant")
            {
                cout << "匹配 Constant\n";
                tail--;
                pos++;
                break;
            }
        case '+':
            if (tokenStream[pos].str == "+")
            {
                cout << "匹配 + \n";
                tail--;
                pos++;
                break;
            }
        case '*':
            if (tokenStream[pos].str == "*")
            {
                cout << "匹配 * \n";
                tail--;
                pos++;
                break;
            }
        case '(':
            if (tokenStream[pos].str == "(")
            {
                cout << "匹配 ( \n";
                tail--;
                pos++;
                break;
            }
        case ')':
            if (tokenStream[pos].str == ")")
            {
                cout << "匹配 ) \n";
                tail--;
                pos++;
                break;
            }
        case '=':
            if (tokenStream[pos].str == "=")
            {
                cout << "匹配 = \n";
                tail--;
                pos++;
                break;
            }
        case ';':
            if (tokenStream[pos].str == ";")
            {
                cout << "匹配 ; \n";
                tail--;
                pos++;
                break;
            }
        default:
            cout << "ERROR!\n";
            flag = false;
            break;
        }
    }
}
int main()
{
    string filename;
    cout << "Please enter the path and name of the source file: (default to the test.txt file in the same directory)" << endl;
    //点击回车键，使用默认文件
    getline(cin, filename);
    // 如果filename为空,则默认为test.txt
    if (filename.empty())
    {
        filename = "test.txt";
    }
    //输出文件名
    cout << "The file name is: " << filename << endl;
    // 打开文件
    inFile = ifstream(filename, ios::in);
    // 如果文件打开失败,则报错
    if (!inFile)
    {
        cerr << "Unable to open file! " << filename.c_str() << endl;
        exit(-1);
    }
    //=================
    cout << "<" << 1 << ">"
         << "\t"
         << "S->R=E;" << endl;
    cout << "<" << 2 << ">"
         << "\t"
         << "R->Identifier" << endl;
    cout << "<" << 3 << ">"
         << "\t"
         << "E->TD" << endl;
    cout << "<" << 4 << ">"
         << "\t"
         << "D->+TD" << endl;
    cout << "<" << 5 << ">"
         << "\t"
         << "D->epsilon" << endl;
    cout << "<" << 6 << ">"
         << "\t"
         << "T->FH" << endl;
    cout << "<" << 7 << ">"
         << "\t"
         << "H->*FH" << endl;
    cout << "<" << 8 << ">"
         << "\t"
         << "H->epsilon" << endl;
    cout << "<" << 9 << ">"
         << "\t"
         << "F->(E)" << endl;
    cout << "<" << 10 << ">"
         << "\t"
         << "F->Identifier" << endl;
    cout << "<" << 11 << ">"
         << "\t"
         << "F->Constant" << endl;

    init();
    cout << "\n词法分析测试结果如下：\n"
         << setw(5) << "步骤" << setw(15) << "栈内"
         << setw(20) << "输入串" << setw(30) << "动作"
         << "\n";

    process();
    return 0;
}