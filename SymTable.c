/*********************************************
*
*           Andre Leite - 2015250489
*           Lucas Ferreira - 2016243439
*
**********************************************/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "SyntaxTree.h"
#include "SymTable.h"



void printThemTables(Node *node){
	
	stack_p root = (stack_p)malloc(sizeof(Stack));
	t_pointer temp; Node *t_temp;
	t_pointer table_root = (t_pointer)malloc(sizeof(Tabnode));
	root->next = NULL;
	
	if(strcmp(node->id,"Program")==0){
		table_root->id_type = strdup("Class");
		table_root->id = strdup(node->child->type);
		table_root->type = NULL;
		table_root->next = NULL;
		specificTable(root,node->child,table_root);
	}
	
	makeTableModel(table_root,node);
	printFinal(table_root);	
	
	temp = table_root->lower;
	while(temp!=NULL){
		if(strcmp(temp->id_type,"MethodDecl")==0){
			t_temp = temp->node->sibling->child;
			navigate(table_root,temp,t_temp);
		}
		temp = temp->lower;
	}
	
}

void statementA(t_pointer top, t_pointer table_root, Node *t){
	
	int mirror, j;
	int out = 0;
	t_pointer temp;
	Node *inner;
	Node *aux = t;
	
		
			out = 0;
			inner = aux->child->sibling;
			
			while(inner != NULL){
				if(strcmp(inner->id,"Call")==0){
					statementA(top,table_root,inner);
				}
				inner = inner->sibling;
			}
			
			getCallType(aux);
			temp = top->lower;
			while(temp != NULL && out != 1){
				if(strcmp(aux->child->type,temp->id)==0){
					
					mirror = aux->child->card_p_t-2;
					if(temp->cardptypes == mirror){
						for(j = 0; j < temp->cardptypes; j++){
							if(strcmp(correctType(temp->paramtypes[j],aux),aux->child->param_t[j+1])==0){
								mirror--;
							}
						}
						if(mirror==0){
							out = 1;
							aux->child->id_type = strdup(correctType(temp->type,aux));
							aux->id_type = strdup(aux->child->id_type);
						}
					}
				}
				temp = temp->lower;
			}
			if(out != 1){
				temp = top->lower;
				while(temp != NULL && out != 1){
					if(strcmp(aux->child->type,temp->id)==0){
						mirror = aux->child->card_p_t-2;
						if(temp->cardptypes == mirror){
							for(j = 0; j < temp->cardptypes; j++){
								if(strcmp(correctType(temp->paramtypes[j],aux),aux->child->param_t[j+1])==0){
									mirror--;
								}else if(strcmp(correctType(temp->paramtypes[j],aux),"double")==0 && strcmp(aux->child->param_t[j+1],"int")==0){
									mirror--;
								}
							}
							if(mirror==0){
								out = 1;
								for(j = 0; j < temp->cardptypes; j++){
									strcpy(aux->child->param_t[j+1],correctType(temp->paramtypes[j],aux));
								}
								
								aux->child->id_type = strdup(correctType(temp->type,aux));
								aux->id_type = strdup(aux->child->id_type);
							}
						}
						
					}
					temp = temp->lower;
				}
			}

	
}

char *navigate(t_pointer top, t_pointer table_root,Node *aux){
	
	Node *t = aux;
	while(t != NULL){
		if(strcmp(t->id,"VarDecl")!=0 && strcmp(t->id,"Rshift")!=0 && strcmp(t->id,"Lshift")!=0){
			if(t->child!=NULL){
				navigate(top, table_root,t->child);
				if(strcmp(t->id,"Call")==0){
					statementA(top, table_root, t);
				}else{
					t->id_type = strdup(correctType(t->id,t));
				}
			}else{
				getType(t,table_root);
				getType(t,top);
			}
		}else{
			t->id_type = "";
		}
		t = t->sibling;
	}
	return "";
}

