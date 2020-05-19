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


void printThemTables(Node *node, int flag){
	
	t_pointer temp; Node *t_temp;
	t_pointer table_root = (t_pointer)malloc(sizeof(Tabnode));
	
	if(strcmp(node->id,"Program")==0){
		table_root->id_type = strdup("Class");
		table_root->id = strdup(node->child->type);
		table_root->type = NULL;
		table_root->next = NULL;
		specificTable(node->child,table_root);
	}

	/*criar esqueleto da tabela*/
	makeTableModel(table_root,node);

	
	temp = table_root->lower;
	while(temp!=NULL){
		if(strcmp(temp->id_type,"MethodDecl")==0){
			t_temp = temp->node->sibling->child;
			navigate(table_root,temp,t_temp);

		}
		temp = temp->lower;
	}

	/*aqui corrige repeticao*/
	repeated(table_root);
	/*elimina repetidos*/
	if(flag==0){
		printFinal(table_root);
	}
	
	/*libertar memoria da raiz*/
	free(table_root);
	
}

void repeated(t_pointer top){
	
	int i, counter;
	char *rep;
	t_pointer header;
	t_pointer back;
	t_pointer pivot = top->lower;
	
	while(pivot!=NULL){
		
		header = top->lower;
		while(header!=pivot){
			if(header->node != NULL && pivot->node != NULL){
				if(strcmp(header->id,pivot->id)==0){
					if(header->cardptypes == pivot->cardptypes){
						counter = 0;
						for(i = 0; i < header->cardptypes; i++){
							if(strcmp(header->paramtypes[i],pivot->paramtypes[i])==0){
								counter++;
							}
						}
						if(counter == header->cardptypes){
							if(strcmp(header->id_type,pivot->id_type)==0){
								rep = strdup(pivot->id);
								pivot->id = strdup("REP");
							}
						}
					}
				}
			}else{
				if(strcmp(header->id,pivot->id)==0){
					if(strcmp(header->id_type,pivot->id_type)==0){
						rep = strdup(pivot->id);
						pivot->id = strdup("REP");
					}
				}
			} 
			back = header;
			header = header->lower;
		}
		
		if(strcmp(pivot->id,"_")==0){
			back->lower = header->lower;
			printf("Line %d, col %d: Symbol %s is reserved\n",pivot->line,pivot->col,pivot->id);
		}else if(strcmp(pivot->id,"REP")==0){
			back->lower = header->lower;
			if(strcmp(pivot->id_type,"MethodDecl")==0){
				printf("Line %d, col %d: Symbol %s(",pivot->line,pivot->col,rep);
				for(i=0; i < pivot->cardptypes; i++){
					if(i>0){
						printf(",");
					}
					printf("%s",correctType(pivot->paramtypes[i],NULL));
					
				}
				printf(") already defined\n");
				repeatedheader(pivot);
			}else{
				printf("Line %d, col %d: Symbol %s already defined\n",pivot->line,pivot->col,rep);
			}
		}
		
		pivot = pivot->lower;
	}
	
	pivot = top->lower;
	while (pivot!=NULL) {
		repeatedheader(pivot);
		pivot = pivot->lower;
	}
	
	pivot = top->lower;
	while (pivot!=NULL) {
		repeatedin(pivot);
		pivot = pivot->lower;
	}
	
	
}

void repeatedheader(t_pointer mdecl){
	
	t_pointer temp = mdecl->next;
	t_pointer forward;
	t_pointer back;
	char *rep;
	
	while(temp != NULL){
		
		forward = mdecl->next;
		while(forward != temp){
			if(strcmp(forward->id,temp->id)==0){
				if(forward->param != NULL && temp->param != NULL){
					rep = strdup(temp->id);
					temp->id = strdup("REP");
				}			
			}
			back = forward;
			forward = forward->next;
		}
		
		if(strcmp(temp->id,"_")==0 && temp->param != NULL){
			back->next = forward->next;
			printf("Line %d, col %d: Symbol %s is reserved\n",temp->line,temp->col,temp->id);
		}else if(strcmp(temp->id,"REP")==0){
			back->next = forward->next;
			printf("Line %d, col %d: Symbol %s already defined\n",temp->line,temp->col,rep);
		}
		temp = temp->next;
	}
	

}

void repeatedin(t_pointer mdecl){
	
	t_pointer forward;
	t_pointer back;
	Node *t_temp;
	char *rep;
	int got=0;
	
	if(mdecl->node != NULL){
		t_temp = mdecl->node->sibling->child;
		while(t_temp!=NULL){
			got = 0;
			if(strcmp(t_temp->id,"VarDecl")==0){
				forward = mdecl->next;
				while(forward != t_temp->tnt){
					if(strcmp(forward->id,t_temp->tnt->id)==0){
						rep = strdup(t_temp->tnt->id);
						t_temp->tnt->id = strdup("REP");						
					}
					back = forward;
					forward = forward->next;
				}
				if(strcmp(t_temp->tnt->id,"_")==0){
					back->next = forward->next;
					printf("Line %d, col %d: Symbol %s is reserved\n",t_temp->tnt->line,t_temp->tnt->col,t_temp->tnt->id);
				}else if(strcmp(t_temp->tnt->id,"REP")==0){
					back->next = forward->next;
					printf("Line %d, col %d: Symbol %s already defined\n",t_temp->tnt->line,t_temp->tnt->col,rep);
				}
			}else{
				checkChildErr(t_temp,t_temp);
			}
			
			t_temp = t_temp->sibling;
		}
	}

}

