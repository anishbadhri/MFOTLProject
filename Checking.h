#include <bits/stdc++.h>
using namespace std;
class checking
{
	// void usage(string);
	//bool check(string mfotl_file);
	vector<string> 	formulas;
public:
	bool test_input(string);
	string get_formulas(string);

};
// void checking::usage(string file)
// {
// 	cout << "Usage: "<< file <<"<mfotl_file> <ltl_file>\n"; 
// }

// bool checking::check(string mfotl_file, vector<string>& formulas)
// {

// }
bool checking::test_input(string mfotl_file)
{
	ofstream	check_ptr("template.smv");
	ifstream	mfotl_ptr(mfotl_file.c_str());
	string		s;
				while(getline(mfotl_ptr,s))
				{
					if(s.find("MFOTLSPEC")!=string::npos)
					{
						// while(getline(mfotl_ptr,s))
						// {
						// 	formulas.push_back(s);
						// }
						break;
					}
					check_ptr << s << '\n'; 
				}
				check_ptr.close();
				mfotl_ptr.close();
	int 		ret = system("NuSMV template.smv");
				if(ret)
				{
					return false;
				}
				return true;

}
string checking::get_formulas(string mfotl_file)
{
	vector<string> 	fs;
	ifstream		mfotl_ptr(mfotl_file.c_str());
	string			s;
					while(getline(mfotl_ptr,s))
					{
						if(s.find("MFOTLSPEC")!=string::npos)
						{
							while(getline(mfotl_ptr,s))
							{
								//cout<<s<<endl;
								//fs.push_back(s);
								return s;
							}
							break;
						}
					}
					//return fs;
}