void getCallType(Node *node){
	
	Node *temp = node->child->sibling;
	node->child->card_p_t = 0;
	strcpy(node->child->param_t[node->child->card_p_t],"(");
	node->child->card_p_t++;
	
	while(temp != NULL){
		strcpy(node->child->param_t[node->child->card_p_t],temp->id_type);
		node->child->card_p_t++;
		temp = temp->sibling;
	}
	
	strcpy(node->child->param_t[node->child->card_p_t],")");
	node->child->card_p_t++;
	
}

char *getType(Node *node, t_pointer tabela){
	
	t_pointer temp = tabela;
	
	if(node->id_type == NULL){
		char *get = correctType(node->id,node);
		if(strcmp(get,"undef")!=0){
			
			node->id_type = strdup(get);
			return get;
			
		}else{
			
			while(temp != NULL){
				
				if(node->type != NULL){
					if(strcmp(node->type,temp->id)==0 && temp->cardptypes == 0){
						node->id_type = strdup(correctType(temp->type,node));
						return temp->type;
					}
				}
			
				if(strcmp(tabela->id_type,"Class")==0){
					temp = temp->lower;
				}else{
					temp = temp->next;
				}
				
			}
			
		}
		node->id_type = strdup(correctType("undef",node));
		return "undef";
	}else if(strcmp(node->id_type,"undef")==0){
		char *get = correctType(node->id,node);
		if(strcmp(get,"undef")!=0){
			node->id_type = strdup(get);
			return get;
		}else{
			while(temp != NULL){
				if(node->type != NULL){
					if(strcmp(node->type,temp->id)==0 && temp->cardptypes == 0){
						node->id_type = strdup(correctType(temp->type,node));
						return temp->type;
	
					}
				}
				if(strcmp(tabela->id_type,"Class")==0){
					temp = temp->lower;
				}else{
					temp = temp->next;
				}
			}
		}
		node->id_type = strdup(correctType("undef",node));
		return "undef";
	}else{
		return node->id_type;
	}
	
}

char *correctType(char *node, Node *n){
	
	if(strcmp(node,"DecLit")==0 || strcmp(node,"Int")==0){
		return "int";
	}else if(strcmp(node,"RealLit")==0 || strcmp(node,"Double")==0){
		return "double";
	}else if(strcmp(node,"BoolLit")==0 || strcmp(node,"Bool")==0){
		return "boolean";
	}else if(strcmp(node,"StringArray")==0){
		return "String[]";
	}else if(strcmp(node,"StrLit")==0){
		return "String";
	}else if(strcmp(node,"Void")==0){
		return "void";
	}else if(strcmp(node,"Eq")==0 || strcmp(node,"Ne")==0 || strcmp(node,"And")==0 || strcmp(node,"Or")==0){
		return "boolean";
	}else if(strcmp(node,"Ge")==0 || strcmp(node,"Gt")==0 || strcmp(node,"Le")==0 || strcmp(node,"Lt")==0){
		return "boolean";
	}else if(strcmp(node,"ParseArgs")==0 || strcmp(node,"Length")==0){
		return "int";
	}else if(strcmp(node,"Return")==0 || strcmp(node,"Block")==0 || strcmp(node,"If")==0 || strcmp(node,"Print")==0 || strcmp(node,"While")==0){
		return "";
	}else if(strcmp(node,"Mul")==0 || strcmp(node,"Sub")==0 || strcmp(node,"Call")==0 || strcmp(node,"Add")==0 || strcmp(node,"Not")==0){
		return childType(n);
	}else if(strcmp(node,"Minus")==0 || strcmp(node,"Xor")==0 || strcmp(node,"Div")==0 || strcmp(node,"Mod")==0 || strcmp(node,"Plus")==0 ){
		return childType(n);
	}else if(strcmp(node,"Rshift")==0 || strcmp(node,"Lshift")==0){
		return childType(n);
	}else if(strcmp(node,"Assign")==0){
		return n->child->id_type;
	}else{
		return "undef";
	}
	
}

