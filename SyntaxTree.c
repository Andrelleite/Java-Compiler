/*********************************************
*
*           Andre Leite - 2015250489
*
**********************************************/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "SyntaxTree.h"

Node* initNode(char *type, char* id){

	Node *node = (Node*)malloc(sizeof(Node));

	node->id = (char*)malloc(1024 * sizeof(char));
	node->type = (char*)malloc(1024 * sizeof(char));
	node->id = strdup(id);
	node->type = strdup(type);

	node->sibling = NULL;
	node->child = NULL;
	node->ptr = NULL;

	return node;

}

void addChild(Node* no, Node *child){

	if((no == NULL) || (child == NULL)){
		return;
	}
	if(no->child != NULL){
		addSibling(no->child, child);
	}
	else{
		while(child->ptr != NULL){
			child = child->ptr;
		}
		no->child = child;
	}

}

void addSibling(Node *no, Node *sibling){
	if((no == NULL) || (sibling == NULL)){
		return;
	}
	while(no->sibling != NULL){
		no = no->sibling;
	}

	while(sibling->ptr != NULL){
		sibling = sibling->ptr;
	}
	no->sibling = sibling;
	sibling->ptr = no;
}




void printThemTrees(Node *root,int dottydots){
	
	int i = 0;

	
	while(i < dottydots && strcmp(root->id,"VarDeclTop")!=0 && strcmp(root->id,"SEMICOLON")!=0 && strcmp(root->id,"FieldDeclTop")!=0 && strcmp(root->id,"MethodAuxTop")!=0 && strcmp(root->id,"NULL") != 0 ){
		printf("..");
		i++;
	}
	
	if(strcmp(root->id,"Id")==0 || strcmp(root->id,"DecLit")==0 || strcmp(root->id,"StrLit")==0 || strcmp(root->id,"RealLit")==0 || strcmp(root->id,"BoolLit")==0){
		printf("%s(%s)\n",root->id,root->type);
	}else{
		if(strcmp(root->id,"VarDeclTop")!=0 && strcmp(root->id,"SEMICOLON")!=0 && strcmp(root->id,"FieldDeclTop")!=0 && strcmp(root->id,"MethodAuxTop")!=0 && strcmp(root->id,"NULL") != 0){
			printf("%s\n",root->id);
		}
	}
	
	
	if(root->child!=NULL){
		printThemTrees(root->child,dottydots+1);
	}
	
	if(root->sibling!=NULL) {
		printThemTrees(root->sibling,dottydots);
	}
	

}

void destroyThemTrees(Node *root){
	if(root != NULL){
		if(root->id != NULL){
			free(root->id);
		}
		if (root->type != NULL){
			free(root->type);
		}
		if(root->sibling != NULL){
			destroyThemTrees(root->sibling);
		}
		if(root->child != NULL){
			destroyThemTrees(root->child);
		}
		free(root);
	}
}


int checkBlock(Node *head){
	
	int i = 0;
	int j = 0;
	int p = 0;
	Node *temp = head;
	while(temp != NULL){
		if(strcmp(temp->id,"NULL")!=0){
			i++;
		}else{
			j++;
		}
		p++;
		temp = temp->sibling;
	}
	if((i > 1) && (p != j || p == 1)){
		return 1;
	}else if(i == 0){
		return 2;
	}
	return 0;
	
}


