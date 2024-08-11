/*************************************************************************
    > File Name: linked_list.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月04日 星期日 22时29分58秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 链表头文件
    > Content:
 ************************************************************************/

#include "linked_list.h"
#include "user.h"
#include <stdio.h>
#include <threads.h>

// 创建新的链表节点
ListNode* createNode(void * val){
    ListNode* newNode = (ListNode*)calloc(1, sizeof(ListNode));
    if ( !newNode ) {
        perror("Memory allocation failed\n");
        exit(1);
    }
    newNode->next = NULL;
    newNode->val = val;
    return newNode;
}

// 在链表末尾添加元素
void appendNode(ListNode **head, void *val) {
    ListNode* newNode = createNode(val);
    if ( *head == NULL ) {
        *head = newNode;
        return;
    }
    ListNode* currNode = *head;
    while(currNode->next != NULL) { currNode = currNode->next; }
    currNode->next = newNode;
}

// 删除链表中值为target的节点（假设只删除一个）
void deleteNode(ListNode **head, void * target){
    if( *head == NULL ) { return; }

    /* 头节点 */
    if((*head)->val == target) {
        ListNode* temp = *head;
        *head = temp->next;
        free(temp);
        return;
    }

    ListNode* currNode = *head;
    while(currNode->next != NULL && currNode->val != target) { currNode = currNode->next; }

    if ( currNode->next != NULL ){
        ListNode* temp = currNode->next;
        currNode->next = temp->next;
        free(temp);
        return;
    }
}

// 删除链表中值为peerfd的节点（假设只删除一个）
void deleteNode2(ListNode **head, int peerfd){
    if( *head == NULL ) { return; }

     /* 头节点 */    
    user_info_t* user = (user_info_t*)((*head)->val);
    if(user->sockfd  ==  peerfd) {
        ListNode* temp = *head;
        *head = temp->next;
        free(temp);
        printf("free user node.\n");
        return;
    }

    /* 头节点不是情况 */
    ListNode* currNode = *head;
    while(currNode->next != NULL) { 
        if ( ((user_info_t*)currNode->next->val)->sockfd != peerfd ) {
            currNode = currNode->next;
            continue;
        }
        break;
    }

    if ( currNode->next != NULL ){
        ListNode* temp = currNode->next;
        currNode->next = temp->next;
        free(temp);
        printf("free user node 2.\n");
        return;
    }
}

// 根据peerfd查找指定的节点, user传出参数
void findByPeerfd(ListNode* head, int peerfd, user_info_t** user){
    if(head == NULL) { return; }

    /* 头节点就是需求节点 */
    user_info_t* user_head = (user_info_t*)(head->val);
    if( user_head->sockfd == peerfd ) {
        *user = user_head;
        return;
    }

    /* 遍历查找链表中符合的用户 */
    ListNode* currNode = head;
    while(currNode->next != NULL) { 
        currNode = currNode->next; 
        if ( ((user_info_t*)currNode->val)->sockfd == peerfd ) {
            *user = (user_info_t*)currNode->val;
            return;
        }
    }
    return;
}

// 打印链表
void printList(ListNode *head){
    if( head == NULL ) return;
    
    ListNode* currNode = head;
    while(currNode != NULL) {
        printf("%s",(char*) currNode->val);
        currNode = currNode->next;
    }
    putchar('\n');
}

// 释放链表内存
void freeList(ListNode *head){
    if ( head == NULL ) return;
    ListNode* currNode = head;
    while(currNode != NULL) {
        ListNode* temp  = currNode->next;
        free(currNode);
        currNode = temp;
    }
}

/* 测试 */
// int main(void) {
// 
//     ListNode* ln = NULL;
//     char buff[] = "hello,world.\n";
//     char buff2[] = "hi,its me.\n";
// 
//     appendNode(&ln, buff);
//     appendNode(&ln, buff);
//     appendNode(&ln, buff2);
//     
//     printList(ln);
// 
//     deleteNode(&ln, buff);
// 
//     printList(ln);
// 
//     freeList(ln);
// 
//     printList(ln);
// 
//     return 0;
// }
