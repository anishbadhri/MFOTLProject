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
	string mfotl_file(argv[1]),ltl_file(argv[2]);
	//cout<<mfotl_file<<endl;
	//vector<string> formulas;
	string formulas;
	checking c;
	c.test_input(mfotl_file);
	ifstream		mfotl_ptr(mfotl_file.c_str());
	string s;

					while(getline(mfotl_ptr,s))
					{
						if(s.find("MFOTLSPEC")!=string::npos)
						{
							while(getline(mfotl_ptr,s))
							{
								//cout<<s<<endl;
								//fs.push_back(s);
								break;
							}
							break;
						}
					}
	formulas = s;
	cout<<formulas<<endl;
	Formula InpFormula(formulas);
	bool done = InpFormula.ftree_convert();
	char temp;
	if(!done)
	{
		cout<< "\nFormula tree construction fails.\n";
		return 0;
	}
	cout<<"Formula Tree Constructed\n";
	temp = getchar();
	done = InpFormula.quant_elim();
	if(!done)
	{
		cout<< "\nQuantifier Elimination fails.\n";
		return 0;
	}
	cout<<"Quantifier Eliminated\n";
	temp = getchar();
	string expression = InpFormula.get_expression();
	cout<<"Expression: "<<expression<<endl;
	convert con(InpFormula.get_NoOfCltTypes());
	vector<int> vec = InpFormula.get_counters();
	con.setCounters(vec);
	con.produceLTLFile(ltl_file,expression);
	cout<<"LTL File Produced\n";
}