#include <bits/stdc++.h>
using namespace std;
class convert
{
	int no_of_types;
	int counter_total;
	vector<int> counters;
	vector<string> ivars;
	vector<string>	variables;
	vector<string>	inits;
	vector<string>	nexts;
public:
	convert(int);
	void print();
	void setCounters(vector<int>);
	void extractIVARs();
	void prepareCounterVariables();
	void prepareArrayVariables();
	void prepareCounterInits();
	void prepareArrayInits();
	void prepareCounterNexts();
	void prepareArrayNexts();
	void produceLTLFile(string,string);
};
convert::convert(int num)
{
	counters.clear();
	counter_total = 0;
	ivars.clear();
	variables.clear();
	inits.clear();
	nexts.clear();
	no_of_types = num;
	counter_total = 0;
	counters = vector<int>(no_of_types+10);
}
void convert::print()
{
	for(int i=0;i<ivars.size();++i)
		cout << ivars[i] << endl;
}
void convert::setCounters(vector<int> obtained_counters)
{
	for(int i=0;i<no_of_types;++i)
	{
		counters[i] = obtained_counters[i];
		counter_total += counters[i];
	}
	extractIVARs();
	prepareCounterVariables();
	prepareArrayVariables();
	prepareCounterInits();
	prepareArrayInits();
	prepareCounterNexts();
	prepareArrayNexts();
	// variables = vector<string>(counter_total+no_of_types);
}
void convert::extractIVARs()
{
	ifstream	template_ptr("template.smv");
	string		s;
				while(getline(template_ptr,s))
				{
					if(s.find("IVAR")!=string::npos)
					{
						string input="";
						for(int i=0;i<s.size();++i)
						{
							if(s[i]==' ')continue;
							if(s.substr(i,4)=="IVAR")
							{
								i+=4;
								for(int j=i+1;j<s.size();++j)
								{
									if(s[j]==' '||s[j]==':')break; //Not Required	//Add ':' too for break condition
									input += s[j];
								}
								ivars.push_back(input);
								break;					//Resolved		//Check if I can add a break statement since only one IVAR per line
							}
						}
					}
				}
}
void convert::prepareCounterVariables()
{
	for(int i=1;i<=no_of_types;++i)
	{
		char max_val = counters[i-1]+'0';
		char type = i+'0';
		string var = "VAR ctr";
		var += type;
		var += ": 0..";
		var += max_val;
		var += ';';
		variables.push_back(var);
		variables.push_back("");
	}
}
void convert::prepareArrayVariables()
{
	for(int i=1;i<=no_of_types;++i)
	{
		char max_val = counters[i-1]+'0';
		char type = i+'0';
		for(int j=0;j<=1;++j)
		{
			string var = "VAR ";
			if(j) var += 'q';
			else var += 'p';
			var += type;
			var += ": array 1..";
			var += max_val;
			var += " of boolean;";
			variables.push_back(var);
			variables.push_back("");
		}
	}
}
void convert::prepareCounterInits()
{
	for(int i=1;i<=no_of_types;++i)
	{
		char type = i+'0';
		string init	= "	init(ctr";
		init += type;
		init += ") := 0;";
		inits.push_back(init);
		inits.push_back("");	
	}
}
void convert::prepareArrayInits()
{
	for(int i=1;i<=no_of_types;++i)
	{
		char type = i+'0';
		for(int k=0;k<=1;++k)
		{
			for(int j=1;j<=counters[i-1];++j)
			{
				int index = j+'0';
				string init = "	init(";
				if(k) init += 'q';
				else init += 'p';
				init += type;
				init += '[';
				init += index;
				init += "]) := FALSE;";
				inits.push_back(init);
			}
			inits.push_back("");
		}
	}
}
void convert::prepareCounterNexts()
{
	for(int i=1;i<=no_of_types;++i)
	{
		char max_val = counters[i-1]+'0';
		char type = i+'0';
		string next = " next(ctr";
		next += type;
		next += ") := case";
		nexts.push_back(next);
		next = "  "; 
		next += ivars[i-1];
		next += " = TRUE & ctr";
		next += type ;
		next += " < ";
		next += max_val; 
		next += " : ctr"; 
		next += type;
		next += " + 1;";
		nexts.push_back(next);
		next = "  "; 
		next += ivars[i-1] ;
		next += " = FALSE & ctr";
		next += type ;
		next += " > 0";
		next += " : ctr"; 
		next += type;
		next += " - 1;";
		nexts.push_back(next);
		next = "  TRUE : ctr";
		next += type;
		next += ';';
		nexts.push_back(next);
		nexts.push_back(" esac;");
		nexts.push_back("");
	}
}
void convert::prepareArrayNexts()
{
	for(int i=1;i<=no_of_types;++i)
	{
		char max_val = counters[i-1]+'0';
		char type = i+'0';
		string input_variable = ivars[i-1];
		string counter_variable = "ctr";
		counter_variable += type;
		for(int k=0;k<=1;++k)
		{
			if(k==0)
			{
				for(int j=1;j<=counters[i-1];++j)
				{
					char index = j+'0';
					char prev = j-1+'0';
					string var = "p",var1 = "q";
					var += type; var1 += type;
					var += '['; var1 += '[';
					var += index; var1 += index;
					var += ']'; var1 += ']';
					string next = " next(";
					next += var;
					next += ") := case";
					nexts.push_back(next);
					next = "  ";
					next += var;
					next += " = FALSE & ";
					next += input_variable;
					next += " = TRUE & ";
					next += counter_variable;
					next += " = ";
					next += prev;
					next += " : TRUE;" ; 
					nexts.push_back(next);
					next = "  ";
					next += var;
					next += " = TRUE & ";	
					next += "next(";
					next += var1;
					next += ") = TRUE : FALSE;";
					nexts.push_back(next);
					next = "  TRUE : ";
					next += var;
					next += ';';
					nexts.push_back(next);
					nexts.push_back(" esac;");
					nexts.push_back("");				
				}
			}
			else
			{
				for(int j=1;j<=counters[i-1];++j)
				{
					char index = j+'0';
					string var1 = "p",var = "q";
					var1 += type; var += type;
					var1 += '['; var += '[';
					var1 += index; var += index;
					var1 += ']'; var += ']';
					string next = " next(";
					next += var;
					next += ") := case";
					nexts.push_back(next);
					next = "    ";
					next += var;
					next += " = FALSE & ";
					next += input_variable;
					next += " = FALSE & ";
					next += counter_variable;
					next += " = ";
					next += index;
					next += " : TRUE;" ; 
					nexts.push_back(next);
					next = "    ";
					next += var;
					next += " = TRUE : FALSE;";	
					nexts.push_back(next);
					next = "  TRUE : ";
					next += var;
					next += ';';
					nexts.push_back(next);
					nexts.push_back(" esac;");
					nexts.push_back("");				
				}
			}
		}		
	}
}
void convert::produceLTLFile(string ltl_file_name,string expression)
{
	ofstream	ltl_ptr(ltl_file_name.c_str());
	ifstream	template_ptr("template.smv");
	string		line;
				while(getline(template_ptr,line))
				{
					if(line.find("MODULE")!=string::npos)
					{
						ltl_ptr << line << endl;
						while(getline(template_ptr,line))
						{
							if(line.find("VAR")==string::npos && line!="")break;
							ltl_ptr << line << endl;
						}
						for(int i=0;i<variables.size();++i)
							ltl_ptr << variables[i] << endl;
					}
					if(line.find("ASSIGN")!=string::npos)
					{
 						ltl_ptr << line << endl;
						while(getline(template_ptr,line))
						{
							if(line.find("init")==string::npos && line!="")break;
							ltl_ptr << line << endl;
						}
						for(int i=0;i<inits.size();++i)
							ltl_ptr << inits[i] << endl;

					}
					if(line.find("next")!=string::npos)
					{
						ltl_ptr << line << endl;
						while(getline(template_ptr,line))
							ltl_ptr << line << endl;
						for(int i=0;i<nexts.size();++i)
							ltl_ptr << nexts[i] << endl;
					
					}
				}
				ltl_ptr << "" << endl;
				ltl_ptr << "LTLSPEC" << endl;
				ltl_ptr << expression <<endl;
				ltl_ptr.close();
				template_ptr.close();
}
