#include "mfotl.h"
using namespace std;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
int main()
{

//MFO InExps

//	string InExp="(Ex:1(p(x:1)))";//--output correct


	string InExp="((Ex:1(p(x:1)))&(Ey:2(p(y:2))))";//--output correct


//define a Formula object. This will create a formula object with expression (formula) as raw text.
	Formula InFormula(InExp);

//Using the methods in formula object we compute, first the formula tree and then eliminate quantifiers from the formula.
//In this process, we gather necessary data from the formula, which can be used later.


	cout <<"\nThe input formula is:->" << InExp << endl;

//convert the InExp to InExp tree.
	bool done=InFormula.ftree_convert();
	if(!done){
		cout<< "\nFormula tree construction fails.\n";
		return 0;
	}
	cout <<"\nFormula Tree Constructed...............\n";
	cout <<"\nReading the Formula Tree...............\n";
	cout <<"\nIn infix form:";
	InFormula.display_ftree();
	cout <<"\n";
	cout <<"\nIn prefix form:";
	InFormula.display_ftree_pre();
	cout <<"\n";
//ftree_convert method should also gather the relevant data into 
//PredList, VarList and PredNum, VarNum data members of the formula object
//at this point we can traverse the maps PredNum and VarNum and find the number of variables and predicates of each client type.

	InFormula.display_lists();
	InFormula.display_nums();

//	return 0;
//---------------------------------------------------------------------------------------------------------------
//now eliminate quantifiers
	done=InFormula.quant_elim();
	if(!done){
		cout<< "\nQuantifier Elimination fails.\n";
		return 0;
	}

	cout <<"The InExp with all quantifiers eliminated is as follows:\nIn prefix form:";
	InFormula.display_ftree_pre_sub();
	cout <<"\n";

	cout <<"\nIn infix form:";
	InFormula.display_ftree_sub();
	cout <<"\n";
	cout << endl;
	string s = InFormula.get_expression();
	cout<<endl;
	cout<<s<<endl;

//	InFormula.display_lists();
//	InFormula.display_nums();

	return 0;


//-----------------------------------------------------------------------------------------------------------------
//At this point we should free all the dynamic memory we created using new, otherwise it will lead to memory leak.
//-----------------------------------------------------------------------------------------------------------------

	return 0;

}//end of main


