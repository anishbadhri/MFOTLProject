#include "mfotl.h"
#include <bits/stdc++.h>
using namespace std;
//------------------------------------------------------OOP CODE---------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------
bool Formula::ftree_convert()
{
	int len=0;
	int i,j;

	int done=-1;
	int in=0;

	bool flag=0;

	string var;
	string var1;
	string client1;

	string var2;
	string client2;
	
	stack<FTree*> for_stack;	
	stack<FTree*> op_stack;

//op_stack should ideally be char stack to allow '(' to be pushed.
//for_stack has to be FTree* stack


	FTree* for_node_n;
	FTree* for_node_l;
	FTree* for_node_r;
	FTree* for_node;

	FTree* op_node;
	FTree* new_op_node;

	cout << "We are in the formula to tree conversion routine.\n";

//initialize the client type no. to zero
//this will be computed and updated here using the two add_to_formula_info methods. 

	NoOfCltTypes=0;

	cout <<"\nThe input formula is:->" << FormulaText << endl;

	len=FormulaText.length();
	cout<<"\nLength of the formula is:-> " << len << endl;
	i=0;
	while(i<len)
	{
		cout<<"\nLooking at the " << i << "th symbol of the formula:" << FormulaText[i]<< endl;
		//looking at FormulaText[i]
		switch(isoperator(FormulaText[i])){//we expect operators to be single letter symbols, including ( and ).
		 case 1:
			cout<<FormulaText[i]<< "is an operator\n";
//Presently the op_prcd method does nothing but differentiate (, ) and other operators. This is so as input is fully parenthesized.
//We will need operator precedence once we remove this constraint on the input.
			switch(op_prcd(FormulaText[i])){
				case 0://**(** do nothing
					cout<<"\nWe are looking at the symbol:" << FormulaText[i];
					cout<<"\nIgnore, move to the next symbol\n";
					++i;
					continue;
				case 1://**)**
					cout<<"\nWe are looking at the symbol:" << FormulaText[i];
					//getchar();
//-----------------------------------------------------------------------------------------------------------------------------
//")" can be encountered in three different places 1. p(x) or p(x:i) 2. (x=y) or (x:i=y:j) 3. (\alpha op \beta) where op can 
//be | or & or (~\alpha). we consider the third case here. second case is considered elsewhere.
//-----------------------------------------------------------------------------------------------------------------------------
					if(FormulaText[i-1]==')'){//look at the operator on the top of the operation stack 
//and accordingly construct a tree by taking one or more operands from the operand stack
						cout<<"\npop an operator from the op stack\ncheck whether it is unary or binary\n";
						fflush(stdout);
						if(!op_stack.empty()){
							op_node=op_stack.top();
							op_stack.pop();
						}
						else{
							cout << "\nThere is some problem.\n";
							cout << "\nWe are trying to access an empty op_stack\n";
							return 0;
						}
						cout<<"\nThe operator is:->" << op_node->val;
						fflush(stdout);
						switch(op_type(op_node->val[0])){
							case 1://unary operator
								cout<<"\nif unary, pop a subformula from the formula stack\n";
								if(!for_stack.empty()){
									for_node_n=for_stack.top();
									for_stack.pop();
								}
								else{
									cout << "\nThere is some problem.\n";
									cout << "\nWe are trying to access an empty for_stack\n";
									return 0;
								}
								display_ft(for_node_n);

								op_node->next=for_node_n;
								op_node->type=1;//for unary operator
								op_node->model=-1;//
								op_node->copy=-1;//
								op_node->subd=0;//
								op_node->num=-1;
								op_node->client=for_node_n->client;

								cout<<"\nConstructed a larger subformula\n";
								display_ft(op_node);
								cout<<"\npush the new subformula node onto the formula stack...\n";

								for_stack.push(op_node);
								//display_for_stack();

								i++;
								continue;


							case 2://binary operator
								cout<<"\nif binary, pop two subformulas from the formula stack\n";
								if(for_stack.empty()){
									cout << "\nThere is some problem.\n";
									cout << "\nWe are trying to access an empty stack.\n";
									return 0;
								}
								for_node_r=for_stack.top();for_stack.pop();
								display_ft(for_node_r);
								cout << "\n";
								if(for_stack.empty()){
									cout << "\nThere is some problem.\n";
									cout << "\nWe are trying to access an empty stack.\n";
									return 0;
								}
								for_node_l=for_stack.top();for_stack.pop();
								display_ft(for_node_l);
								cout << "\n";

								op_node->left=for_node_l;
								op_node->right=for_node_r;
								op_node->type=2;//for binary operator
								op_node->model=-1;//
								op_node->copy=-1;//
								op_node->subd=0;//
								op_node->num=-1;

								op_node->client=for_node_l->client;

								cout<<"\nConstructed a larger subformula\n";
								display_ft(op_node);
								cout << "\n";

								cout<<"\npush the new subformula node onto the formula stack...\n";
								for_stack.push(op_node);
								//display_for_stack();

								i++;
								continue;
							case 3://quantifiers
								cout<<"\nif quantifier, pop a subformula from the formula stack\n";
								if(for_stack.empty()){
									cout << "\nThere is some problem.\n";
									cout << "\nWe are trying to access an empty stack.\n";
									return 0;
								}
								for_node_n=for_stack.top();for_stack.pop();
								display_ft(for_node_n);
								cout << "\n";

//make sure that formula is correctly popped from the formula stack.
								op_node->next=for_node_n;
								op_node->type=3;//for quantifiers
								op_node->model=-1;//
								op_node->copy=-1;//
								op_node->subd=0;//
								op_node->num=-1;

								op_node->client=for_node_n->client;

								cout<<"\nConstructed a larger subformula\n";
								display_ft(op_node);
								cout << "\n";


								cout<<"\npush the new subformula node onto the formula stack...\n";
								for_stack.push(op_node);
								//display_for_stack();

								i++;
								continue;
//the following case of predicate should not occur.
//we have aleady constructed a tree for pred(var:client) and pushed onto formula stack
							case 4://predicates
								cout<<"\nif predicate, pop a subformula from the formula stack\n";
								if(for_stack.empty()){
									cout << "\nThere is some problem.\n";
									cout << "\nWe are trying to access an empty stack.\n";
									return 0;
								}
								for_node_n=for_stack.top();for_stack.pop();
								display_ft(for_node_n);
								cout << "\n";

//make sure that formula is correctly popped from the formula stack.
								op_node->next=for_node_n;
								op_node->type=4;//for quantifiers
								op_node->model=-1;//
								op_node->copy=-1;//
								op_node->subd=0;//
								op_node->num=-1;
								op_node->client=for_node_n->client;

								cout<<"\nConstructed a larger subformula\n";
								display_ft(op_node);
								cout << "\n";

								cout<<"\npush the new subformula node onto the formula stack...\n";
								for_stack.push(op_node);
								//display_for_stack();

								i++;
								continue;
						}//end of switch(op_type(op_node->val[0]))

					
					}//end of if(FormulaText[i-1]==')')
					else{//do nothing
					//this is the case when we encounter closing paranethesis of (x=y)
						cout<<"\nIgnored the " << i << "th symbol " << FormulaText[i] << endl;
						i++;
						continue;
					}

				case 2:	//if FormulaText[i] is not left or right bracket but an operator (~,&,|,E,A) then construct an internal node and store in the stack, it is an operator proper ~,&,|, et. al.
					cout<<"\nLooking at a real operator:" << FormulaText[i]<< endl;
					fflush(stdout);
					new_op_node= new FTree;
					if(new_op_node==NULL){
						//cout<<"\nMemory Allocation Error\n";
						exit(1);
					}
					//cout<<"\nConstructed a tree node to store %c with pointer %p",FormulaText[i],new_op_node);
					fflush(stdout);

					new_op_node->val=FormulaText[i];
					new_op_node->model=-1;
					new_op_node->copy=-1;
					new_op_node->subd=0;
					new_op_node->num=-1;

					new_op_node->parent=NULL;
					new_op_node->right=NULL;
					new_op_node->left=NULL;
					new_op_node->next=NULL;

					new_op_node->client.clear();

					switch(op_type(new_op_node->val[0])){
						case 1: cout<< "\nUnary Operator\n";
							new_op_node->type=1;//unary operator
							//new_op_node->val[1]='\0';---no longer needed
							i++;
							op_stack.push(new_op_node);
							break;
							
						case 2: cout<< "\nBinary Operator\n";
							new_op_node->type=2;//binary operator
							//new_op_node->val[1]='\0';--no longer needed
							i++;
							op_stack.push(new_op_node);
							break;

						case 3: cout<< "\nQuantifier\n";
							new_op_node->type=3;//quantifier
							cout << "\nType field updated.\n";fflush(stdout);
//FormulaText[i] is either E or A. We expect it to be followed by variable or variable:client-type
							j=1;
							flag=0;
							in=0;
//The following loop is needed--we read from FormulaText and construct val field for the FTree nod for quantifier
							while(FormulaText[i+j]!='(' && FormulaText[i+j]!=')'){
								new_op_node->val.push_back(FormulaText[i+j]);
								if(FormulaText[i+j]==':') {
									flag=1;
									in=j;
								}
								j++;
							}
							//new_op_node->val[j]='\0';--no longer needed
							cout << "Value field updated.\n";fflush(stdout);
							if(!flag){//flag is false						
								new_op_node->client.clear();//no client info
								
							}
							else{//flag is true
//i think the following for loop can be replaced by a single string manipulation. i need to check;
//yes we can use substr method---string& substr(position,length);
								new_op_node->client.clear();
								//for(int k=in+1; k<=j;k++){
								//	new_op_node->client.push_back(new_op_node->val[k]);
								//}
								new_op_node->client=new_op_node->val.substr(in+1,new_op_node->val.length()-in-1);
							}
							cout<< "\nClient field updated.\n";fflush(stdout);
							i=i+j;
							op_stack.push(new_op_node);
							break;

						case 4: cout<< "\nMonadic Predicate\n";
							new_op_node->type=4;//monadic predicate p(var:client)
							j=1;
							while(FormulaText[i+j]!='('){
//we expect predicate p/q/r to be followed with only digits
								new_op_node->val.push_back(FormulaText[i+j]);
								j++;
							}
							//new_op_node->val[j]='\0';--no longer needed
//in order to add predicate to formula_info we need client type.
//clearly the predicate should be followed by variable or variable:client-type enclosed in ().
							i=i+j+1;							
							j=0;	
							flag=0; in=0;
							var.clear();
							while(FormulaText[i+j]!=')'){
								var.push_back(FormulaText[i+j]);
								if(FormulaText[i+j]==':') {flag=1;in=j;}
								j++;
							}
							//var[j]='\0';--no longer needed
							if(!flag){//flag is false						
								new_op_node->client.clear();//no client info
								
							}
							else{//flag is true
//i think the following for loop can be replaced by a single string manipulation. i need to check;
								new_op_node->client.clear();
								//for(int k=in+1; k<=j;k++){
								//	new_op_node->client.push_back(var[k]);
								//}
								//var[in]='\0';--no longer needed
								new_op_node->client=var.substr(in+1,var.length()-in-1);
							}
							i=i+j+2;
							add_predicate_to_formula_info(new_op_node->val,new_op_node->client);
//							if(done)
//								formula_info->PNum++;
//we should also add a variable to formula_info	
							FTree* new_for_node= new FTree;
							if(new_for_node==NULL){
								//cout<<"\nMemory Allocation Error\n";
								exit(1);
							}
							//cout<<"\nConstructed a tree node to store %c with pointer %p",FormulaText[i],new_op_node);
							fflush(stdout);

		//					new_op_node->global=0;
							new_for_node->val=var;
							new_for_node->model=-1;
							new_for_node->copy=-1;
							new_for_node->subd=0;
							new_for_node->num=-1;
							new_for_node->client=new_op_node->client;
							add_variable_to_formula_info(new_for_node->val,new_for_node->client);
					
							new_op_node->next=new_for_node;	
							for_stack.push(new_op_node);	
							break;

					}//end of switch(op_type(new_op_node->val[0]))
					//cout<<"\nLabel for internal node is %s",new_op_node->val);
					fflush(stdout);			
					
					//cout<<"\npush the new op node onto the stack...............\n";
					//display_op_stack();
					continue;

			
			}//end of switch(op_prcd(FormulaText[i]))
		 	continue;
//-------------------end of case 1 for isoperator----------------------------------------------------
		 case 0: //FormulaText[i] is not an operator
			//cout<<"\n%c is not an operator",FormulaText[i]);
			fflush(stdout);
//in this case, we shall encounter a variable only as a part of = (equality) subformula.
//the other two possibilities, variable along with E or A and variable along with predicate we have already taken care of.

			//construct token
			if(FormulaText[i-1]=='('||FormulaText[i-1]=='='){
				var1.clear();//initialize the token if the preceding character is '('
				//cout<<"\nInitialized the token.\nWe have to read the full variable.\n";
				fflush(stdout);
			}
			else{
				//cout<<"\nThere is some problem with the structure of the input. Exiting.......;
				fflush(stdout);
				exit(1);
			}
			//cout<<"\nwe are here.1\n";
			//fflush(stdout);
			flag=0;
			j=i;
			while(FormulaText[j]!='='&& FormulaText[j]!='!' && FormulaText[j]!=':' && FormulaText[j]!=')' ){
				var1.push_back(FormulaText[j]);
				j++;
				//cout<<"\nAdding %c to the token\n",FormulaText[j-1]);
				//getchar();
				//cout<<"\nwe are here.\n";
				fflush(stdout);

			}
			//var1[j-i]='\0';--no longer needed

			//cout<<"\nwe are here.2\n";
			//fflush(stdout);

//token carries a variable now. we have to make sure two things at this point, 
//1: is there any client info, 2: is it an equality formula or inequality formula

			
			client1.clear();
			if(FormulaText[j]==':'){
				//there is client info. we need to store it in client1
				i=++j;
				while(FormulaText[j]!='='&& FormulaText[j]!='!' && FormulaText[j]!=')'){
					client1.push_back(FormulaText[j]);
					j++;
					//cout<<"\nAdding %c to the token\n",FormulaText[j-1]);
					//getchar();
					//cout<<"\nwe are here.\n";
					fflush(stdout);

				}
				//client1[j-i]='\0';--no longer needed
			}
						
			switch(FormulaText[j]){
				case '!':	flag=0;
						i=j+2;
						break;	
						
				case '=':	flag=1;
						i=j+1;
						break;

				default:	cerr << "\nError in input. Exiting";
						exit(1);

			}			

			for_node_l=new FTree;
			if(for_node_l==NULL){
				//cout<<"\nMemory Allocation Error\n";
				exit(1);
			}
			for_node_l->type=0;
			for_node_l->val=var1;
			for_node_l->client=client1;
			//cout<<"\nwe are here.\n";
			fflush(stdout);
			add_variable_to_formula_info(for_node_l->val,for_node_l->client);
			//cout<<"\nwe are here.\n";
			fflush(stdout);
//			if(done){
				//cout<<"\nSuccessfully added a variable to the VList.\n"; 
//				formula_info->VNum++;
//			}
			//cout<<"\nThe label for leaf node is %s with pointer %p\n",for_node->val,for_node);
			fflush(stdout);
			for_node_l->parent=NULL;
			for_node_l->right=NULL;
			for_node_l->left=NULL;
			for_node_l->next=NULL;

			for_node_l->model=-1;
			for_node_l->copy=-1;
			for_node_l->subd=0;
			for_node_l->num=-1;

//			for_stack.push(for_node);
			//cout<<"\npush the new leaf node onto the stack...............\n";
			fflush(stdout);

//now we compute the second part of the equality (inequality)
			if(FormulaText[i-1]=='='){
				var2.clear();//initialize the token if the preceding character is '('
				//cout<<"\nInitialized the token.\nWe have to read the full variable.\n";
				fflush(stdout);
			}
			else{
				//cout<<"\nThere is some problem with the structure of the input. Exiting.......;
				fflush(stdout);
				exit(1);
			}
			//cout<<"\nwe are here.1\n";
			//fflush(stdout);
			
			j=i;
			while(FormulaText[j]!=':' && FormulaText[j]!=')' ){
				var2.push_back(FormulaText[j]);
				j++;
				//cout<<"\nAdding %c to the token\n",FormulaText[j-1]);
				//getchar();
				//cout<<"\nwe are here.\n";
				fflush(stdout);

			}
			//var2[j-i]='\0';-- no longer needed

			//cout<<"\nwe are here.2\n";
			//fflush(stdout);

//token carries a variable now. we have to make sure two things at this point, 
//1: is there any client info, 2: is it an equality formula or inequality formula

			
			client2.clear();
			if(FormulaText[j]==':'){
				//there is client info. we need to store it in client1
				i=++j;
				while(FormulaText[j]!=')'){
					client2.push_back(FormulaText[j]);
					j++;
					//cout<<"\nAdding %c to the token\n",FormulaText[j-1]);
					//getchar();
					//cout<<"\nwe are here.\n";
					fflush(stdout);

				}
				//client2[j-i]='\0';--no longer needed
			}
						
			for_node_r=new FTree;
			if(for_node_r==NULL){
				//cout<<"\nMemory Allocation Error\n";
				exit(1);
			}
			for_node_r->type=0;
			for_node_r->val=var2;
			for_node_r->client=client2;
			//cout<<"\nwe are here.\n";
			fflush(stdout);
			add_variable_to_formula_info(for_node_r->val,for_node_r->client);
			//cout<<"\nwe are here.\n";
			fflush(stdout);
//			if(done){
				//cout<<"\nSuccessfully added a variable to the VList.\n"; 
//				formula_info->VNum++;
//			}
			//cout<<"\nThe label for leaf node is %s with pointer %p\n",for_node->val,for_node);
			fflush(stdout);
			for_node_r->parent=NULL;
			for_node_r->right=NULL;
			for_node_r->left=NULL;
			for_node_r->next=NULL;

			for_node_r->model=-1;
			for_node_r->copy=-1;
			for_node_r->subd=0;
			for_node_r->num=-1;

//			for_stack.push(for_node);
			//cout<<"\npush the new leaf node onto the stack...............\n";
			fflush(stdout);	

//--------------------------------------------------------------------------------------------------------			
//at this point, we construct a subtree rooted at "=" or "!=" as a special case
			fflush(stdout);
			op_node=new FTree;
			if(op_node==NULL){
				//cout<<"\nMemory Allocation Error\n";
				exit(1);
			}
			if(flag==0)
				op_node->val="!=";
			else
				op_node->val="=";
			//cout<<"\nThe operator is %s\n",op_node->val);
			fflush(stdout);
			op_node->left=for_node_l;
			op_node->right=for_node_r;
			op_node->type=2;//for binary operator
			op_node->model=-1;//
			op_node->copy=-1;//
			op_node->subd=0;//
			op_node->num=-1;
			op_node->client.clear();

			//cout<<"\npush the new subformula node onto the formula stack ...............\n";
			for_stack.push(op_node);


			i=j+1;
			continue;

//-------------------end of case 0 for isoperator----------------------------------------------------
		 case -1:
			//cout<<"\nThere is an error in the input. Exiting...........;
			exit(1);
//-------------------end of case -1 for isoperator----------------------------------------------------
		}//end of switch-case(isoperator(FormulaText[i]))
	}//end of while(i<len)
//	for_node=for_stack.top();for_stack.pop();
	FormulaTree=for_stack.top();for_stack.pop();
//print the number of client types.
	cout << "\nThe no. of client types mentioned in the formula is: " << NoOfCltTypes << endl;
	if(FormulaTree!=NULL)
		return 1;
	else
		return 0;
}//end of ftree_convert
//---------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------
void Formula::add_predicate_to_formula_info(string pred,string client)
{
	string PE;
//Note that pred does not contain client info.
	PE=pred;
	PE.append(":");
	PE.append(client);
	PE.shrink_to_fit();//works with --std=c++11

	if(PredList.find(PE)==PredList.end())//PE is not in the set PredList
	{
		PredList.insert(PE);
		if(PredNum.find(client)==PredNum.end()){//No entry for client in the map PredNum
			cout << "\nInitializing the entry for " << client << " in map PredNum.\n";
			cout << "\nRegistering a new client type.\n";
			//getchar();
			//cout << "\nLength of client is: " << strlen(client)<< endl;
			PredNum[client]=1;
		}
		else{
			cout << "\nIncrementing the entry for " << client << " in map PredNum.\n";
			//getchar();
			//cout << "\nLength of client is: " << strlen(client)<< endl;
			PredNum[client]=PredNum[client]+1;
		}
	}

}

