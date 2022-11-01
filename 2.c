#include<stdio.h>
#include <iostream>
using namespace std;
 
// 函数结果状态代码
#define TRUE    1
#define FALSE   0
#define OK      1
#define ERROR   0
#define INFEASIBLE -1
#define OVERFLOW   -2
#define MAXSIZE    100
 
// Status 是函数的类型 其值是函数结果状态代码
typedef int Status;
typedef int ElemType;
 
typedef struct _tag_Sqlist{
 
    ElemType *elem;
    int length;
}Sqlist;
 
// 构造一个空的顺序表
Status InitList(Sqlist &L){
 
    L.elem = new ElemType[MAXSIZE];  // 为顺序表分配空间
    if (!L.elem) exit(OVERFLOW);     // 存储分配失败
    L.length = 0;                   // 空表长度0
    return OK;
}
 
// 求线性表的长度
int GetLength(Sqlist L){
 
    return L.length;
}
 
// L中查找与给定值e相等的元素，若成功返回该元素在表中的序号，否则返回0;
int LocateElem(Sqlist L, ElemType e){
 
    for (int i = 0; i < L.length; ++i) {
        if (L.elem[i] == e) return i+1;
    }
    return 0;
}
 
// 将线性表L中的第i个位置元素返回给e
Status GetElem(Sqlist L, int i, ElemType &e){
 
    if (i < 1 || i > L.length) return ERROR; // 判断是否合理
    e = L.elem[i-1];    // 第i-1的单元存储着第i个数据
    return OK;
}
 
 
// 在线性表L中的第i个位置插入新元素e
Status ListInsert(Sqlist &L, int i, ElemType e){
 
    if (i < 1 || i > L.length + 1) return ERROR;       // 判断i值是否合法
    if (L.length == MAXSIZE) return ERROR;             // 当前存储空间已满
    for (int j = L.length -1 ; j >= i -1 ; --j) {
        L.elem[j+1] = L.elem[j];                       // 插入位置及之后的元素后移
    }
    L.elem[i-1] = e;                                   // 将新元素e放入第i个位置
    L.length++;                                        // 表长+1
    return OK;
}
 
// 遍历线性表
void ListTraversals(Sqlist L){
 
    for (int i = 0; i < GetLength(L); ++i) {
        cout << L.elem[i] << " ";
    }
    cout << endl;
}
 
// 线性表偶的合并
void SqlistUnion(Sqlist &La, Sqlist &Lb){
 
    int La_len = GetLength(La);
    int Lb_len = GetLength(Lb);
    for (int i = 1; i <= Lb_len; ++i) {
 
        ElemType e = 0;
        GetElem(Lb, i, e);
        if (!LocateElem(La, e)) ListInsert(La, ++La_len, e);
    }
}
 
// 有序表合并--用顺序表实现
void MergeList_Sq(Sqlist La, Sqlist Lb, Sqlist &Lc){
 
    ElemType  *pa ,*pb, *pc, *pa_last, *pb_last;
    pa = La.elem;
    pb = Lb.elem;                           // 指针pa,pb的初始值分别指向两个表的第一个元素
    Lc.length = La.length + Lb.length;      // 新表长度为待合并两表的长度之和
    Lc.elem = new ElemType[Lc.length];      // 为合并后新表分配一个数组空间
    pc = Lc.elem;                           // 指针pc指向新表的第一个元素
    pa_last = La.elem + La.length -1;       // 指针pa_last指向La表的最后一个元素
    pb_last = Lb.elem + Lb.length -1;       // 指针pb_last指向Lb表的最后一个元素
 
    while (pa <= pa_last && pb <= pb_last){    // 两个表都非空
        if (*pa <= *pb) *pc++ = *pa++;          // 一次摘取两表中值最小的节点
        else *pc++ = *pb++;
    }
    while (pa <= pa_last) *pc++ = *pa++;    // Lb表已经达到表尾，将La中剩余元素加入Lc
    while (pb <= pb_last) *pc++ = *pb++;    // La表已经达到表尾，将Lb中剩余元素加入Lc
}
 
int main() {
 
    // 创建线性表La Lb
    int ret = 0;
    Sqlist La, Lb, Lc;
    ret = InitList(La);
    if (ret == OK) cout << "创建线性表La成功" << endl;
    ret = InitList(Lb);
    if (ret == OK) cout << "创建线性表Lb成功" << endl;
    ret = InitList(Lc);
    if (ret == OK) cout << "创建线性表Lc成功" << endl;
 
    // La = (1, 7, 8) Lb = (2, 4, 6, 8, 10, 11)
    // 插入线性表La
    ret = ListInsert(La, 1, 1);
    ret = ListInsert(La, 2, 7);
    ret = ListInsert(La, 3, 8);
 
    cout << "La: ";
    ListTraversals(La);
 
    // 插入线性表Lb
    ret = ListInsert(Lb, 1, 2);
    ret = ListInsert(Lb, 2, 4);
    ret = ListInsert(Lb, 3, 6);
    ret = ListInsert(Lb, 4, 8);
    ret = ListInsert(Lb, 5, 10);
    ret = ListInsert(Lb, 6, 11);
    cout << "Lb: ";
    ListTraversals(Lb);
 
    // 有序表的合并
    MergeList_Sq(La, Lb, Lc);
    cout << "有序表的合并: ";
    ListTraversals(Lc);
    
    return 0;
}
 