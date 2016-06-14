#ifndef _LIST_H_
#define _LIST_H_

#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef struct ListNode {
    ElemType data;
    ListNode *next; //指向下一个结点
    ListNode *prior; //预留反向指针,用于处理循环链表,单链表中未使用
} ListNode;

//判断链表是否为空
bool isEmpty(const ListNode* head, bool noHead = 1)
{
    return noHead ? NULL == head : NULL == head->next;
}
//得到链表结点个数--即获取长度
unsigned getLength(const ListNode* head, bool noHead = 1)
{
    unsigned length = 0;
    const ListNode* p = noHead ? head : head->next;
    while (p != NULL) {
        p = p->next;
        ++length;
    }
    return length;
}
//创建链表，注意参数必须为二级指针或者一级指针的引用
int createList_head_n(ListNode* &head, unsigned n, bool noHead = 1)
{
    head = noHead ? NULL : (ListNode*)malloc(sizeof(ListNode));
    if (!noHead) {
        head->next = NULL;
    }
    ListNode *p = NULL;
    ElemType temp;
    if (n <= 0) {
        return -1;
    }
    for (int i = n; i >= 1; i--) {
        p = (ListNode*)malloc(sizeof(ListNode));
        if (p == NULL) {
            return -2;
        }
        printf("please input no.%d data \'s value: ", i);
        scanf("%d", &temp);
        fflush(stdin);//清除缓冲区多余的数据
        p->data = temp;
        if (noHead) {
            p->next = head;
            head = p;
        } else {
            p->next = head->next;
            head->next = p;
        }
    }
    return 0;
}
//创建链表，以特定值(9999)结束,而不是固定长度
int createList_head(ListNode* &head, bool noHead = 1)
{
    puts("请输入若干结点值,以9999表示链表创建结束:");
    head = noHead ? NULL : (ListNode*)malloc(sizeof(ListNode));
    if (!noHead) {
        head->next = NULL;
    }
    ListNode *p = NULL;
    ElemType temp;
    fflush(stdin);
    scanf("%d", &temp);
    while (temp != 9999) {
        p = (ListNode*)malloc(sizeof(ListNode));
        if (p == NULL) {
            return -2;
        }
        p->data = temp;
        if (noHead) {
            p->next = head;
            head = p;
        } else {
            p->next = head->next;
            head->next = p;
        }
        scanf("%d", &temp);
    }
    return 0;
}
//显示链表结构
void showList(const ListNode* head, const char* note = "", bool noHead = 1)
{
    if (note && note[0]) {
        puts(note);
    }
    if (isEmpty(head, noHead)) {
        puts("List is empty !");
        return;
    }
    const ListNode* p = noHead ? head : head->next;
    while (p) {
        printf("%d -> ", p->data);
        p = p->next;
    }
    puts("\b\b\b\b\t");
}
#endif //_LIST_H_