//--------------------------------------------------------------------------------------------------
void Formula::add_variable_to_formula_info(string VE,string client)
{
//	string VE;
//Note that var contains both variable as well as client info.
//	VE=var;
//	VE.append(":");
//	VE.append(client);
	VE.shrink_to_fit();//works with --std=c++11

	if(VarList.find(VE)==VarList.end())//VE is not in the set VarList
	{
		VarList.insert(VE);
		cout << "\nInserting variable " << VE << " in the list.\n";
		//getchar();
		if(VarNum.find(client)==VarNum.end()){//No entry for client in the map VarNum
			cout << "\nInitializing the entry for " << client << " in map VarNum.\n";
			//getchar();
			//cout << "\nLength of client is: " << strlen(client)<< endl;
			VarNum[client]=1;
//register a new client type
			NoOfCltTypes++;

		}
		else{
			cout << "\nIncrementing the entry for " << client << " in map VarNum.\n";
			//getchar();
			//cout << "\nLength of client is: " << strlen(client)<< endl;
			VarNum[client]=VarNum[client]+1;
		}
	}


}
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
bool Formula::quant_elim()
{
	QEFTree=eliminate_quantifier(FormulaTree);
	if(QEFTree!=NULL)
		return 1;
	else 
		return 0;
}

//---------------------------------------------------------------------------------------------------

