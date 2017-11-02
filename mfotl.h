#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<iostream>
#include<string>
#include<stack>
#include<set>
#include<map>
#include<vector>
#define MAX 100

using namespace std; 
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
typedef struct FTree
{

	int type;//type can either be 0 (leaf or proposition) or 1 (unary opearator) or 2(binary operator) or 3 (quantifier) or 4 (predicate)-------we can make type as enum with 5 values, instead. 
	bool subd;//0 for not substituted 1 for substituted---useful only when type is 0
//	int global;//global==0,local=={1,2,...,n}
	unsigned model;//model as a positive integer; can be converted to boolean string whenever needed
	unsigned copy;//copy of the model above
	unsigned num;//num=R*model+copy
	string val;//variable or operator (logical or temporal)
	string client;//client type
	struct FTree* parent;
	struct FTree* left;
	struct FTree* right;
	struct FTree* next;
}FTree;
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
class Formula{
 private:
	string FormulaText;
	FTree* FormulaTree;
	FTree* QEFTree;
	
	int NoOfCltTypes;

	set <string> PredList;
	set <string> VarList;

	map <string,int> PredNum;
	map <string,int> VarNum;

 public:
	Formula(){};//Constructor
	Formula(string InExp){FormulaText=InExp;};//Parameterized Constructor
	~Formula(){};//Destructor
		
	bool ftree_convert();
	bool quant_elim();

	void display_ftree();
	void display_ftree_pre();
	void display_ftree_sub();
	void display_ftree_pre_sub();

	void display_lists();
	void display_nums(); 

	//FUNCTION AND VARIABLES ADDED TO LINK FILES
	//////////////////////////////////////////////////////////////////////////////
	inline int get_NoOfCltTypes(){	return NoOfCltTypes; }
	vector<int> get_counters();
	string get_expression();
	void display_ft_sub2(FTree*,string&);
	//////////////////////////////////////////////////////////////////////////////
	//ENDS HERE
 protected:
	FTree* eliminate_quantifier(FTree*);
	int isoperator(char);
	int op_prcd(char);
	int op_type(char);
	void substitute(FTree*,string,int,int,int);
	FTree* copy(FTree*);
	void add_variable_to_formula_info(string,string);
	void add_predicate_to_formula_info(string,string);

	void display_ft(FTree*);
	void display_ft_pre(FTree*);
	void display_ft_sub(FTree*);
	void display_ft_pre_sub(FTree*);
};
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
//typedef struct PEntry{
//	char pred[5];
//	char client[5];
//}PEntry;
//--------------------------------------------------------------------------------------------
//typedef struct VEntry{
//	char var[5];
//	char client[5];
//}VEntry;
//--------------------------------------------------------------------------------------------
//typedef struct FStat{
//	char client[5];
//	unsigned PNum;
//	unsigned VNum;
//}FStat;
//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