char *childType(Node *n){
	
	Node *t = n->child;
	char *sucesso = strdup(n->child->id_type);
	
	while(t != NULL){
		if(strcmp(t->id_type,"double")==0 && strcmp(sucesso,"int")==0){
			sucesso = strdup(t->id_type);
		}else if(strcmp(t->id_type,"boolean")==0 && strcmp(sucesso,"double")==0){
			sucesso = strdup(t->id_type);
		}else if(strcmp(t->id_type,"boolean")==0 && strcmp(sucesso,"int")==0){
			sucesso = strdup(t->id_type);
		}
		t = t->sibling;
	}
	
	if(strcmp(sucesso,"")==0){
		sucesso = "undef";
	}
	
	return sucesso;
	
}

void printFinal(t_pointer table){
	
	int i;
	t_pointer auxf, t_temp;
	t_temp = table;
	auxf = table->lower;
	if(strcmp(t_temp->id_type,"Class")==0){
		printf("===== Class %s Symbol Table =====\n",t_temp->id);		
		t_temp = t_temp->lower;
		while(t_temp!=NULL){
			printf("%s",t_temp->id);
			if(strcmp(t_temp->id_type,"MethodDecl")==0){
				printf("\t(");
				controlPrint(t_temp->paramtypes[0]);
				for(i=1; i < t_temp->cardptypes; i++){
					printf(",");
					controlPrint(t_temp->paramtypes[i]);
				}
				printf(")\t");
			}else{
				printf("\t\t");
			}
			
			controlPrint(t_temp->type);
			if(t_temp->param != NULL){
				printf("\tparam");
			}
			printf("\n");
			t_temp = t_temp->lower;
		}
		printf("\n");

	}else if(strcmp(t_temp->id_type,"MethodDecl")==0){
		printf("===== Method %s(",t_temp->id);
		controlPrint(t_temp->paramtypes[0]);
		for(i=1; i < t_temp->cardptypes; i++){
			printf(",");
			controlPrint(t_temp->paramtypes[i]);
		}
		printf(") Symbol Table =====\n");
		t_temp = t_temp->next;
		while(t_temp!=NULL){
			printf("%s",t_temp->id);
			if(t_temp->cardptypes != 0){
				printf("\t(");
				controlPrint(t_temp->paramtypes[0]);
				for(i=1; i < t_temp->cardptypes; i++){
					printf(",");
					controlPrint(t_temp->paramtypes[i]);
				}
				printf(")\t");
			}else{
				printf("\t\t");
			}
			controlPrint(t_temp->type);
			if(t_temp->param != NULL){
				printf("\tparam");
			}
			printf("\n");
			t_temp = t_temp->next;
		}
		printf("\n");
	}
	
	
	
	while(auxf != NULL){
		printFinal(auxf);
		auxf = auxf->next;
	}
	
	
}

void makeTableModel(t_pointer table, Node *node){
	
	t_pointer t_temp; 

	t_temp = table->lower;
	while(t_temp!=NULL){
		if(strcmp(t_temp->id_type,"MethodDecl")==0){		
			method(node,t_temp->node,t_temp);
		}
		t_temp = t_temp->lower;
	}
}

void method(Node *root,Node *method, t_pointer table_root){
	
	Node *aux;
	t_pointer t_temp = table_root;
	t_pointer new_table_node;

	new_table_node = (t_pointer)malloc(sizeof(Tabnode));
	
	if(method->child->sibling->sibling->child != NULL){
		aux = method->child->sibling->sibling->child;
		aux = aux->sibling;
		while(aux!=NULL){
			aux = aux->sibling;
		}
	}
	new_table_node->id_type = strdup("Return");
	new_table_node->id = strdup("return");
	new_table_node->type = strdup(method->child->id);
	new_table_node->cardptypes = 0;
	new_table_node->param = NULL;
	t_temp->next = new_table_node;
	t_temp = t_temp->next;
	aux = method->child->sibling->sibling->child;
	while(aux != NULL){
		
		new_table_node = (t_pointer)malloc(sizeof(Tabnode));
		new_table_node->id_type = strdup("ParamDecl");
		new_table_node->id = strdup(aux->child->sibling->type);
		new_table_node->type = strdup(aux->child->id);
		new_table_node->cardptypes = 0;
		new_table_node->param = strdup("param");
		t_temp->next = new_table_node;
		t_temp = t_temp->next;
		
		
		aux = aux->sibling;
	}
	aux = method->sibling->child;
	while(aux != NULL){
		
		if(strcmp(aux->id,"VarDecl")==0){
			
			new_table_node = (t_pointer)malloc(sizeof(Tabnode));
			new_table_node->id_type = strdup("VarDecl");
			new_table_node->id = strdup(aux->child->sibling->type);
			new_table_node->type = strdup(aux->child->id);
			new_table_node->cardptypes = 0;
			new_table_node->param = NULL;
			t_temp->next = new_table_node;
			t_temp = t_temp->next;
			
			
		}
		aux = aux->sibling;
	}
				
			
}

