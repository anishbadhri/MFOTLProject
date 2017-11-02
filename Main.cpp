#include <bits/stdc++.h>
#include "mfotl.h"
#include "Checking.h"
#include "Convert.h"
using namespace std;





int func(string InExp)
{
	//MFO InExps

//	string InExp="(Ex:1(p(x:1)))";//--output correct

	InExp = "((Ex:1(p(x:1)))&(Ey:2(p(y:2))))";
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

}














void usage(string file)
{
	cout << "Usage: "<< file <<" <mfotl_file> <ltl_file>\n"; 
}
// bool check(string mfotl_file,vector<string>& formulas)
// {
// 	ofstream	check_ptr("template.smv");
// 	ifstream	mfotl_ptr(mfotl_file.c_str());
// 	string		s;
// 				while(getline(mfotl_ptr,s))
// 				{
// 					if(s.find("MFOTLSPEC")!=string::npos)
// 					{
// 						while(getline(mfotl_ptr,s))
// 						{
// 							formulas.push_back(s);
// 						}
// 						break;
// 					}
// 					check_ptr << s << '\n'; 
// 				}
// 				check_ptr.close();
// 				mfotl_ptr.close();
// 	int 		ret = system("./check.sh template.smv");
// 				if(ret)
// 				{
// 					return false;
// 				}
// 				return true;
// }

int main(int argc,char* argv[])
{	
	string			executable(argv[0]);
	checking		check_obj;
	vector<string>	formulas;	
					if(argc<3)
					{
						usage(executable);
						exit(0);
					}
	string			mfotl_file(argv[1]),ltl_file(argv[2]);
					if(!check_obj.test_input(mfotl_file))
					{
						cout << "Compilation error\n";
						exit(0);
					}
					//else
					{
						formulas = check_obj.get_formulas(mfotl_file);
					}
					cout<<"MFOTL Formulas\n";
					for(int i=0;i<formulas.size();i++)
					{
						cout<<formulas[i]<<endl;
					}
					cout<<"\n\n";
					int dummy;
					cout<<"Step 1\n";
					cin>>dummy;
					dummy = func(formulas[0]);
					cout<<"Step 2\n";
					cin>>dummy;
					cout<<"Fucks Up Here\n";
					Formula InpFormula(formulas[0]);
					bool done = InpFormula.ftree_convert();
					if(!done)
					{
						cout<< "\nFormula tree construction fails.\n";
						return 0;
					}
					cout <<"\nFormula Tree Constructed...............\n";
					cout <<"\nReading the Formula Tree...............\n";
					cout <<"\nIn infix form:";
					InpFormula.display_ftree();
					cout <<"\n";
					cout <<"\nIn prefix form:";
					InpFormula.display_ftree_pre();
					cout <<"\n";
				//ftree_convert method should also gather the relevant data into 
				//PredList, VarList and PredNum, VarNum data members of the formula object
				//at this point we can traverse the maps PredNum and VarNum and find the number of variables and predicates of each client type.

					InpFormula.display_lists();
					InpFormula.display_nums();

				//	return 0;
				//---------------------------------------------------------------------------------------------------------------
				//now eliminate quantifiers
					done=InpFormula.quant_elim();
					if(!done){
						cout<< "\nQuantifier Elimination fails.\n";
						return 0;
					}

					cout <<"The InExp with all quantifiers eliminated is as follows:\nIn prefix form:";
					InpFormula.display_ftree_pre_sub();
					cout <<"\n";

					cout <<"\nIn infix form:";
					string expression;
					expression = InpFormula.get_expression();
					cout <<"\n";
					cout << endl;
	convert 		con(InpFormula.get_NoOfCltTypes());
	vector<int>		vec;
					vec = InpFormula.get_counters();
					con.setCounters(vec);
					con.produceLTLFile(ltl_file,expression);
}