void checkChildErr(Node *t, Node *op){
	
	Node *temp = t;

	if(temp->sibling!=NULL){
		checkChildErr(temp->sibling,op);
	}
	if(temp->child!=NULL){
		checkChildErr(temp->child,temp);
	}
	
}

void statementA(t_pointer top, t_pointer table_root, Node *t){

	int mirror, flip, j;
	int out = 0;
	t_pointer temp;
	Node *inner;
	Node *aux = t;

	flip = 0;
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
							flip = 1;
							aux->child->id_type = strdup(correctType(temp->type,aux));
							aux->id_type = strdup(aux->child->id_type);
						}
					}
				}
				temp = temp->lower;
			}/*------------- correct ---------------*/
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
								flip = 1;
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
			if(flip==0){
				aux->child->id_type = strdup("undef");
				aux->id_type = strdup(aux->child->id_type);
				aux->child->card_p_t = 3;
				strcpy(aux->child->param_t[0],"");
				strcpy(aux->child->param_t[1],"undef");
				strcpy(aux->child->param_t[2],"");

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
						if(node->line >= temp->line){
							node->id_type = strdup(correctType(temp->type,node));
							return temp->type;
						}
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
					if(strcmp(node->type,temp->id)==0 && temp->cardptypes == 0 && strcmp(temp->id_type,"Class")!=0){
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
		new_table_node->col = aux->child->sibling->column;
		new_table_node->line = aux->child->sibling->line;
		new_table_node->cardptypes = 0;
		new_table_node->param = strdup("param");
		t_temp->next = new_table_node;
		t_temp = t_temp->next;
		aux->tnt = new_table_node;

		
		aux = aux->sibling;
	}

	aux = method->sibling->child;
	
	while(aux != NULL){

		if(strcmp(aux->id,"VarDecl")==0){

			new_table_node = (t_pointer)malloc(sizeof(Tabnode));
			new_table_node->id_type = strdup("VarDecl");
			new_table_node->line = aux->child->sibling->line;
			new_table_node->col = aux->child->sibling->column;
			new_table_node->id = strdup(aux->child->sibling->type);
			new_table_node->type = strdup(aux->child->id);
			new_table_node->cardptypes = 0;
			new_table_node->param = NULL;
			t_temp->next = new_table_node;
			t_temp = t_temp->next;
			aux->tnt = new_table_node;
			
		}
		aux = aux->sibling;
	}
				
	
}

void specificTable(Node *node,t_pointer table_root){
	
	int i;
	Node *temp = node->sibling;
	Node *upper;
	Node *st_upper;
	t_pointer t_temp = table_root;
	t_pointer new_table_node;
	char *tp = (char *) malloc(sizeof(char)*32);

	
	while(temp != NULL){

		if(strcmp(temp->id,"FieldDecl")==0){
			tp = strdup(temp->child->id);
			upper = temp->child->sibling;
			st_upper = temp->child;

			new_table_node = (t_pointer)malloc(sizeof(Tabnode));
			new_table_node->id = strdup(upper->type);
			new_table_node->id_type = (char *)malloc(sizeof(char)*16);
			new_table_node->type = strdup(temp->child->id);
			new_table_node->id_type = strdup(temp->id);
			new_table_node->line = upper->line;
			new_table_node->col = upper->column;
			new_table_node->cardptypes = 0;
			new_table_node->lower = NULL;
			new_table_node->next = NULL;
			new_table_node->param = NULL;
			t_temp->lower = new_table_node;
			t_temp = t_temp->lower;
			
		}else if(strcmp(temp->id,"MethodDecl")==0){

			i = 0;
			tp = strdup(temp->child->child->id);
			upper = temp->child->child->sibling;
			st_upper = temp->child;

			new_table_node = (t_pointer)malloc(sizeof(Tabnode));
			new_table_node->id_type = (char *)malloc(sizeof(char)*128);
			strcpy(new_table_node->id_type,temp->id);
			new_table_node->node = st_upper;
			new_table_node->line = upper->line;
			new_table_node->col = upper->column;
			new_table_node->cardptypes = 0;
			new_table_node->id = strdup(upper->type);
			new_table_node->type = strdup(temp->child->child->id);
			new_table_node->lower = NULL;
			new_table_node->next = NULL;

			if(upper->sibling->child != NULL){
				upper = upper->sibling->child;
				strcpy(new_table_node->paramtypes[i],upper->child->id);
				new_table_node->cardptypes++;
				upper = upper->sibling;
				i++;
				while(upper!=NULL){
					strcpy(new_table_node->paramtypes[i],upper->child->id);
					upper = upper->sibling;
					new_table_node->cardptypes++;
					i++;
				}
			}
			
			new_table_node->param = NULL;
			t_temp->lower = new_table_node;
			t_temp = t_temp->lower;
		}

		temp = temp->sibling;
	}

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