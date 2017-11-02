#include "mfotl.h"
#include<iostream>
using namespace std;
//---------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------OOP CODE---------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
void Formula::display_lists()
{


	set <string> :: iterator setIter;
	
	//cout << "\nPredicate List.\n";

	for(setIter=PredList.begin();setIter!=PredList.end();setIter++);
		//cout << *setIter << endl;

	//cout << "\nVariable List.\n";

	for(setIter=VarList.begin();setIter!=VarList.end();setIter++);
		//cout << *setIter << endl;

}
void Formula::display_nums()
{

	map <string,int> :: iterator mapIter;

	//cout << "\nPredicates... \nClient type: No. of Predicates\n";
	int i=1;
	for(mapIter=PredNum.begin();mapIter!=PredNum.end();mapIter++){
		//cout<< i++ <<"th entry->" << mapIter->first << "(Client Type):" << mapIter->second << "(No. of Predicates)\n";
	}
	i=1;
	//cout << "\nVariables... \nClient type: No. of Variables\n";

	for(mapIter=VarNum.begin();mapIter!=VarNum.end();mapIter++){
		//cout << i++ <<"th entry->" << mapIter->first << "(Client Type):" << mapIter->second << "(No. of Predicates)\n";
	}

} 
//---------------------------------------------------------------------------------------------------------------------
void Formula::display_ftree()
{
	display_ft(FormulaTree);
	return;
}
void Formula::display_ftree_pre()
{
	display_ft_pre(FormulaTree);
	return;
}
void Formula::display_ftree_sub()
{
	display_ft_sub(QEFTree);
	return;
}
void Formula::display_ftree_pre_sub()
{
	display_ft_pre_sub(QEFTree);
	return;
}
//---------------------------------------------------------------------------------------------------------------------
void Formula::display_ft(FTree* FT)
{
	
	if(FT==NULL){
//		////cout <<"\nError in the formula tree.\n")
		return;
	}
	switch(FT->type){

		case 4: ////cout <<"\nThe node type is %d",FT->type);
			//cout << FT->val;
			display_ft(FT->next);
			break;

		case 3: ////cout <<"\nThe node type is %d",FT->type);
			//cout << FT->val;
			display_ft(FT->next);
			break;

		case 2: ////cout <<"\nThe node type is %d",FT->type);
			display_ft(FT->left);
			//cout << FT->val;
			display_ft(FT->right);
			break;

		case 1: ////cout <<"\nThe node type is %d",FT->type);
			//cout << FT->val;
			display_ft(FT->next);
			break;

		case 0: ////cout <<"\nThe node type is %d",FT->type);
			//cout << FT->val;
//the following is needed
			//if(!FT->client.empty()){
			//	//cout << ":"<< FT->client;
			//}
			break;

		default:
			////cout <<"\nError! Type can either be 0, 1 or 2.\n");
			break;
	}

}
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
void Formula::display_ft_pre(FTree* FT)
{
	
	if(FT==NULL){
//		////cout <<"\nError in the formula tree.\n")
		return;
	}
	switch(FT->type){

		case 4: ////cout <<"\nThe node type is %d",FT->type);
			//cout << FT->val;
			display_ft_pre(FT->next);
			break;

		case 3: ////cout <<"\nThe node type is %d",FT->type);
			//cout << FT->val;
			display_ft_pre(FT->next);
			break;

		case 2: ////cout <<"\nThe node type is %d",FT->type);
			//cout << FT->val;
			display_ft_pre(FT->left);
			display_ft_pre(FT->right);
			break;

		case 1: ////cout <<"\nThe node type is %d",FT->type);
			//cout << FT->val;
			display_ft_pre(FT->next);
			break;

		case 0: ////cout <<"\nThe node type is %d",FT->type);
			//cout << FT->val;
//the following is needed
			//if(!FT->client.empty()){
			//	//cout << ":"<<FT->client;
			//}		
			break;

		default:
			////cout <<"\nError! Type can either be 0, 1 or 2.\n");
			break;
	}

}
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
void Formula::display_ft_sub(FTree* FT)
{
	
	if(FT==NULL){
//		////cout <<"\nError in the formula tree.\n")
		return;
	}
	switch(FT->type){

		case 4: ////cout <<"\nThe node type is %d",FT->type);---monadic predicates
			//cout << FT->val<<FT->client;
			display_ft_sub(FT->next);
			break;

		case 3: ////cout <<"\nThe node type is %d",FT->type);--quantifiers
			//cout << FT->val;
			display_ft_sub(FT->next);
			break;

		case 2: ////cout <<"\nThe node type is %d",FT->type);--binary operators
			display_ft_sub(FT->left);
			//cout << FT->val;
			display_ft_sub(FT->right);
			break;

		case 1: ////cout <<"\nThe node type is %d",FT->type);--unary operators
			//cout << FT->val;
			display_ft_sub(FT->next);
			break;

		case 0: ////cout <<"\nThe node type is %d",FT->type);--variable or local proposition
			if(FT->subd)
			{	//cout << "[" << FT->num << "]";	
			}
			else{
				//cout << FT->val;
				//if(!FT->client.empty()){
				//	//cout << ":"<< FT->client;
				//}

			}
			break;

		default:
			////cout <<"\nError! Type can either be 0, 1 or 2.\n");
			break;
	}

}
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
void Formula::display_ft_pre_sub(FTree* FT)
{
	
	if(FT==NULL){
//		////cout <<"\nError in the formula tree.\n")
		return;
	}
	switch(FT->type){

		case 4: ////cout <<"\nThe node type is %d",FT->type);---monadic predicates
			//cout << FT->val<<FT->client;
			display_ft_pre_sub(FT->next);
			break;

		case 3: ////cout <<"\nThe node type is %d",FT->type);---quantifiers
			//cout << FT->val;
			display_ft_pre_sub(FT->next);
			break;

		case 2: ////cout <<"\nThe node type is %d",FT->type);---binary operators
			//cout << FT->val;
			display_ft_pre_sub(FT->left);
			display_ft_pre_sub(FT->right);
			break;

		case 1: ////cout <<"\nThe node type is %d",FT->type);---unary operators
			//cout << FT->val;
			display_ft_pre_sub(FT->next);
			break;

		case 0: ////cout <<"\nThe node type is %d",FT->type);--variable or local proposition
			if(FT->subd)
			{	//cout << "[" << FT->num << "]";			
			}
			else{
				//cout << FT->val;
				//if(!FT->client.empty()){
				//	//cout << ":"<< FT->client;
				//}

			}
			break;

		default:
			////cout <<"\nError! Type can either be 0, 1 or 2.\n");
			break;
	}

}
//-------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------



