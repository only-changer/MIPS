#include<cstdio>
#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<cstdlib>
#include<fstream>
const int N = 10000000;
using namespace std;
vector<string> str;
map<string, int> label;
map<string, int> data_label;
map<string, int> to_register;
int i = -1, j, k = 0;
int r[32] = { 0 };
int lo = 0, hi = 0;
struct data_type
{
	int num;
	int mark = -1;
	int size;
	int current_size = 0;
	char chr;
};
data_type datar[N];
int datanum = 0;
int design(int x)
{
	if (x > 0) return x;
	//	else return (x + 4294967296);
}
void ready()
{
	to_register["zero"] = 0;
	to_register["at"] = 1;
	to_register["v0"] = 2;
	to_register["v1"] = 3;
	to_register["a0"] = 4;
	to_register["a1"] = 5;
	to_register["a2"] = 6;
	to_register["a3"] = 7;
	to_register["t0"] = 8;
	to_register["t1"] = 9;
	to_register["t2"] = 10;
	to_register["t3"] = 11;
	to_register["t4"] = 12;
	to_register["t5"] = 13;
	to_register["t6"] = 14;
	to_register["t7"] = 15;
	to_register["s0"] = 16;
	to_register["s1"] = 17;
	to_register["s2"] = 18;
	to_register["s3"] = 19;
	to_register["s4"] = 20;
	to_register["s5"] = 21;
	to_register["s6"] = 22;
	to_register["s7"] = 23;
	to_register["t8"] = 24;
	to_register["t9"] = 25;
	to_register["gp"] = 28;
	to_register["sp"] = 29;
	to_register["fp"] = 30;
	to_register["ra"] = 31;
}
string check(string s)
{
	string ss;
	for (int i = 0; i < s.size(); ++i)
	{
		if (s[i] == '\\')
		{
			if (s[i + 1] == '\\') ss += '\\\\';
			if (s[i + 1] == '\'') ss += '\\\'';
			if (s[i + 1] == '\"') ss += '\\\"';
			if (s[i + 1] == 'n') ss += '\n';
			if (s[i + 1] == 't') ss += '\t';
			if (s[i + 1] == '0') ss += '\0';
			if (s[i + 1] == 'r') ss += '\r';
			++i;
		}
		else ss += s[i];
	}
	return ss;
}
ofstream fout("array_test1-mahaojun.out");
int main()
{
	int snum = 0;
	r[29] = N;
	ready();
	FILE *stdin1 = fopen("array_test1-mahaojun.s", "r");
//	FILE *stdin2 = fopen("array_test2-mahaojun.in", "r");
	//FILE *stdin3 = fopen("array_test1-mahaojun.out", "w");
	char chr[100];
	while (fscanf(stdin1, "%[^\n]", &chr) != EOF)
	{
		++i;
		string s = chr;
		while (s[0] == '\t' || s[0] == ' ') s.erase(s.begin());
		str.push_back(s);
		if (s[s.size() - 1] == ':')
		{
			label[s] = i;

		}
		fscanf(stdin1, "\n");
	}
	for (k = 0; k < i; ++k)
	{
		if (str[k] == ".data")
		{
			while (str[k + 1] != ".text")
			{
				++k;
				if (str[k].find(".word", 0) != str[k].npos)
				{
					int j = str[k].find(".word", 0) + 6;
					string s = "";
					while (j < str[k].size())
					{
						s = "";
						for (; str[k][j] != ',' && j < str[k].size(); ++j)
						{
							s += str[k][j];
						}
						int p = atoi(s.c_str());
						data_type d;
						d.size = 4;
						d.mark = 1;
						d.num = p;
						datar[datanum] = d;
						datanum += 4;
						++j;
					}
				}
				if (str[k].find(".half", 0) != str[k].npos)
				{
					int j = str[k].find(".half", 0) + 6;
					string s = "";
					while (j < str[k].size())
					{
						s = "";
						for (; str[k][j] != ',' && j < str[k].size(); ++j)
						{
							s += str[k][j];
						}
						int p = atoi(s.c_str());
						data_type d;
						d.size = 2;
						d.mark = 2;
						d.num = p;
						datar[datanum] = d;
						datanum += 2;
						++j;
					}
				}
				if (str[k].find(".byte", 0) != str[k].npos)
				{
					int j = str[k].find(".byte", 0) + 6;
					string s = "";
					while (j < str[k].size())
					{
						s = "";
						for (; str[k][j] != ',' && j < str[k].size(); ++j)
						{
							s += str[k][j];
						}
						int p = atoi(s.c_str());
						data_type d;
						d.size = 1;
						d.mark = 3;
						d.num = p;
						datar[datanum] = d;
						datanum += 1;
						++j;
					}
				}
				if (str[k].find(".asciiz", 0) != str[k].npos)
				{
					int j = str[k].find("\"", 0) + 1;
					string s = "";
					for (; j < str[k].size() - 1; ++j)
					{
						s += str[k][j];
					}
					s = check(s);
					if (s.size() == 0) continue;
					data_type d;
					d.size = s.size() + 1;
					d.mark = 5;
					datar[datanum] = d;
					for (j = 0; j <= s.size(); ++j)
					{
						datar[datanum].chr = s[j];
						++datanum;
					}
					//	cout<<s<<endl;
				}
				else
					if (str[k].find(".ascii", 0) != str[k].npos)
					{
						int j = str[k].find("\"", 0) + 1;
						string s = "";
						for (; j < str[k].size() - 1; ++j)
						{
							s += str[k][j];
						}
						s = check(s);
						if (s.size() == 0) continue;
						data_type d;
						d.size = s.size();
						d.mark = 5;
						datar[datanum] = d;
						for (j = 0; j < s.size(); ++j)
						{
							datar[datanum].chr = s[j];
							++datanum;
						}
					}
				if (str[k].find(".align", 0) != str[k].npos)
				{
					int j = str[k].find(".align", 0) + 7;
					string s = "";
					for (; j < str[k].size(); ++j)
					{
						s += str[k][j];
					}
					int p = atoi(s.c_str());
					int ans = 1;
					for (int q = 1; q <= p; ++q) ans *= 2;
					datanum = (datanum / ans + 1) * ans;
				//	cout<<ans<<endl;
				}
				if (str[k].find(".space", 0) != str[k].npos)
				{
					int j = str[k].find(".space", 0) + 7;
					string s = "";
					for (; j < str[k].size(); ++j)
					{
						s += str[k][j];
					}
					int p = atoi(s.c_str());
					datanum += p;
				}
				if (str[k][str[k].size() - 1] == ':')
				{
					data_label[str[k]] = datanum;
					//cout<<str[k]<<' '<<datanum<<endl;
				}
			//	cout<<str[k]<<' '<<datanum<<endl;
			}
		}
	}
	j = label["main:"];
	while (j < str.size())
	{
		++j;
		fout<< j << '\t' << str[j]<<endl;
		for (int k = 0;k < 32;++k) fout<<k<<'\t'; fout<<endl;
		for (int k = 0;k < 32;++k) fout<<r[k]<<'\t'; fout<<endl;
		if (str[j].find("jal", 0) != str[j].npos)
		{
			r[31] = j + 1;
			string s = "";
			for (k = str[j].find("jal", 0) + 4; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			s += ':';
			j = label[s];
			continue;
		}
		if (str[j].find("li", 0) != str[j].npos)
		{
			string s = "";
			int key;
			for (k = str[j].find("li", 0) + 4; k < str[j].size() && str[j][k] != ','; ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
			else key = to_register[s]; s = "";
			for (k = str[j].find(",", 0) + 1; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			int p = atoi(s.c_str());
			r[key] = p;
			continue;
		}
		if (str[j].find("syscall", 0) != str[j].npos)
		{
			//cout<<r[2]<<' '<<r[4]<<endl;
			if (r[2] == 1) cout<<r[4]; else
				if (r[2] == 4) {
					int j = r[4];
					while (datar[j].chr != '\0') { cout<<datar[j].chr; ++j; }
				}
				else
					if (r[2] == 5) {
						cin>>r[2];
					}
					else
						if (r[2] == 8)
						{
							char chr[1000];
							cin>>chr;
							string s = chr;
							data_type d;
							d.size = s.size();
							d.mark = 5;
							datar[r[4]] = d;
							int t = r[4];
							for (int j = 0; j <= s.size(); ++j)
							{
								datar[t].chr = s[j];
								++t;
							}
							
						}
						else
							if (r[2] == 10) {cout<<snum<<endl;return 0; }else
								if (r[2] == 17) {cout<<snum<<endl;return r[4];} else
									if (r[2] == 9)
									{
										r[2] = datanum;
										datar[datanum].mark = 6;
										datar[datanum].size = r[4];
										datar[datanum].current_size = 0;
										datanum += r[4];
									}
			continue;
		}
		if (str[j].find("sb", 0) != str[j].npos)
		{
			string s = "";
			int key;
			for (k = str[j].find("sb", 0) + 4; k < str[j].size() && str[j][k] != ','; ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
			else key = to_register[s]; s = "";
			for (k = str[j].find(",", 0) + 1; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			//cout << "               " << r[key] << endl;
			if (s.find("($", 0) == s.npos)
			{
				s += ':';
			//	if (key != 0) 
				datar[data_label[s]].chr = char(r[key]); 
				//else datar[data_label[s]].chr = '\0';
				datar[data_label[s]].mark = 5;
				datar[data_label[s]].size = 1;
			}
			else
			{
				string ss = ""; int ke = -1;
				for (k = 0; k < s.find("($", 0); ++k) if (s[k] != ' ') ss += s[k];
				int p = atoi(ss.c_str()); ss = "";
				for (k = s.find("($", 0) + 2; k < s.size() - 1; ++k) if (s[k] != ' ') ss += s[k];
				if (ss[0] >= '0' && ss[0] <= '9') ke = atoi(ss.c_str());
				else ke = to_register[ss];
				int t = r[ke] + p;
				//if (key != 0) 
				datar[t].chr = char(r[key]);
				// else datar[t].chr = '\0';
				datar[t].mark = 5;
				datar[t].size = 1;
			}
			continue;
		}
		if (str[j].find("sw", 0) != str[j].npos)
		{
			string s = "";
			int key;
			for (k = str[j].find("sw", 0) + 4; k < str[j].size() && str[j][k] != ','; ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
			else key = to_register[s]; s = "";
			for (k = str[j].find(",", 0) + 1; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s.find("($", 0) == s.npos)
			{
				s += ':';
				datar[data_label[s]].num = r[key];
				datar[data_label[s]].mark = 1;
				datar[data_label[s]].size = 4;
			}
			else
			{
				string ss = ""; int ke = -1;
				for (k = 0; k < s.find("($", 0); ++k) if (s[k] != ' ') ss += s[k];
				int p = atoi(ss.c_str()); ss = "";
				for (k = s.find("($", 0) + 2; k < s.size() - 1; ++k) if (s[k] != ' ') ss += s[k];
				if (ss[0] >= '0' && ss[0] <= '9') ke = atoi(ss.c_str());
				else ke = to_register[ss];
				int t = r[ke] + p;
				datar[t].num = r[key];
				datar[t].mark = 1;
				datar[t].size = 4;
			//	 cout << ke << ' ' << r[ke] << ' ' << p <<' '<<key<<' '<<r[key]<< endl;
			//	cout << "!!!!" << t << endl;
			}
			continue;
		}
		if (str[j].find("la", 0) != str[j].npos)
		{
			string s = "";
			int key;
			for (k = str[j].find("la", 0) + 4; k < str[j].size() && str[j][k] != ','; ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
			else key = to_register[s]; s = "";
			for (k = str[j].find(",", 0) + 1; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s.find("($", 0) == s.npos)
			{
				s += ':';
				r[key] = data_label[s];
			}
			else
			{
				string ss = ""; int ke = -1;
				for (k = 0; k < s.find("($", 0); ++k) if (s[k] != ' ') ss += s[k];
				int p = atoi(ss.c_str()); ss = "";
				for (k = s.find("($", 0) + 2; k < s.size() - 1; ++k) if (s[k] != ' ') ss += s[k];
				if (ss[0] >= '0' && ss[0] <= '9') ke = atoi(ss.c_str());
				else ke = to_register[ss];
				int t = r[ke] + p;
				r[key] = t;
			}
			continue;
		}
		if (str[j].find("lb", 0) != str[j].npos)
		{
			string s = "";
			int key;
			for (k = str[j].find("lb", 0) + 4; k < str[j].size() && str[j][k] != ','; ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
			else key = to_register[s]; s = "";
			for (k = str[j].find(",", 0) + 1; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s.find("($", 0) == s.npos)
			{
				s += ':';
				r[key] = int(datar[data_label[s]].chr);
			}
			else
			{
				string ss = ""; int ke = -1;
				for (k = 0; k < s.find("($", 0); ++k) if (s[k] != ' ') ss += s[k];
				int p = atoi(ss.c_str()); ss = "";
				for (k = s.find("($", 0) + 2; k < s.size() - 1; ++k) if (s[k] != ' ') ss += s[k];
				if (ss[0] >= '0' && ss[0] <= '9') ke = atoi(ss.c_str());
				else ke = to_register[ss];
				int t = r[ke] + p;
				r[key] = int(datar[t].chr);
			}
			continue;
		}
		if (str[j].find("lw", 0) != str[j].npos)
		{
			string s = "";
			int key;
			for (k = str[j].find("lw", 0) + 4; k < str[j].size() && str[j][k] != ','; ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
			else key = to_register[s]; s = "";
			for (k = str[j].find(",", 0) + 1; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s.find("($", 0) == s.npos)
			{
				s += ':';
				r[key] = datar[data_label[s]].num;
			}
			else
			{
				string ss = ""; int ke = -1;
				for (k = 0; k < s.find("($", 0); ++k) if (s[k] != ' ') ss += s[k];
				int p = atoi(ss.c_str()); ss = "";
				for (k = s.find("($", 0) + 2; k < s.size() - 1; ++k) if (s[k] != ' ') ss += s[k];
				if (ss[0] >= '0' && ss[0] <= '9') ke = atoi(ss.c_str());
				else ke = to_register[ss];
				int t = r[ke] + p;
				r[key] = datar[t].num;
		//	cout << ke << ' ' << r[ke] << ' ' << p << ' '<<r[key]<<endl;
			}
			continue;
		}
		if (str[j].find("jr", 0) != str[j].npos)
		{
			string s = "";
			int key;
			for (k = str[j].find("jr", 0) + 4; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
			else key = to_register[s];
			j = r[key] - 1;
			continue;
		}
		if (str[j].find("addu", 0) != str[j].npos)
		{
			string s = "";
			int key1, key2, key3;
			for (k = str[j].find("addu", 0) + 6; k < str[j].size() && str[j][k] != ','; ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
			else key1 = to_register[s]; s = "";
			for (k = str[j].find('$', k) + 1; str[j][k] != ',' && k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
			else key2 = to_register[s]; s = ""; k += 2;
			for (; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s.find('$', 0) != s.npos)
			{
				s.erase(s.begin());
				if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
				else key3 = to_register[s];
				r[key1] = (unsigned) int (r[key2]) + (unsigned) int (r[key3]);
			}
			else
			{
				int q = atoi(s.c_str());
				r[key1] = (unsigned) int (r[key2]) + (unsigned) int (q);
			}
			continue;
		}
		if (str[j].find("add", 0) != str[j].npos)
		{
			string s = "";
			int key1, key2, key3;
			for (k = str[j].find("add", 0) + 5; k < str[j].size() && str[j][k] != ','; ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
			else key1 = to_register[s]; s = "";
			for (k = str[j].find('$', k) + 1; str[j][k] != ',' && k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
			else key2 = to_register[s]; s = ""; k += 2;
			for (; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s.find('$', 0) != s.npos)
			{
				s.erase(s.begin());
				if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
				else key3 = to_register[s];
				r[key1] = r[key2] + r[key3];
			//	cout << key1 << ' ' << key2 << ' ' << key3 << ' ' << r[key1] << ' ' << r[key2] << ' ' << r[key3] << endl;
			}
			else
			{
				int q = atoi(s.c_str());
				r[key1] = r[key2] + q;
			}
			continue;
		}
		if (str[j].find("subu", 0) != str[j].npos)
		{
			string s = "";
			int key1, key2, key3;
			for (k = str[j].find("subu", 0) + 6; k < str[j].size() && str[j][k] != ','; ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
			else key1 = to_register[s]; s = "";
			for (k = str[j].find('$', k) + 1; str[j][k] != ',' && k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
			else key2 = to_register[s]; s = ""; k += 2;
			for (; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s.find('$', 0) != s.npos)
			{
				s.erase(s.begin());
				if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
				else key3 = to_register[s];
				r[key1] = (unsigned) int (r[key2]) - (unsigned) int (r[key3]);
			}
			else
			{
				int q = atoi(s.c_str());
				r[key1] = (unsigned) int (r[key2]) - (unsigned) int (q);
			//	cout << "           " << key1<<' '<<key2<<' '<<r[key1] << ' ' << r[key2] << endl;
			}
			continue;
		}
		if (str[j].find("sub", 0) != str[j].npos)
		{
			string s = "";
			int key1, key2, key3;
			for (k = str[j].find("sub", 0) + 5; k < str[j].size() && str[j][k] != ','; ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
			else key1 = to_register[s]; s = "";
			for (k = str[j].find('$', k) + 1; str[j][k] != ',' && k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
			else key2 = to_register[s]; s = ""; k += 2;
			for (; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s.find('$', 0) != s.npos)
			{
				s.erase(s.begin());
				if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
				else key3 = to_register[s];
				r[key1] = r[key2] - r[key3];
			}
			else
			{
				int q = atoi(s.c_str());
				r[key1] = r[key2] - q;
			}
			continue;
		}
		if (str[j].find("mulu", 0) != str[j].npos)
		{
			string s = "";
			int key1, key2, key3;
			for (k = str[j].find("mulu", 0) + 6; k < str[j].size() && str[j][k] != ','; ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
			else key1 = to_register[s]; s = "";
			for (k = str[j].find('$', k) + 1; str[j][k] != ',' && k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
			else key2 = to_register[s]; s = ""; k += 2;
			for (; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s != "")
			{
				if (s.find('$', 0) != s.npos)
				{
					s.erase(s.begin());
					if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
					else key3 = to_register[s];
					r[key1] =  (unsigned) int (r[key2]) *  (unsigned) int (r[key3]);
				}
				else
				{
					int q = atoi(s.c_str());
					r[key1] =  (unsigned) int (r[key2]) *  (unsigned) int (q);
				}
			}
			else
			{
				long long ss = r[key1]*r[key2];
				lo = ss & ((1LL << 32) - 1);
				hi = ss >> 32;
			}
			continue;
		}
		if (str[j].find("mul", 0) != str[j].npos)
		{
			string s = "";
			int key1, key2, key3;
			for (k = str[j].find("mul", 0) + 5; k < str[j].size() && str[j][k] != ','; ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
			else key1 = to_register[s]; s = "";
			for (k = str[j].find('$', k) + 1; str[j][k] != ',' && k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
			else key2 = to_register[s]; s = ""; k += 2;
			for (; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s != "")
			{
				if (s.find('$', 0) != s.npos)
				{
					s.erase(s.begin());
					if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
					else key3 = to_register[s];
					r[key1] = r[key2] * r[key3];
				}
				else
				{
					int q = atoi(s.c_str());
					r[key1] = r[key2] * q;
				}
			}
			else
			{
				long long ss = r[key1]*r[key2];
				lo = ss & ((1LL << 32) - 1);
				hi = ss >> 32;
			}
			continue;
		}
		if (str[j].find("remu", 0) != str[j].npos)
		{
			string s = "";
			int key1, key2, key3;
			for (k = str[j].find("remu", 0) + 6; k < str[j].size() && str[j][k] != ','; ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
			else key1 = to_register[s]; s = "";
			for (k = str[j].find('$', k) + 1; str[j][k] != ',' && k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
			else key2 = to_register[s]; s = ""; k += 2;
			for (; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s.find('$', 0) != s.npos)
			{
				s.erase(s.begin());
				if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
				else key3 = to_register[s];
				r[key1] = (unsigned) int (r[key2]) % (unsigned) int (r[key3]);
			}
			else
			{
				int q = atoi(s.c_str());
				r[key1] = (unsigned) int (r[key2]) % (unsigned) int (q);
			}
			continue;
		}
		if (str[j].find("rem", 0) != str[j].npos)
		{
			string s = "";
			int key1, key2, key3;
			for (k = str[j].find("rem", 0) + 5; k < str[j].size() && str[j][k] != ','; ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
			else key1 = to_register[s]; s = "";
			for (k = str[j].find('$', k) + 1; str[j][k] != ',' && k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
			else key2 = to_register[s]; s = ""; k += 2;
			for (; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s.find('$', 0) != s.npos)
			{
				s.erase(s.begin());
				if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
				else key3 = to_register[s];
				r[key1] = r[key2] % r[key3];
			}
			else
			{
				int q = atoi(s.c_str());
				r[key1] = r[key2] % q;
			}
			continue;
		}
		if (str[j].find("xoru", 0) != str[j].npos)
		{
			string s = "";
			int key1, key2, key3;
			for (k = str[j].find("xoru", 0) + 6; k < str[j].size() && str[j][k] != ','; ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
			else key1 = to_register[s]; s = "";
			for (k = str[j].find('$', k) + 1; str[j][k] != ',' && k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
			else key2 = to_register[s]; s = ""; k += 2;
			for (; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s.find('$', 0) != s.npos)
			{
				s.erase(s.begin());
				if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
				else key3 = to_register[s];
				r[key1] = (unsigned) int (r[key2])^  (unsigned) int (r[key3]);
			}
			else
			{
				int q = atoi(s.c_str());
				r[key1] =  (unsigned) int (r[key2])^ (unsigned) int (q);
			}
			continue;
		}
		if (str[j].find("xor", 0) != str[j].npos)
		{
			string s = "";
			int key1, key2, key3;
			for (k = str[j].find("xor", 0) + 5; k < str[j].size() && str[j][k] != ','; ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
			else key1 = to_register[s]; s = "";
			for (k = str[j].find('$', k) + 1; str[j][k] != ',' && k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
			else key2 = to_register[s]; s = ""; k += 2;
			for (; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s.find('$', 0) != s.npos)
			{
				s.erase(s.begin());
				if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
				else key3 = to_register[s];
				r[key1] = r[key2] ^r[key3];
			}
			else
			{
				int q = atoi(s.c_str());
				r[key1] = r[key2] ^ q;
			}
			continue;
		}
		if (str[j].find("neg", 0) == 0)
		{
			string s = "";
			int key1, key2, key3;
			for (k = str[j].find("neg", 0) + 5; k < str[j].size() && str[j][k] != ','; ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
			else key1 = to_register[s]; s = "";
			for (k = str[j].find('$', k) + 1; str[j][k] != ',' && k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
			else key2 = to_register[s]; s = ""; k += 2;
			r[key1] = -r[key2];
			continue;
		}
		if (str[j].find("divu", 0) != str[j].npos)
		{
			string s = "";
			int key1, key2, key3;
			for (k = str[j].find("divu", 0) + 6; k < str[j].size() && str[j][k] != ','; ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
			else key1 = to_register[s]; s = "";
			for (k = str[j].find('$', k) + 1; str[j][k] != ',' && k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
			else key2 = to_register[s]; s = ""; k += 2;
			for (; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s != "")
			{
				if (s.find('$', 0) != s.npos)
				{
					s.erase(s.begin());
					if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
					else key3 = to_register[s];
					r[key1] = unsigned (r[key2]) / unsigned (r[key3]);
				}
				else
				{
					int q = atoi(s.c_str());
					r[key1] = unsigned (r[key2]) / unsigned (q);
				}
			}
			else
			{
				lo = unsigned (r[key1]) / unsigned (r[key2]);
				hi = unsigned (r[key1]) % unsigned (r[key2]);
			}
			continue;
		}
		if (str[j].find("div", 0) != str[j].npos)
		{
			string s = "";
			int key1, key2, key3;
			for (k = str[j].find("div", 0) + 5; k < str[j].size() && str[j][k] != ','; ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
			else key1 = to_register[s]; s = "";
			for (k = str[j].find('$', k) + 1; str[j][k] != ',' && k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
			else key2 = to_register[s]; s = ""; k += 2;
			for (; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s != "")
			{
				if (s.find('$', 0) != s.npos)
				{
					s.erase(s.begin());
					if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
					else key3 = to_register[s];
					r[key1] = r[key2] / r[key3];
				}
				else
				{
					int q = atoi(s.c_str());
					r[key1] = r[key2] / q;
				}
			}
			else
			{
				lo = r[key1] / r[key2];
				hi = r[key1] % r[key2];
			}
			continue;
		}
		if (str[j].find("mfhi", 0) != str[j].npos)
		{
			string s = "";
			int key;
			for (k = str[j].find("mfhi", 0) + 6; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
			else key = to_register[s];
			r[key] = hi;
			continue;
		}
		if (str[j].find("mflo", 0) != str[j].npos)
		{
			string s = "";
			int key;
			for (k = str[j].find("mflo", 0) + 6; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
			else key = to_register[s];
			r[key] = lo;
			continue;
		}
		if (str[j].find("move", 0) != str[j].npos)
		{
			string s = "";
			int key1, key2;
			for (k = str[j].find("move", 0) + 6; k < str[j].size() && str[j][k] != ','; ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
			else key1 = to_register[s]; s = "";
			for (k = str[j].find('$', k) + 1; str[j][k] != ',' && k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
			else key2 = to_register[s]; s = "";
			r[key1] = r[key2];
		}
		if (str[j].find("beqz", 0) != str[j].npos)
		{
			++snum;
			string s = "";
			int key1, key2;
			bool b = false;
			for (k = str[j].find('$', 0) + 1; str[j][k] != ',' && k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
			else key1 = to_register[s]; s = "";   k += 2;
			if (r[key1] == 0) b = true;
			if (b == true)
			{
				for (; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
				s += ':';
				j = label[s];
			}
			continue;
		}
		if (str[j].find("bnez", 0) != str[j].npos)
		{
			++snum;
			string s = "";
			int key1, key2;
			bool b = false;
			for (k = str[j].find('$', 0) + 1; str[j][k] != ',' && k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
			else key1 = to_register[s]; s = "";   k += 2;
			if (r[key1] != 0) b = true;
			if (b == true)
			{
				for (; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
				s += ':';
				j = label[s];
			}
			continue;
		}
		if (str[j].find("blez", 0) != str[j].npos)
		{
			++snum;
			string s = "";
			int key1, key2;
			bool b = false;
			for (k = str[j].find('$', 0) + 1; str[j][k] != ',' && k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
			else key1 = to_register[s]; s = "";   k += 2;
			if (r[key1] <= 0) b = true;
			if (b == true)
			{
				for (; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
				s += ':';
				j = label[s];
			}
			continue;
		}
		if (str[j].find("bgez", 0) != str[j].npos)
		{
			++snum;
			string s = "";
			int key1, key2;
			bool b = false;
			for (k = str[j].find('$', 0) + 1; str[j][k] != ',' && k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
			else key1 = to_register[s]; s = "";   k += 2;
			if (r[key1] >= 0) b = true;
			if (b == true)
			{
				for (; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
				s += ':';
				j = label[s];
			}
			continue;
		}
		if (str[j].find("bgtz", 0) != str[j].npos)
		{
			++snum;
			string s = "";
			int key1, key2;
			bool b = false;
			for (k = str[j].find('$', 0) + 1; str[j][k] != ',' && k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
			else key1 = to_register[s]; s = "";   k += 2;
			if (r[key1] > 0) b = true;
			if (b == true)
			{
				for (; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
				s += ':';
				j = label[s];
			}
			//cout << key1 << ' ' << r[key1] << endl;
			continue;
		}
		if (str[j].find("bltz", 0) != str[j].npos)
		{
			++snum;
			string s = "";
			int key1, key2;
			bool b = false;
			for (k = str[j].find('$', 0) + 1; str[j][k] != ',' && k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
			else key1 = to_register[s]; s = "";   k += 2;
			if (r[key1] < 0) b = true;
			if (b == true)
			{
				for (; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
				s += ':';
				j = label[s];
			}
			continue;
		}
		if (str[j].find("beq", 0) != str[j].npos)
		{
			++snum;
			string s = "";
			int key1, key2;
			bool b = false;
			for (k = str[j].find('$', 0) + 1; str[j][k] != ',' && k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
			else key1 = to_register[s]; s = "";   k += 2;
			for (; str[j][k] != ','; ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s.find('$', 0) != s.npos)
			{
				s.erase(s.begin());
				if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
				else key2 = to_register[s];
				if (r[key1] == r[key2]) b = true;
			}
			else
			{
				int q = atoi(s.c_str());
				if (r[key1] == q) b = true;
			} k += 2; s = "";
			if (b == true)
			{
				for (; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
				s += ':';
				j = label[s];
			}
			continue;
		}
		if (str[j].find("bne", 0) != str[j].npos)
		{
			++snum;
			string s = "";
			int key1, key2;
			bool b = false;
			for (k = str[j].find('$', 0) + 1; str[j][k] != ',' && k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
			else key1 = to_register[s]; s = "";   k += 2;
			for (; str[j][k] != ','; ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s.find('$', 0) != s.npos)
			{
				s.erase(s.begin());
				if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
				else key2 = to_register[s];
				if (r[key1] != r[key2]) b = true;
			}
			else
			{
				int q = atoi(s.c_str());
				if (r[key1] != q) b = true;
			} k += 2; s = "";
			if (b == true)
			{
				for (; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
				s += ':';
				j = label[s];
			}
			continue;
		}
		if (str[j].find("bge", 0) != str[j].npos)
		{
			++snum;
			string s = "";
			int key1, key2;
			bool b = false;
			for (k = str[j].find('$', 0) + 1; str[j][k] != ',' && k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
			else key1 = to_register[s]; s = ""; k += 2;
			for (; str[j][k] != ','; ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s.find('$', 0) != s.npos)
			{
				s.erase(s.begin());
				if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
				else key2 = to_register[s];
				if (r[key1] >= r[key2]) b = true;
			//	cout<<key1<<' '<<key2<<' '<<r[key1]<<' '<<r[key2]<<endl;
			}
			else
			{
				int q = atoi(s.c_str());
				if (r[key1] >= q) b = true;
			} k += 2; s = "";
			if (b == true)
			{
				for (; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
				s += ':';
				j = label[s];
			}
			continue;
		}
		if (str[j].find("ble", 0) != str[j].npos)
		{
			++snum;
			string s = "";
			int key1, key2;
			bool b = false;
			for (k = str[j].find('$', 0) + 1; str[j][k] != ',' && k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
			else key1 = to_register[s]; s = ""; k += 2;
			for (; str[j][k] != ','; ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s.find('$', 0) != s.npos)
			{
				s.erase(s.begin());
				if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
				else key2 = to_register[s];
				if (r[key1] <= r[key2]) b = true;
			}
			else
			{
				int q = atoi(s.c_str());
				if (r[key1] <= q) b = true;
			} k += 2; s = "";
			if (b == true)
			{
				for (; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
				s += ':';
				j = label[s];
			}
			continue;
		}
		if (str[j].find("bgt", 0) != str[j].npos)
		{
			++snum;
			string s = "";
			int key1, key2;
			bool b = false;
			for (k = str[j].find('$', 0) + 1; str[j][k] != ',' && k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
			else key1 = to_register[s]; s = ""; k += 2;
			for (; str[j][k] != ','; ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s.find('$', 0) != s.npos)
			{
				s.erase(s.begin());
				if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
				else key2 = to_register[s];
				if (r[key1] > r[key2]) b = true;
				//cout<<"              "<<key1<<' '<<r[key1]<<' '<<key2<<' '<<r[key2]<<endl;
			}
			else
			{
				int q = atoi(s.c_str());
				if (r[key1] > q) b = true;
				//	cout<<"              "<<key1<<' '<<r[key1]<<' '<<q<<endl;
			} k += 2; s = "";
			if (b == true)
			{
				for (; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
				s += ':';
				j = label[s];
			}
			continue;
		}
		if (str[j].find("blt", 0) != str[j].npos)
		{
			++snum;
			string s = "";
			int key1, key2;
			bool b = false;
			for (k = str[j].find('$', 0) + 1; str[j][k] != ',' && k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
			else key1 = to_register[s]; s = ""; k += 2;
			for (; str[j][k] != ','; ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s.find('$', 0) != s.npos)
			{
				s.erase(s.begin());
				if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
				else key2 = to_register[s];
				if (r[key1] < r[key2]) b = true;
				// cout<<"              "<<key1<<' '<<r[key1]<<' '<<key2<<' '<<r[key2]<<endl;
			}
			else
			{
				int q = atoi(s.c_str());
				if (r[key1] < q) b = true;
				//	cout<<"              "<<key1<<' '<<r[key1]<<' '<<q<<endl;
			} k += 2; s = "";
			if (b == true)
			{
				for (; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
				s += ':';
				j = label[s];
			}
			continue;
		}
		if (str[j].find("seq", 0) != str[j].npos)
		{
			string s = "";
			int key1, key2, key3;
			for (k = str[j].find("seq", 0) + 5; k < str[j].size() && str[j][k] != ','; ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
			else key1 = to_register[s]; s = "";
			for (k = str[j].find('$', k) + 1; str[j][k] != ',' && k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
			else key2 = to_register[s]; s = ""; k += 2;
			for (; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s.find('$', 0) != s.npos)
			{
				s.erase(s.begin());
				if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
				else key3 = to_register[s];
				if (r[key2] == r[key3]) r[key1] = 1; else r[key1] = 0;
			}
			else
			{
				int q = atoi(s.c_str());
				if (r[key2] == q) r[key1] = 1; else r[key1] = 0;
			}
			continue;
		}
		if (str[j].find("sge", 0) != str[j].npos)
		{
			string s = "";
			int key1, key2, key3;
			for (k = str[j].find("sge", 0) + 5; k < str[j].size() && str[j][k] != ','; ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
			else key1 = to_register[s]; s = "";
			for (k = str[j].find('$', k) + 1; str[j][k] != ',' && k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
			else key2 = to_register[s]; s = ""; k += 2;
			for (; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s.find('$', 0) != s.npos)
			{
				s.erase(s.begin());
				if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
				else key3 = to_register[s];
				if (r[key2] >= r[key3]) r[key1] = 1; else r[key1] = 0;
			}
			else
			{
				int q = atoi(s.c_str());
				if (r[key2] >= q) r[key1] = 1; else r[key1] = 0;
			}
			continue;
		}
		if (str[j].find("sgt", 0) != str[j].npos)
		{
			string s = "";
			int key1, key2, key3;
			for (k = str[j].find("sgt", 0) + 5; k < str[j].size() && str[j][k] != ','; ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
			else key1 = to_register[s]; s = "";
			for (k = str[j].find('$', k) + 1; str[j][k] != ',' && k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
			else key2 = to_register[s]; s = ""; k += 2;
			for (; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s.find('$', 0) != s.npos)
			{
				s.erase(s.begin());
				if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
				else key3 = to_register[s];
				if (r[key2] > r[key3]) r[key1] = 1; else r[key1] = 0;
			}
			else
			{
				int q = atoi(s.c_str());
				if (r[key2] > q) r[key1] = 1; else r[key1] = 0;
			}
			continue;
		}
		if (str[j].find("sle", 0) != str[j].npos)
		{
			string s = "";
			int key1, key2, key3;
			for (k = str[j].find("sle", 0) + 5; k < str[j].size() && str[j][k] != ','; ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
			else key1 = to_register[s]; s = "";
			for (k = str[j].find('$', k) + 1; str[j][k] != ',' && k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
			else key2 = to_register[s]; s = ""; k += 2;
			for (; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s.find('$', 0) != s.npos)
			{
				s.erase(s.begin());
				if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
				else key3 = to_register[s];
				if (r[key2] <= r[key3]) r[key1] = 1; else r[key1] = 0;
			}
			else
			{
				int q = atoi(s.c_str());
				if (r[key2] <= q) r[key1] = 1; else r[key1] = 0;
			}
			continue;
		}
		if (str[j].find("slt", 0) != str[j].npos)
		{
			string s = "";
			int key1, key2, key3;
			for (k = str[j].find("slt", 0) + 5; k < str[j].size() && str[j][k] != ','; ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
			else key1 = to_register[s]; s = "";
			for (k = str[j].find('$', k) + 1; str[j][k] != ',' && k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
			else key2 = to_register[s]; s = ""; k += 2;
			for (; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s.find('$', 0) != s.npos)
			{
				s.erase(s.begin());
				if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
				else key3 = to_register[s];
				if (r[key2] < r[key3]) r[key1] = 1; else r[key1] = 0;
			}
			else
			{
				int q = atoi(s.c_str());
				if (r[key2] < q) r[key1] = 1; else r[key1] = 0;
			}
			continue;
		}
		if (str[j].find("sne", 0) != str[j].npos)
		{
			string s = "";
			int key1, key2, key3;
			for (k = str[j].find("sne", 0) + 5; k < str[j].size() && str[j][k] != ','; ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
			else key1 = to_register[s]; s = "";
			for (k = str[j].find('$', k) + 1; str[j][k] != ',' && k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
			else key2 = to_register[s]; s = ""; k += 2;
			for (; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s.find('$', 0) != s.npos)
			{
				s.erase(s.begin());
				if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
				else key3 = to_register[s];
				if (r[key2] != r[key3]) r[key1] = 1; else r[key1] = 0;
			}
			else
			{
				int q = atoi(s.c_str());
				if (r[key2] != q) r[key1] = 1; else r[key1] = 0;
			}
			continue;
		}
		if (str[j][0] == 'b')
		{
			string s = "";
			for (k = 2; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			s += ':';
			// cout<<j<<' '<<s<<endl; 
			j = label[s];
			continue;
		}
		if (str[j][0] == 'j')
		{
			string s = "";
			for (k = 2; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			s += ':';
			// cout<<j<<' '<<s<<endl; 
			j = label[s];
			continue;
		}
	}
}












