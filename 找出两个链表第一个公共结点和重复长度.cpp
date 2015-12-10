/******************************************************************
问题描述:给定两个单向链表，找出它们的第一个公共节点和重合部分的长度。
链表的节点定义如下:
struct ListNode {
	int m_nKey;
	ListNode* m_pNext;
};

思路:
如果两个链表有公共结点,那么该公共结点之后的所有结点都是重合的,最后一个结点必然是重合的。因此,我们判断两个链表是不是有重合的部分,只需要判断最后一个结点。如果两个尾结点是一样的,说明它们重合;否则两个链表没有公共的结点。

在上面的思路中,顺序遍历两个链表到尾结点的时候,我们不能保证在两个链表上同时到达尾结点。这是因为两个链表长度可能不一样。但我们假设一个链表比另一个长s个结点,我们先在长的链表上遍历s个结点,之后再同时遍历两个链表,这时就能保证两个链表同时到达尾节点了。由于两个链表从第一个公共结点开始到链表的尾结点,这一部分是重合的。因此,它们肯定也是同时到达第一公共结点的。于是在遍历中，第一个相同的结点就是第一个公共的结点。
******************************************************************/
#include<stdio.h>
typedef struct ListNode {
	int key;
	ListNode* next;
}ListNode;
//返回一个结点类型：值表示公共结点个数,指针表示第一个公共结点
ListNode findFirstCommonNode(ListNode* pHead1, ListNode* pHead2)
{
	if(pHead1==NULL || pHead2==NULL)
		return {0};
	ListNode *pFast = pHead1, *pSlow = pHead2, *pSync = NULL, *pSlowLast = NULL;
	while(pFast->next!=NULL && pSlow->next!=NULL){
		pFast = pFast->next;
		pSlow = pSlow->next;
	}
	//某个链表到达了尾结点
	if(pFast->next==NULL){	//链表1更短
		pSlowLast = pFast;	//记录短链表的最后一个结点
		pSync = pSlow;
		pFast = pHead2;		//记录长链表
		pSlow = pHead1;		//记录短链表
	}else{ //链表2更短
		pSlowLast = pSlow;	//记录短链表的最后一个结点
		pSync = pFast;
		pFast = pHead1;		//记录长链表
		pSlow = pHead2;		//记录短链表
	}
	while(pSync->next!=NULL){
		pSync = pSync->next;
		pFast = pFast->next;
	}
	if(pSync!=pSlowLast)	//最后一个结点不同,则没有公共结点
		return {0};
	while(pFast!=pSlow){
		pFast = pFast->next;
		pSlow = pSlow->next;
	}//这里一定已经找到公共结点
	unsigned length = 1;	//记录公共结点长度
	while(pSlow!=pSlowLast){
		pSlow = pSlow->next;
		++length;
	}
	return {length,pFast};
}