//FUNCTIONS AND VARIABLES ADDED TO LINK FILES
void Formula::display_ft_sub2(FTree* FT,string& s)
{
	
	if(FT==NULL){
//		////cout <<"\nError in the formula tree.\n")
		return;
	}
	if(!(FT->next == NULL && FT->left == NULL && FT->right==NULL))
	{//cout<<"(";
	s += "(";}
	switch(FT->type){

		case 4: ////cout <<"\nThe node type is %d",FT->type);---monadic predicates
			s += FT->val;
			s += FT->client;
			//cout << FT->val<<FT->client;
			display_ft_sub2(FT->next,s);
			break;

		case 3: ////cout <<"\nThe node type is %d",FT->type);--quantifiers
			s += FT->val;
			//cout << FT->val;
			display_ft_sub2(FT->next,s);
			break;

		case 2: ////cout <<"\nThe node type is %d",FT->type);--binary operators
			display_ft_sub2(FT->left,s);
			s += FT->val;
			//cout << FT->val;
			display_ft_sub2(FT->right,s);
			break;

		case 1: ////cout <<"\nThe node type is %d",FT->type);--unary operators
			s += FT->val;
			//cout << FT->val;
			display_ft_sub2(FT->next,s);
			break;

		case 0: ////cout <<"\nThe node type is %d",FT->type);--variable or local proposition
			if(FT->subd)
			{	//cout << "[" << FT->num << "]";	
				s += "[";
				s += to_string(FT->num);
				s += "]";
			}
			else{
				//cout << FT->val;
				s += FT->val;
				//if(!FT->client.empty()){
				//	//cout << ":"<< FT->client;
				//}

			}
			break;

		default:
			////cout <<"\nError! Type can either be 0, 1 or 2.\n");
			break;
	}
	if(!(FT->next == NULL && FT->left == NULL && FT->right==NULL))
	{//cout<<")";
	s+=')';}

}