void specificTable(stack_p stack,Node *node,t_pointer table_root){
	
	int i;
	Node *temp = node->sibling;
	Node *upper;
	Node *st_upper;
	stack_p slot = stack;
	stack_p brand_new;
	t_pointer t_temp = table_root;
	t_pointer new_table_node;
	char *tp = (char *) malloc(sizeof(char)*32);

	
	while(temp != NULL){
		
		if(strcmp(temp->id,"FieldDecl")==0){
			tp = strdup(temp->child->id);
			upper = temp->child->sibling;
			
			/*table insertion*/
			new_table_node = (t_pointer)malloc(sizeof(Tabnode));
			new_table_node->id = strdup(upper->type);
			new_table_node->id_type = (char *)malloc(sizeof(char)*16);
			new_table_node->type = strdup(temp->child->id);
			new_table_node->id_type = strdup(temp->id);
			new_table_node->cardptypes = 0;
			new_table_node->lower = NULL;
			new_table_node->next = NULL;
			new_table_node->param = NULL;
			t_temp->lower = new_table_node;
			t_temp = t_temp->lower;
			
			/*printf("%s\t\t",upper->type);
			controlPrint(tp);
			printf("\n");*/
		}else if(strcmp(temp->id,"MethodDecl")==0){
			
			i = 0;
			tp = strdup(temp->child->child->id);
			upper = temp->child->child->sibling;
			st_upper = temp->child;

			brand_new = (stack_p)malloc(sizeof(Stack));
			brand_new->node = st_upper;
			brand_new->next = NULL;
			slot->next = brand_new;
			slot = slot->next;
			
			/*table insertion*/
			new_table_node = (t_pointer)malloc(sizeof(Tabnode));
			new_table_node->id_type = (char *)malloc(sizeof(char)*16);
			strcpy(new_table_node->id_type,temp->id);
			new_table_node->node = st_upper;
			new_table_node->cardptypes = 0;
			new_table_node->id = strdup(upper->type);
			new_table_node->type = strdup(temp->child->child->id);
			new_table_node->lower = NULL;
			new_table_node->next = NULL;
			
			
			/*printf("%s\t(",upper->type);*/
			if(upper->sibling->child != NULL){
				upper = upper->sibling->child;
				strcpy(new_table_node->paramtypes[i],upper->child->id);
				new_table_node->cardptypes++;
				/*controlPrint(upper->child->id);*/
				upper = upper->sibling;
				i++;
				while(upper!=NULL){
					/*printf(",");
					controlPrint(upper->child->id);*/
					strcpy(new_table_node->paramtypes[i],upper->child->id);
					upper = upper->sibling;
					new_table_node->cardptypes++;
					i++;
				}
			}
			
			
			
			/*printf(")\t");
			controlPrint(tp);
			printf("\n");*/
			new_table_node->param = NULL;
			t_temp->lower = new_table_node;
			t_temp = t_temp->lower;
		}
		
		temp = temp->sibling;
	}
	/*printf("\n");*/
}

void controlPrint(char *token){
	
	if(strcmp(token,"Int")==0){
		printf("int");
	}else if(strcmp(token,"StringArray")==0){
		printf("String[]");
	}else if(strcmp(token,"Void")==0){
		printf("void");
	}else if(strcmp(token,"DecLit")==0){
		printf("int");
	}else if(strcmp(token,"Double")==0){
		printf("double");
	}else if(strcmp(token,"Bool")==0){
		printf("boolean");
	}
	
}
