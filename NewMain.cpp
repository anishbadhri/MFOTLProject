#include <bits/stdc++.h>
#include "Checking.h"
#include "Convert.h"
#include "mfotl.h"


int main(int argc,char* argv[])
{
	if(argc != 3)
	{
		cout<<"Usage: "<<argv[0]<<" <mfotlfile> <ltlfile>\n";
		return 0;
	}
	string 		mfotl_file(argv[1]),ltl_file(argv[2]);
	string 		formulas,s;
	checking 	c;
	ifstream	mfotl_ptr(mfotl_file.c_str());
	bool 		done=c.test_input(mfotl_file);
				if(!done)
				{
					cout << "Syntax error" << endl;
				}
				while(getline(mfotl_ptr,s))
				{
					if(s.find("MFOTLSPEC")!=string::npos)
					{
						while(getline(mfotl_ptr,s))
						{
							break;
						}
						break;
					}
				}
				formulas = s;
				cout<<formulas<<endl;
	Formula 	InpFormula(formulas);
				done=InpFormula.ftree_convert();
				if(!done)
				{
					cout<< "\nFormula tree construction fails.\n";
					return 0;
				}
				cout<<"\nFormula Tree Constructed\n";
				done = InpFormula.quant_elim();
				if(!done)
				{
					cout<< "\nQuantifier Elimination fails.\n";
					return 0;
				}
				cout<<"Quantifier Eliminated\n";
	string 		expression = InpFormula.get_expression();
	convert 	con(InpFormula.get_NoOfCltTypes());
	vector<int> vec = InpFormula.get_counters();
				con.setCounters(vec);
				con.produceLTLFile(ltl_file,expression);
				cout<<endl<<endl;
				con.print();
}