FTree* Formula::eliminate_quantifier(FTree* TF)
{

	FTree* root=NULL;
	FTree* new_root=NULL;
	FTree* old_root=NULL;

	FTree* new_subformula=NULL;
	FTree* SubdTFnext=NULL;

	string var;
	int i,j,k;

	int M;
	int R;
	string client;
	bool flag=0;
	int in=0;

	
//We can not have  global M and R. It depends on client type.


//	//getchar();

	cout << "\n\n\nWe are in quantifier elimination routine....";
	cout << "Looking at the following subformula:";
	display_ft_pre(TF);
	cout<<"\n";

	//cout<<"\nIn infix form:;
	//display_ft(TF);
	//cout<<"\n";
	
	display_lists();
	display_nums();

	client=TF->client;
	int PredVal=PredNum[client];
	int VarVal=VarNum[client];
	cout << "The client name is: "<< client<< endl;
	cout<<"\nThe no. of predicates for client "<< client<< " is: " << PredVal << endl;
	cout<<"\nThe no. of variables is: " << VarVal << endl;
//compute M and R for the client type of E
	M=1 << PredVal;
	R=VarVal;
	cout<<"\n\nThe no. of models for client "<< client<< " is: " << M << endl;
	cout<<"\n\nThe no. of copies of models is: " << R << endl;

	//getchar();

	//we traverse the formula tree and replace Ex subtree by 2^M-1 'or' subtrees and replace Ax subtree by 2^M-1 'and' subtrees.
	switch(TF->type)
	{
		case 0:// type variable 
				return TF;

		case 1:// type unary connective
				TF->next=eliminate_quantifier(TF->next);
				return TF;

		case 2:// type binary connective
				TF->right=eliminate_quantifier(TF->right);
				TF->left=eliminate_quantifier(TF->left);
				return TF;

		case 3:// type quantifier
				switch(TF->val[0])
				{
					case 'E': 	//replace TF tree with Ev at root by an 'or' rooted tree
							//TF->val contains string Evar. we need to extract var
							//k=1;
							var.clear();
							var=TF->val.substr(1,TF->val.length()-1);
							//while(k<size){
							//	var.push_back(TF->val[k]);
							//	k++;
							//}
							//var[k-1]='\0';--no longer needed
							cout << "\neliminating E over the variable " << var << endl;
							cout << "\nAfter eliminating quantifiers from the sub-formula:  ";
							display_ft_pre_sub(TF->next);
							
							SubdTFnext=eliminate_quantifier(TF->next);
							cout<<"\n\nWe get the following formula:   ";
							display_ft_pre_sub(SubdTFnext);
							cout<<"\n\n";
							//getchar();
//------------------------------------------------------------------------------------------------------------------------------
//At this point we should do a sanity check. If var does not occur in SubdTFnext, we should return TF with TF->next=SubdTFnext.
//------------------------------------------------------------------------------------------------------------------------------
							//cout<<"\nEliminating an existential quantifier E" << var<< endl;


							//client=TF->client;
							//cout<<"\nThe no. of predicates for client "<< client<< " is: " << PredNum[client] << endl;
							//cout<<"\nThe no. of variables is: " << VarNum[client] << endl;
//compute M and R for the client type of E
							//M=1 << PredNum[client];
							//R=VarNum[client];
							//cout<<"\nThe no. of models for client "<< client<< " is: " << M << endl;
							//cout<<"\nThe no. of copies of models is: " << R << endl;

							//getchar();
//-----------------------------------no problem till here-----------------------------------------------------------------
							for(int i=0;i<M;i++){
								for(int j=0;j<R;j++){
									if(i==0 && j==0){
										root=new FTree;
										root->val="|";
										root->type=2;
										root->client=client;
										cout << "\nConstructing a copy of the subformula.......\n";
										new_subformula=copy(SubdTFnext);

										cout<<"\nCopy of the subformula with free variable " << var;
										display_ft_pre_sub(new_subformula);
										cout<<"\n";

										cout<<"\n\nReplacing "<< var << " by " << R*i+j << " in the above formula\n\n";
										//getchar();

										substitute(new_subformula,var,0,0,R*0+0);

										cout<<"\nThe substituted subformula is:";
										display_ft_pre_sub(new_subformula);
										cout<<"\n\n";

										root->left=new_subformula;
										root->right=NULL;

										cout<<"\nThe partially quantifier eliminated formula is:";
										display_ft_pre_sub(root);
										cout<<"\n\n";

										old_root=root;
									}
									else if(i==M-1 && j==R-1){
										new_subformula=copy(SubdTFnext);

										cout<<"\nCopy of the subformula with free variable " << var;
										display_ft_pre_sub(new_subformula);
										cout<<"\n";

										cout<<"\n\nReplacing "<< var << " by " << R*i+j << " in the above formula\n\n";
										//getchar();

										substitute(new_subformula,var,i,j,R*i+j);

										cout<<"\nThe substituted subformula is:";
										display_ft_pre_sub(new_subformula);
										cout<<"\n\n";

										old_root->right=new_subformula;

										cout<<"\nThe partially quantifier eliminated formula is:";
										display_ft_pre_sub(old_root);
										cout<<"\n\n";

									}
									else{
										new_root=new FTree;
										new_root->val="|";
										new_root->type=2;
										new_root->client=client;

										new_subformula=copy(SubdTFnext);

										cout<<"\nCopy of the subformula with free variable " << var;
										display_ft_pre_sub(new_subformula);
										cout<<"\n";

										cout<<"\n\nReplacing "<< var << " by " << R*i+j << " in the above formula\n\n";
										//getchar();

										substitute(new_subformula,var,i,j,R*i+j);

										cout<<"\nThe substituted subformula is:";
										display_ft_pre_sub(new_subformula);
										cout<<"\n";

										new_root->left=new_subformula;
										new_root->right=NULL;

										cout<<"\nThe partially quantifier eliminated formula is:";
										display_ft_pre_sub(root);
										cout<<"\n\n";

										old_root->right=new_root;
										old_root=new_root;
									}
								}//end of for-j
							}//end of for-i
							return root;




					case 'A':	//replace TF tree with Av at root by an 'and' rooted tree

							var.clear();
							var=TF->val.substr(1,TF->val.length()-1);
							//k=1;
							//while(TF->val[k]!='\0'){
							//	var[k-1]=TF->val[k];
							//	k++;
							//}
							//var[k-1]='\0';
							//cout<<"\nEliminating an universal quantifier A%s\n",var);
							
							//client=TF->client;
//compute M and R for the client type of A
							//M=1 << PredNum[client];
							//R=VarNum[client];

							SubdTFnext=eliminate_quantifier(TF->next);

							//cout<<"\nAfter eliminating quantifiers from the sub-formula:;
							//display_ft_pre_sub(SubdTFnext);
							//cout<<"\n\n";							
							//getchar();

//------------------------------------------------------------------------------------------------------------------------------
//At this point we should do a sanity check. If var does not occur in SubdTFnext, we should return TF with TF->next=SubdTFnext.
//------------------------------------------------------------------------------------------------------------------------------


							for(int i=0;i<M;i++){
								for(int j=0;j<R;j++){
									if(i==0 && j==0){
										root=new FTree;
										root->val="&";
										root->type=2;
										root->client=client;

										new_subformula=copy(SubdTFnext);

										//cout<<"\nCopy of the subformula with free variable %s:",var);
										//display_ft_pre_sub(new_subformula);
										//cout<<"\n";
										//getchar();

										substitute(new_subformula,var,0,0,R*0+0);

										//cout<<"\nThe substituted subformula is:;
										//display_ft_pre_sub(new_subformula);
										//cout<<"\n";

										root->left=new_subformula;

										//cout<<"\nThe partially quantifier eliminated formula is:;
										//display_ft_pre_sub(root);
										//cout<<"\n";

										old_root=root;
									}
									else if(i==M-1 && j==R-1){
										new_subformula=copy(SubdTFnext);

										//cout<<"\nCopy of the subformula with free variable %s:",var);
										//display_ft_pre_sub(new_subformula);
										//cout<<"\n";
										//getchar();

										substitute(new_subformula,var,i,j,R*i+j);

										//cout<<"\nThe substituted subformula is:;
										//display_ft_pre_sub(new_subformula);
										//cout<<"\n";

										old_root->right=new_subformula;

										//cout<<"\nThe partially quantifier eliminated formula is:;
										//display_ft_pre_sub(old_root);
										//cout<<"\n";

										
									}
									else{
										new_root=new FTree;
										new_root->val="&";
										new_root->type=2;
										new_root->client=client;

										new_subformula=copy(SubdTFnext);

										//cout<<"\nCopy of the subformula with free variable %s:",var);
										//display_ft_pre_sub(new_subformula);
										//cout<<"\n";

										//getchar();

										substitute(new_subformula,var,i,j,R*i+j);

										//cout<<"\nThe substituted subformula is:;
										//display_ft_pre_sub(new_subformula);
										//cout<<"\n";

										new_root->left=new_subformula;
										old_root->right=new_root;

										//cout<<"\nThe partially quantifier eliminated formula is:;
										//display_ft_pre_sub(root);
										//cout<<"\n";

										old_root=new_root;
									}
								}
							}
							return root;


					default: 	//cout<<"\nThere is an error in the subformula.\nWe expected a quantifier.\n";
							return 0;
				}			

		case 4:// type predicate
				return TF;

	}
}
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
FTree* Formula::copy(FTree* TF)
{

	 FTree* new_leaf=NULL;
	 FTree* new_node=NULL;
	 FTree* new_subtree=NULL;
	 FTree* new_l_subtree=NULL;
	 FTree* new_r_subtree=NULL;

	//cout<<"\nIn the copy routine for:";
	//display_ft_pre_sub(TF);
	if(TF==NULL){
		cout<<"\nError in the formula tree.\n";
		return(NULL);
	}
			//cout<<"\nThe formula to copy (in prefix form);
			//display_ft_pre_sub(TF);	
			fflush(stdout);

	switch(TF->type){
		case 2: //cout<<"\nThe node type is %d",TF->type);
			new_l_subtree=copy(TF->left);
			new_r_subtree=copy(TF->right);

			new_node=new FTree;
			if(new_node==NULL){
				//cout<<"\nError in memory allocation\nExiting\n";
				exit(0);
			}
			new_node->type=2;
			new_node->subd=0;
			new_node->model=-1;
			new_node->copy=-1;
			new_node->num=-1;

			new_node->val=TF->val;
			new_node->client=TF->client;
			new_node->left=new_l_subtree;
			new_node->right=new_r_subtree;
			new_node->next=NULL;
			return(new_node);
		case 3:
		case 4:
		case 1: //cout<<"\nThe node type is %d",TF->type);
			fflush(stdout);
			new_subtree=copy(TF->next);
			new_node=new FTree;
			if(new_node==NULL){
				//cout<<"\nError in memory allocation\nExiting\n";
				exit(0);
			}
			new_node->type=TF->type;
			new_node->subd=0;
			new_node->model=-1;
			new_node->copy=-1;
			new_node->num=-1;

			new_node->val=TF->val;
			new_node->client=TF->client;

			new_node->left=NULL;
			new_node->right=NULL;
			new_node->next=new_subtree;
			return(new_node);

		case 0: //cout<<"\nThe node type is :" << TF->type;
			fflush(stdout);
			new_leaf=new FTree;
			if(new_leaf==NULL){
				cout<<"\nError in memory allocation\nExiting\n";
				exit(0);
			}
			new_leaf->type=0;
			new_leaf->subd=TF->subd;
			new_leaf->model=TF->model;	
			new_leaf->copy=TF->copy;
			new_leaf->num=TF->num;

			new_leaf->val=TF->val;
			new_leaf->client=TF->client;

			new_leaf->left=NULL;
			new_leaf->right=NULL;
			new_leaf->next=NULL;
			cout << "\n\n";
			return(new_leaf);		
			

		default:
			//cout<<"\nError! Type can either be 0, 1 or 2.\n";
			break;

	}
}
//--------------------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------------------------
void Formula::substitute(FTree* TF,string var, int i, int j,int k)
{
//	//cout<<"\nReplacing %s by (%d,%d) recursively in the formula:",var,i,j);
//	//display_ft_pre(TF);
//	//cout<<"\n";
	if(TF==NULL){
		//cout<<"\nFormula is NULL\nThis should not have happened.\n";
		fflush(stdout);
		return;
	}
	switch(TF->type)
	{
		case 0:		if(TF->val==var && TF->subd ==0){
					//cout<<"We are replacing %s by (%d,%d) at the leaf level\n",TF->val,i,j);
					TF->model=i;
					TF->copy=j;
					TF->num=k;
					TF->subd=1;
				}
				return;

		case 2:		substitute(TF->left,var,i,j,k);
				substitute(TF->right,var,i,j,k);
				return;	

		case 1:
		case 3:
		case 4:
				substitute(TF->next,var,i,j,k);
				return;
	}
}
//---------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------
int Formula::op_type(char symbol)
{
 switch (symbol)
 {
//-------------------------UNARY------------------------------------- 
 case '~'://NOT

 case 'X'://NEXT
 case 'Y'://ONE-STEP PAST

 case 'F'://DIAMOND
 case 'G'://BOX

 case 'P'://DIAMOND MINUS
 case 'Q'://BOX MINUS


	return 1;
//-------------------------BINARY-------------------------------------
 case '|'://OR
 case '&'://AND
 case '='://EQUALS

 case 'U'://UNTIL
 case 'V'://RELEASE
	return 2;
//------------------------QUANTIFIERS---------------------------------
 case 'E':
 case 'A':
	return 3;

//------------------------MONADIC PREDICATES----------------------------------
 case 'p':
 case 'q':
 case 'r':
 case 's':
 case 't':
	return 4;
 }
}
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
int Formula::op_prcd(char symbol)
{
 switch (symbol)
 {
//-------------------------UNARY------------------------------------- 
 case '~'://NOT

 case 'X'://NEXT
 case 'Y'://ONE-STEP PAST

 case 'F'://DIAMOND
 case 'G'://BOX

 case 'P'://DIAMOND MINUS
 case 'Q'://BOX MINUS

 case 'E':
 case 'A':

 case 'p':
 case 'q':
 case 'r':
 case 's':
 case 't':

//-------------------------BINARY-------------------------------------
 case '|'://OR
 case '&'://AND
 case '='://EQUALS

 case 'U'://UNTIL
 case 'V'://RELEASE
	return 2;

 case '(':
	return 0;
 case ')':
 	return 1;
 }
 
}
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
int Formula::isoperator(char symbol)
{
 switch (symbol)
 {
 	case '~'://~,V,&,X,U,R,P,Q,Y,F,G
 	case '|':
 	case '&':
 	case '=':
 	
 	case 'X':
 	case 'Y':
 	case 'U':


 	case 'V':
 	case 'F':
 	case 'G':
 	case 'P':
 	case 'Q':

 	case 'E':
 	case 'A':
	
 	case 'p':
 	case 'q':
 	case 'r':
 	case 's':
 	case 't':

 	case '(':
 	case ')':
 		return 1;//non-variables
 	case 'x':
 	case 'y':
 	case 'z':
 		return 0;//variables

	default: 
		return -1;//illegal input
 }

}
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------



//FUNCTIONS AND VARIABLES ADDED TO LINK FILES
vector<int> Formula::get_counters()
{
	map<string,int>::iterator it1,it2;
	vector<int> set_counters;
	for(it1 = PredNum.begin();it1 != PredNum.end(); ++it1)
	{
		string client_temp = it1->first;
		it2 = VarNum.find(client_temp);
		if(it2 == VarNum.end())
		{
			//cout<<"Error Occured\n";
			exit(0);
		}
		int NoOfPred = it1->second;
		int NoOfVars = it2->second;
		int current_counter = NoOfVars * pow(2,NoOfPred);
		set_counters.push_back(current_counter);
	}
	return set_counters;
}

string Formula::get_expression()
{
	string expression = "";
	display_ft_sub2(QEFTree,expression);
	return expression;
}