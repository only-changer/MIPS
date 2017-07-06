#include<cstdio>
#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<cstdlib>
#include<fstream>
#include<ctime>
#include<cstdlib>
const int N = 10000000;
using namespace std;
vector<string> str;
map<string, int> label;
map<string, int> data_label;
map<string, int> to_register;
map<string, int> to_int;
int hazard = 0;
int ha[5] = { 0 };
int mark = 0;
int i = -1, j, k = 0;
int r[32] = { 0 };
int f[34] = { 0 };
int BP[120] = { 0 };
int tbp[120][16] = { 0 };
vector<bool> all[120];
int cnum = 0, snum = 0;
int lo = 0, hi = 0;
string jump;
void inc(int x)
{
	if (all[x].size() <= 4) return;
	else
	{
		int z = all[x].size();
		int y = (all[x][z - 5] * 8 + all[x][z - 4] * 4 + all[x][z - 3] * 2 + all[x][z - 2]);
		if (all[x][z - 1] == 1)
		{
			++tbp[x][y];
			if (tbp[x][y] > 4) tbp[x][y] = 4;
		}
	}
}
void dec(int x)
{
	if (all[x].size() <= 4) return;
	else
	{
		int z = all[x].size();
		int y = (all[x][z - 5] * 8 + all[x][z - 4] * 4 + all[x][z - 3] * 2 + all[x][z - 2]);
		if (all[x][z - 1] == 0)
		{
			--tbp[x][y];
			if (tbp[x][y] < 0) tbp[x][y] = 0;
		}
	}
}
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
	to_int["add"] = 1;
	to_int["addu"] = 2;
	to_int["sub"] = 3;
	to_int["subu"] = 4;
	to_int["mul"] = 5;
	to_int["mulu"] = 6;
	to_int["div"] = 7;
	to_int["divu"] = 8;
	to_int["xor"] = 9;
	to_int["xoru"] = 10;
	to_int["neg"] = 11;
	to_int["negu"] = 12;
	to_int["rem"] = 13;
	to_int["remu"] = 14;
	to_int["li"] = 15;
	to_int["seq"] = 16;
	to_int["sge"] = 17;
	to_int["sgt"] = 18;
	to_int["sle"] = 19;
	to_int["slt"] = 20;
	to_int["sne"] = 21;
	to_int["b"] = 22;
	to_int["beq"] = 23;
	to_int["bne"] = 24;
	to_int["bge"] = 25;
	to_int["ble"] = 26;
	to_int["bgt"] = 27;
	to_int["blt"] = 28;
	to_int["beqz"] = 29;
	to_int["bnez"] = 30;
	to_int["bgez"] = 31;
	to_int["blez"] = 32;
	to_int["bgtz"] = 33;
	to_int["bltz"] = 34;
	to_int["j"] = 35;
	to_int["jr"] = 36;
	to_int["jal"] = 37;
	to_int["la"] = 38;
	to_int["lb"] = 39;
	to_int["lw"] = 40;
	to_int["sb"] = 41;
	to_int["sw"] = 42;
	to_int["move"] = 43;
	to_int["mfhi"] = 44;
	to_int["mflo"] = 45;
	to_int["syscall"] = 46;
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
int maxx(int x, int y)
{
	if (x > y) return x;
	else return y;
}
int DH(int x)
{
	if (f[x] == 1)
	{
		hazard = 2;
		mark = 0;
	}
	return 0;
}
int LDH(int x)
{
	int m = f[x];
	f[x] = 1;
	return m;
}
class add
{
private:
	int key1, key2, type, key3, q;
	int ans;
	int h = 0;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("add", 0) + 5; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";
		for (k = str.find('$', k) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		else key2 = to_register[s]; s = ""; k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key2));
		if (s.find('$', 0) != s.npos)
		{
			s.erase(s.begin());
			if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
			else key3 = to_register[s];
			type = 1;
			h = maxx(h, DH(key3));
		}
		else
		{
			q = atoi(s.c_str());
			type = 2;
		}
		h = maxx(h, LDH(key1));
	}
	void EX()
	{
		if (type == 1) ans = r[key2] + r[key3];
		else ans = r[key2] + q;
	}
	void WB()
	{
		f[key1] = h;
		//if (type == 1) cout << key1 << ' ' << key2 << ' ' << key3 << ' ' << r[key1] << ' ' << r[key2] << ' ' << r[key3] << endl;
		r[key1] = ans;
	}
};
class addu
{
private:
	int key1, key2, type, key3, q, ans;
	int h = 0;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("addu", 0) + 6; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";
		for (k = str.find('$', k) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		else key2 = to_register[s]; s = ""; k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];

		h = maxx(h, DH(key2));
		if (s.find('$', 0) != s.npos)
		{
			s.erase(s.begin());
			if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
			else key3 = to_register[s];
			h = maxx(h, DH(key3));
			type = 1;
		}
		else
		{
			q = atoi(s.c_str());
			type = 2;
		}
		h = maxx(h, LDH(key1));
	}
	void EX()
	{
		if (type == 1) ans = (unsigned) int(r[key2]) + (unsigned) int(r[key3]);
		else ans = (unsigned) int(r[key2]) + (unsigned) int(q);
	}
	void WB()
	{
		f[key1] = h;
		r[key1] = ans;
	}
};
class sub
{
private:
	int key1, key2, type, key3, q, ans;
	int h = 0;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("sub", 0) + 5; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";
		for (k = str.find('$', k) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		else key2 = to_register[s]; s = ""; k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];

		h = maxx(h, DH(key2));
		if (s.find('$', 0) != s.npos)
		{
			s.erase(s.begin());
			if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
			else key3 = to_register[s];
			h = maxx(h, DH(key3));
			type = 1;
		}
		else
		{
			q = atoi(s.c_str());
			type = 2;
		}
		h = maxx(h, LDH(key1));
	}
	void EX()
	{
		if (type == 1) ans = r[key2] - r[key3];
		else ans = r[key2] - q;
	}
	void WB()
	{
		f[key1] = h;
		r[key1] = ans;
	}
};
class subu
{
private:
	int key1, key2, type, key3, q, ans;
	int h = 0;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("subu", 0) + 6; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";
		for (k = str.find('$', k) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		else key2 = to_register[s]; s = ""; k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];

		h = maxx(h, DH(key2));
		if (s.find('$', 0) != s.npos)
		{
			s.erase(s.begin());
			if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
			else key3 = to_register[s];
			type = 1;
			h = maxx(h, DH(key3));
		}
		else
		{
			q = atoi(s.c_str());
			type = 2;
		}
		h = maxx(h, LDH(key1));
	}
	void EX()
	{
		if (type == 1) ans = (unsigned) int(r[key2]) - (unsigned) int(r[key3]);
		else ans = (unsigned) int(r[key2]) - (unsigned) int(q);
	}
	void WB()
	{
		f[key1] = h;
		r[key1] = ans;
	}
};
class mul
{
private:
	int key1, key2, key3, type, q, loer, hier, ans;
	int h, h1, h2;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("mul", 0) + 5; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";
		for (k = str.find('$', k) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		else key2 = to_register[s]; s = ""; k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];

		h = maxx(h, DH(key2));
		if (s != "")
		{
			if (s.find('$', 0) != s.npos)
			{
				s.erase(s.begin());
				if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
				else key3 = to_register[s];
				h = maxx(h, DH(key3));
				type = 1;
			}
			else
			{
				q = atoi(s.c_str());
				type = 2;
			}
			h = maxx(h, LDH(key1));
		}
		else
		{
			type = 3;
			h = maxx(h, DH(key1));
			h1 = maxx(h1, LDH(32));
			h2 = maxx(h2, LDH(33));
		}

	}
	void EX()
	{
		if (type == 1) ans = r[key2] * r[key3];
		if (type == 2) ans = r[key2] * q;
		if (type == 3)
		{
			long long ss = r[key1] * r[key2];
			loer = ss & ((1LL << 32) - 1);
			hier = ss >> 32;
		}
	}
	void WB()
	{
		if (type <= 2) f[key1] = h; else { f[32] = h1; f[33] = h2; }
		if (type <= 2) r[key1] = ans;
		else
		{
			lo = loer;
			hi = hier;
		}
	}
};
class mulu
{
private:
	int key1, key2, key3, type, q, loer, hier, ans;
	int h = 0, h1, h2;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("mulu", 0) + 6; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";
		for (k = str.find('$', k) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		else key2 = to_register[s]; s = ""; k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key2));
		if (s != "")
		{
			if (s.find('$', 0) != s.npos)
			{
				s.erase(s.begin());
				if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
				else key3 = to_register[s];
				h = maxx(h, DH(key3));
				type = 1;
			}
			else
			{
				q = atoi(s.c_str());
				type = 2;
			}
			h = maxx(h, LDH(key1));
		}
		else
		{
			type = 3;
			h = maxx(h, DH(key1));
			h1 = maxx(h1, LDH(32));
			h2 = maxx(h2, LDH(33));
		}
	}
	void EX()
	{
		if (type == 1) ans = (unsigned) int(r[key2]) * (unsigned) int(r[key3]);
		if (type == 2) ans = (unsigned) int(r[key2]) * (unsigned) int(q);
		if (type == 3)
		{
			long long ss = r[key1] * r[key2];
			loer = ss & ((1LL << 32) - 1);
			hier = ss >> 32;
		}
	}
	void WB()
	{
		if (type <= 2) f[key1] = h; else { f[32] = h1; f[33] = h2; }
		if (type == 1) f[key3] = 0;
		if (type <= 2) r[key1] = ans;
		else
		{
			lo = loer;
			hi = hier;
		}
	}
};
class divv
{
private:
	int key1, key2, key3, type, q, loer, hier, ans;
	int h = 0, h2, h1;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("div", 0) + 5; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";
		for (k = str.find('$', k) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		else key2 = to_register[s]; s = ""; k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];

		h = maxx(h, DH(key2));
		if (s != "")
		{
			if (s.find('$', 0) != s.npos)
			{
				s.erase(s.begin());
				if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
				else key3 = to_register[s];
				type = 1;
				h = maxx(h, DH(key3));
			}
			else
			{
				q = atoi(s.c_str());
				type = 2;
			}
			h = maxx(h, LDH(key1));
		}
		else
		{
			type = 3;
			h = maxx(h, DH(key1));
			h1 = maxx(h1, LDH(32));
			h2 = maxx(h2, LDH(33));
		}
	}
	void EX()
	{
		if (type == 1) ans = r[key2] / r[key3];
		if (type == 2) ans = r[key2] / q;
		if (type == 3)
		{
			loer = r[key1] / r[key2];
			hier = r[key1] % r[key2];
		}
	}
	void WB()
	{
		if (type <= 2) f[key1] = h; else { f[32] = h1; f[33] = h2; }
		if (type <= 2) r[key1] = ans;
		else
		{
			lo = loer;
			hi = hier;
		}
	}
};
class divvu
{
private:
	int key1, key2, key3, type, q, loer, hier, ans;
	int h = 0, h1, h2;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("divu", 0) + 6; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";
		for (k = str.find('$', k) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		else key2 = to_register[s]; s = ""; k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];

		h = maxx(h, DH(key2));
		if (s != "")
		{
			if (s.find('$', 0) != s.npos)
			{
				s.erase(s.begin());
				if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
				else key3 = to_register[s];
				h = maxx(h, DH(key3));
				type = 1;
			}
			else
			{
				q = atoi(s.c_str());
				type = 2;
			}
			h = maxx(h, LDH(key1));
		}
		else
		{
			type = 3;
			h = maxx(h, DH(key1));
			h1 = maxx(h1, LDH(32));
			h2 = maxx(h2, LDH(33));
		}
	}
	void EX()
	{
		if (type == 1) ans = (unsigned) int(r[key2]) / (unsigned) int(r[key3]);
		if (type == 2) ans = (unsigned) int(r[key2]) / (unsigned) int(q);
		if (type == 3)
		{
			loer = r[key1] / r[key2];
			hier = r[key1] % r[key2];
		}
	}
	void WB()
	{
		if (type <= 2) f[key1] = h; else { f[32] = h1; f[33] = h2; }
		if (type <= 2) r[key1] = ans;
		else
		{
			lo = loer;
			hi = hier;
		}
	}
};
class xxor
{
private:
	int key1, key2, type, key3, q, ans;
	int h = 0;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("xor", 0) + 5; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";
		for (k = str.find('$', k) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		else key2 = to_register[s]; s = ""; k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];

		h = maxx(h, DH(key2));
		if (s.find('$', 0) != s.npos)
		{
			s.erase(s.begin());
			if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
			else key3 = to_register[s];
			h = maxx(h, DH(key3));
			type = 1;
		}
		else
		{
			q = atoi(s.c_str());
			type = 2;
		}
		h = maxx(h, LDH(key1));
	}
	void EX()
	{
		if (type == 1) ans = r[key2] ^ r[key3];
		else ans = r[key2] ^ q;
	}
	void WB()
	{
		f[key1] = h;
		r[key1] = ans;
	}
};
class xxoru
{
private:
	int key1, key2, type, key3, q, ans;
	int h = 0;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("xoru", 0) + 6; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";
		for (k = str.find('$', k) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		else key2 = to_register[s]; s = ""; k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];

		h = maxx(h, DH(key2));
		if (s.find('$', 0) != s.npos)
		{
			s.erase(s.begin());
			if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
			else key3 = to_register[s];
			h = maxx(h, DH(key3));
			type = 1;
		}
		else
		{
			q = atoi(s.c_str());
			type = 2;
		}
		h = maxx(h, LDH(key1));
	}
	void EX()
	{
		if (type == 1) ans = (unsigned) int(r[key2]) ^ (unsigned) int(r[key3]);
		else ans = (unsigned) int(r[key2]) ^ (unsigned) int(q);
	}
	void WB()
	{
		f[key1] = h;
		r[key1] = ans;
	}
};
class neg
{
private:
	int key1, key2, ans;
	int h = 0;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("neg", 0) + 5; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";
		for (k = str.find('$', k) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		else key2 = to_register[s]; s = "";

		h = maxx(h, DH(key2));
		h = maxx(h, LDH(key1));
	}
	void EX()
	{
		ans = (-1)*r[key2];
	}
	void WB()
	{
		f[key1] = h;
		r[key1] = ans;
	}
};
class negu
{
private:
	int key1, key2, ans;
	int h = 0;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("negu", 0) + 6; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";
		for (k = str.find('$', k) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		else key2 = to_register[s]; s = "";

		h = maxx(h, DH(key2));
		h = maxx(h, LDH(key1));
	}
	void EX()
	{
		ans = (-1)* (unsigned) int(r[key2]);
	}
	void WB()
	{
		f[key1] = h;
		r[key1] = ans;
	}
};
class rem
{
private:
	int key1, key2, type, key3, q, ans;
	int h = 0;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("rem", 0) + 5; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";
		for (k = str.find('$', k) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		else key2 = to_register[s]; s = ""; k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];

		h = maxx(h, DH(key2));
		if (s.find('$', 0) != s.npos)
		{
			s.erase(s.begin());
			if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
			else key3 = to_register[s];
			type = 1;
			h = maxx(h, DH(key3));
		}
		else
		{
			q = atoi(s.c_str());
			type = 2;
		}
		h = maxx(h, LDH(key1));
	}
	void EX()
	{
		if (type == 1) ans = r[key2] % r[key3];
		else ans = r[key2] % q;
	}
	void WB()
	{
		f[key1] = h;
		r[key1] = ans;
	}
};
class remu
{
private:
	int key1, key2, type, key3, q, ans;
	int h = 0;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("remu", 0) + 6; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";
		for (k = str.find('$', k) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		else key2 = to_register[s]; s = ""; k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];

		h = maxx(h, DH(key2));
		if (s.find('$', 0) != s.npos)
		{
			s.erase(s.begin());
			if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
			else key3 = to_register[s];
			h = maxx(h, DH(key3));
			type = 1;
		}
		else
		{
			q = atoi(s.c_str());
			type = 2;
		}
		h = maxx(h, LDH(key1));
	}
	void EX()
	{
		if (type == 1) ans = (unsigned) int(r[key2]) % (unsigned) int(r[key3]);
		else ans = (unsigned) int(r[key2]) % (unsigned) int(q);
	}
	void WB()
	{
		f[key1] = h;
		r[key1] = ans;
	}
};
class li
{
private:
	int key, p;
	int h = 0;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("li", 0) + 4; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
		else key = to_register[s]; s = "";
		for (k = str.find(",", 0) + 1; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		p = atoi(s.c_str());
		h = maxx(h, LDH(key));
	}
	void EX() {}
	void WB()
	{
		f[key] = h;
		r[key] = p;
	}
};
class seq
{
private:
	int key1, key2, key3, type, q, ans;
	int h = 0;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("seq", 0) + 5; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";
		for (k = str.find('$', k) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		else key2 = to_register[s]; s = ""; k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];

		h = maxx(h, DH(key2));
		if (s.find('$', 0) != s.npos)
		{
			s.erase(s.begin());
			if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
			else key3 = to_register[s];
			h = maxx(h, DH(key3));
			type = 1;
		}
		else
		{
			q = atoi(s.c_str());
			type = 2;
		}
		h = maxx(h, LDH(key1));
	}
	void EX()
	{
		if (type == 1) if (r[key2] == r[key3]) ans = 1; else ans = 0;
		if (type == 2) if (r[key2] == q) ans = 1; else ans = 0;
	}
	void WB()
	{
		f[key1] = h;
		r[key1] = ans;
	}
};
class sge
{
private:
	int key1, key2, key3, type, q, ans;
	int h = 0;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("sge", 0) + 5; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";
		for (k = str.find('$', k) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		else key2 = to_register[s]; s = ""; k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];

		h = maxx(h, DH(key2));
		if (s.find('$', 0) != s.npos)
		{
			s.erase(s.begin());
			if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
			else key3 = to_register[s];
			h = maxx(h, DH(key3));
			type = 1;
		}
		else
		{
			q = atoi(s.c_str());
			type = 2;
		}
		h = maxx(h, LDH(key1));
	}
	void EX()
	{
		if (type == 1) if (r[key2] >= r[key3]) ans = 1; else ans = 0;
		if (type == 2) if (r[key2] >= q) ans = 1; else ans = 0;
	}
	void WB()
	{
		f[key1] = h;
		r[key1] = ans;
	}
};
class sgt
{
private:
	int key1, key2, key3, type, q, ans;
	int h = 0;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("sgt", 0) + 5; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";
		for (k = str.find('$', k) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		else key2 = to_register[s]; s = ""; k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];

		h = maxx(h, DH(key2));
		if (s.find('$', 0) != s.npos)
		{
			s.erase(s.begin());
			if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
			else key3 = to_register[s];
			h = maxx(h, DH(key3));
			type = 1;
		}
		else
		{
			q = atoi(s.c_str());
			type = 2;
		}
		h = maxx(h, LDH(key1));
	}
	void EX()
	{
		if (type == 1) if (r[key2] > r[key3]) ans = 1; else ans = 0;
		if (type == 2) if (r[key2] > q) ans = 1; else ans = 0;
	}
	void WB()
	{
		f[key1] = h;
		r[key1] = ans;
	}
};
class sle
{
private:
	int key1, key2, key3, type, q, ans;
	int h = 0;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("sle", 0) + 5; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";
		for (k = str.find('$', k) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		else key2 = to_register[s]; s = ""; k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];

		h = maxx(h, DH(key2));
		if (s.find('$', 0) != s.npos)
		{
			s.erase(s.begin());
			if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
			else key3 = to_register[s];
			h = maxx(h, DH(key3));
			type = 1;
		}
		else
		{
			q = atoi(s.c_str());
			type = 2;
		}
		h = maxx(h, LDH(key1));
	}
	void EX()
	{
		if (type == 1) if (r[key2] <= r[key3]) ans = 1; else ans = 0;
		if (type == 2) if (r[key2] <= q) ans = 1; else ans = 0;
	}
	void WB()
	{
		f[key1] = h;
		r[key1] = ans;
	}
};
class slt
{
private:
	int key1, key2, key3, type, q, ans;
	int h = 0;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("slt", 0) + 5; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";
		for (k = str.find('$', k) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		else key2 = to_register[s]; s = ""; k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];

		h = maxx(h, DH(key2));
		if (s.find('$', 0) != s.npos)
		{
			s.erase(s.begin());
			if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
			else key3 = to_register[s];
			h = maxx(h, DH(key3));
			type = 1;
		}
		else
		{
			q = atoi(s.c_str());
			type = 2;
		}
		h = maxx(h, LDH(key1));
	}
	void EX()
	{
		if (type == 1) if (r[key2] < r[key3]) ans = 1; else ans = 0;
		if (type == 2) if (r[key2] < q) ans = 1; else ans = 0;
	}
	void WB()
	{
		f[key1] = h;
		r[key1] = ans;
	}
};
class sne
{
private:
	int key1, key2, key3, type, q, ans;
	int h = 0;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("sne", 0) + 5; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";
		for (k = str.find('$', k) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		else key2 = to_register[s]; s = ""; k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];

		h = maxx(h, DH(key2));
		if (s.find('$', 0) != s.npos)
		{
			s.erase(s.begin());
			if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
			else key3 = to_register[s];
			h = maxx(h, DH(key3));
			type = 1;
		}
		else
		{
			q = atoi(s.c_str());
			type = 2;
		}
		h = maxx(h, LDH(key1));
	}
	void EX()
	{
		if (type == 1) if (r[key2] != r[key3]) ans = 1; else ans = 0;
		if (type == 2) if (r[key2] != q) ans = 1; else ans = 0;
	}
	void WB()
	{
		f[key1] = h;
		r[key1] = ans;
	}
};
class bb
{
private:
	string s;
public:
	void DP(string str)
	{
		hazard = 1; mark = 0;
		s = "";
		for (k = 2; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		s += ':';
	}
	void EX() {}
	int WB()
	{

		return label[s];
	}
};
class beq//23
{
private:
	int key1, key2, type, q;
	bool b;
	int h = 0;
	string s;
public:
	void DP(string str)
	{
		//	hazard = 1; 
		mark = 0;
		s = "";
		for (k = str.find('$', 0) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";   k += 2;
		for (; str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key1));
		if (s.find('$', 0) != s.npos)
		{
			s.erase(s.begin());
			if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
			else key2 = to_register[s];
			h = maxx(h, DH(key2));
			type = 1;
		}
		else
		{
			q = atoi(s.c_str());
			type = 2;
		} k += 2; s = "";
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		s += ':';
		jump = s;
	}
	bool EX()
	{
		if (type == 1) b = (r[key1] == r[key2]);
		else b = (r[key1] == q);
		return b;
	}
	int WB()
	{
		if (b == true) return label[s]; else return 0;
	}
};
class bne
{
private:
	int key1, key2, type, q;
	int h = 0;
	bool b;
	string s;
public:
	void DP(string str)
	{
		//	hazard = 1; 
		mark = 0;
		s = "";
		for (k = str.find('$', 0) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";   k += 2;
		for (; str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key1));
		if (s.find('$', 0) != s.npos)
		{
			s.erase(s.begin());
			if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
			else key2 = to_register[s];
			h = maxx(h, DH(key2));
			type = 1;
		}
		else
		{
			q = atoi(s.c_str());
			type = 2;
		} k += 2; s = "";
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		s += ':';
		jump = s;
	}
	bool EX()
	{
		if (type == 1) b = (r[key1] != r[key2]);
		else b = (r[key1] != q);
		return b;
	}
	int WB()
	{
		if (b == true) return label[s]; else return 0;
	}
};
class bge
{
private:
	int key1, key2, type, q;
	bool b;
	int h = 0;
	string s;
public:
	void DP(string str)
	{
		//	hazard = 1; 
		mark = 0;
		s = "";
		for (k = str.find('$', 0) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";   k += 2;
		for (; str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key1));
		if (s.find('$', 0) != s.npos)
		{
			s.erase(s.begin());
			if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
			else key2 = to_register[s];
			h = maxx(h, DH(key2));
			type = 1;
		}
		else
		{
			q = atoi(s.c_str());
			type = 2;
		} k += 2; s = "";
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		s += ':';
		jump = s;
	}
	bool EX()
	{
		if (type == 1) b = (r[key1] >= r[key2]);
		else b = (r[key1] >= q);
		return b;
	}
	int WB()
	{
		//	cout << key1 << ' ' << key2 << ' ' << r[key1] << ' ' << r[key2] << endl;


		if (b == true) return label[s]; else return 0;
	}
};
class ble
{
private:
	int key1, key2, type, q;
	int h = 0;
	bool b;
	string s;
public:
	void DP(string str)
	{
		//	hazard = 1; 
		mark = 0;
		s = "";
		for (k = str.find('$', 0) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";   k += 2;
		for (; str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key1));
		if (s.find('$', 0) != s.npos)
		{
			s.erase(s.begin());
			if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
			else key2 = to_register[s];
			h = maxx(h, DH(key2));
			type = 1;
		}
		else
		{
			q = atoi(s.c_str());
			type = 2;
		} k += 2; s = "";
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		s += ':';
		jump = s;
	}
	bool EX()
	{
		if (type == 1) b = (r[key1] <= r[key2]);
		else b = (r[key1] <= q);
		return b;
	}
	int WB()
	{
		if (b == true) return label[s]; else return 0;
	}
};
class bgt
{
private:
	int key1, key2, type, q;
	bool b;
	string s;
	int h = 0;
public:
	void DP(string str)
	{
		//	hazard = 1; 
		mark = 0;
		s = "";
		for (k = str.find('$', 0) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";   k += 2;
		for (; str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key1));
		if (s.find('$', 0) != s.npos)
		{
			s.erase(s.begin());
			if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
			else key2 = to_register[s];
			h = maxx(h, DH(key2));
			type = 1;
		}
		else
		{
			q = atoi(s.c_str());
			type = 2;
		} k += 2; s = "";
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		s += ':';
		jump = s;
	}
	bool EX()
	{
		if (type == 1) b = (r[key1] > r[key2]);
		else b = (r[key1] > q);
		return b;
	}
	int WB()
	{
		if (b == true) return label[s]; else return 0;
	}
};
class blt
{
private:
	int key1, key2, type, q;
	bool b;
	int h = 0;
	string s;
public:
	void DP(string str)
	{
		//	hazard = 1; 
		mark = 0;
		s = "";
		for (k = str.find('$', 0) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";   k += 2;
		for (; str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key1));
		if (s.find('$', 0) != s.npos)
		{
			s.erase(s.begin());
			if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
			else key2 = to_register[s];
			h = maxx(h, DH(key2));
			type = 1;
		}
		else
		{
			q = atoi(s.c_str());
			type = 2;
		} k += 2; s = "";
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		s += ':';
		jump = s;
	}
	bool EX()
	{
		if (type == 1) b = (r[key1] < r[key2]);
		else b = (r[key1] < q);
		return b;
	}
	int WB()
	{

		if (b == true) return label[s]; else return 0;
	}
};
class beqz
{
private:
	int key;
	string s;
	int h = 0;
	bool b;
public:
	void DP(string str)
	{
		//		hazard = 1; 
		mark = 0;
		s = "";
		for (k = str.find('$', 0) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
		else key = to_register[s]; s = "";   k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key));
		s += ':';
		jump = s;
	}
	bool EX()
	{
		b = (r[key] == 0);
		return b;
	}
	int WB()
	{
		if (b == true) return label[s]; else return 0;
	}
};
class bnez
{
private:
	int key;
	bool b;
	string s;
	int h = 0;
public:
	void DP(string str)
	{
		//	hazard = 1; 
		mark = 0;
		s = "";
		for (k = str.find('$', 0) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
		else key = to_register[s]; s = "";   k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key));
		s += ':';
		jump = s;
	}
	bool EX()
	{
		b = (r[key] != 0);
		return b;
	}
	int WB()
	{
		if (b == true) return label[s]; else return 0;
	}
};
class blez
{
private:
	int key;
	string s;
	int h = 0;
	bool b;
public:
	void DP(string str)
	{
		//		hazard = 1; 
		mark = 0;
		s = "";
		for (k = str.find('$', 0) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
		else key = to_register[s]; s = "";   k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key));
		s += ':';
		jump = s;
	}
	bool EX()
	{
		b = (r[key] <= 0);
		return b;
	}
	int WB()
	{
		if (b == true) return label[s]; else return 0;
	}
};
class bgez
{
private:
	int key;
	bool b;
	string s;
	int h = 0;
public:
	void DP(string str)
	{
		//	hazard = 1; 
		mark = 0;
		s = "";
		for (k = str.find('$', 0) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
		else key = to_register[s]; s = "";   k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key));
		s += ':';
		jump = s;
	}
	bool EX()
	{
		b = (r[key] >= 0);
		return b;
	}
	int WB()
	{
		if (b == true) return label[s]; else return 0;
	}
};
class bgtz
{
private:
	int key;
	string s;
	bool b;
	int h = 0;
public:
	void DP(string str)
	{
		//	hazard = 1; 
		mark = 0;
		s = "";
		for (k = str.find('$', 0) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
		else key = to_register[s]; s = "";   k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		s += ':';
		jump = s;
		h = maxx(h, DH(key));
		//	cout << key << ' ' << r[key] << endl;
	}
	bool EX()
	{
		b = (r[key] > 0);
		return b;
	}
	int WB()
	{
		if (b == true) return label[s]; else return 0;
	}
};
class bltz
{
private:
	int key;
	string s;
	bool b;
	int h = 0;
public:
	void DP(string str)
	{
		//	hazard = 1; 
		mark = 0;
		s = "";
		for (k = str.find('$', 0) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
		else key = to_register[s]; s = "";   k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key));
		s += ':';
		jump = s;
	}
	bool EX()
	{
		b = (r[key] < 0);
		return b;
	}
	int WB()
	{
		if (b == true) return label[s]; else return 0;
	}
};
class jj
{
private:
	string s;
public:
	void DP(string str)
	{
		hazard = 1;
		mark = 0;
		s = "";
		for (k = 2; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		s += ':';
	}
	void EX() {}
	int WB()
	{

		return label[s];
	}
};
class jr
{
private:
	int key, ans;
	int h = 0;
public:
	void DP(string str)
	{
		//cout<<"????"<<endl;
		hazard = 1; mark = 0;
		string s = "";
		for (k = str.find("jr", 0) + 4; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
		else key = to_register[s];
		h = maxx(h, DH(key));
	}
	void EX() { ans = r[key]; }
	int WB()
	{
		return ans;
	}
};
class jal
{
private:
	string s;
	int j;
public:
	void DP(string str, int m)
	{
		hazard = 1; mark = 0;
		s = "";
		for (k = 4; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		s += ':';
		j = m;
	}
	void EX() {}
	int WB()
	{
		r[31] = j;
		return label[s];
	}
};
class la
{
private:
	int key, ans, type, ke, p;
	int h = 0;
	string s;
public:
	void DP(string str)
	{
		s = "";
		for (k = str.find("la", 0) + 4; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
		else key = to_register[s]; s = "";
		for (k = str.find(",", 0) + 1; k < str.size(); ++k) if (str[k] != ' ') s += str[k];

		if (s.find("($", 0) == s.npos)
		{
			type = 1;
			s += ':';
			//ans = data_label[s];
		}
		else
		{
			string ss = "";
			for (k = 0; k < s.find("($", 0); ++k) if (s[k] != ' ') ss += s[k];
			p = atoi(ss.c_str()); ss = "";
			for (k = s.find("($", 0) + 2; k < s.size() - 1; ++k) if (s[k] != ' ') ss += s[k];
			if (ss[0] >= '0' && ss[0] <= '9') ke = atoi(ss.c_str());
			else ke = to_register[ss];
			//int t = r[ke] + p;
			type = 2;
			h = maxx(h, DH(ke));
			//ans = t;
		}
		h = maxx(h, LDH(key));
	}
	void EX()
	{
		if (type == 1) ans = data_label[s];
		else ans = r[ke] + p;
	}
	void WB()
	{
		f[key] = h;
		r[key] = ans;
	}
};
class lb
{
private:
	int key, ans, type, ke, p;
	int h = 0, rr;
	string s;
public:
	void DP(string str)
	{
		s = "";
		for (k = str.find("lb", 0) + 4; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
		else key = to_register[s]; s = "";
		for (k = str.find(",", 0) + 1; k < str.size(); ++k) if (str[k] != ' ') s += str[k];

		if (s.find("($", 0) == s.npos)
		{
			type = 1;
			s += ':';
			//ans = data_label[s];
		}
		else
		{
			string ss = "";
			for (k = 0; k < s.find("($", 0); ++k) if (s[k] != ' ') ss += s[k];
			p = atoi(ss.c_str()); ss = "";
			for (k = s.find("($", 0) + 2; k < s.size() - 1; ++k) if (s[k] != ' ') ss += s[k];
			if (ss[0] >= '0' && ss[0] <= '9') ke = atoi(ss.c_str());
			else ke = to_register[ss];
			//int t = r[ke] + p;
			type = 2;
			h = maxx(h, DH(ke));
			//ans = t;
		}
		h = maxx(h, LDH(key));
	}
	void EX()
	{
		if (type == 1) ans = data_label[s];
		else ans = r[ke] + p;
	}
	void MA()
	{
		rr = int(datar[ans].chr);
	}
	void WB()
	{
		f[key] = h;
		r[key] = rr;
	}
};
class lw
{
private:
	int key, ans, type, ke, p;
	int h = 0, rr;
	string s;
public:
	void DP(string str)
	{
		s = "";
		for (k = str.find("lw", 0) + 4; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
		else key = to_register[s]; s = "";
		for (k = str.find(",", 0) + 1; k < str.size(); ++k) if (str[k] != ' ') s += str[k];

		if (s.find("($", 0) == s.npos)
		{
			type = 1;
			s += ':';
			//ans = data_label[s];
		}
		else
		{
			string ss = "";
			for (k = 0; k < s.find("($", 0); ++k) if (s[k] != ' ') ss += s[k];
			p = atoi(ss.c_str()); ss = "";
			for (k = s.find("($", 0) + 2; k < s.size() - 1; ++k) if (s[k] != ' ') ss += s[k];
			if (ss[0] >= '0' && ss[0] <= '9') ke = atoi(ss.c_str());
			else ke = to_register[ss];
			//int t = r[ke] + p;
			type = 2;
			h = maxx(h, DH(ke));
			//ans = t;
		}
		h = maxx(h, LDH(key));
	}
	void EX()
	{
		if (type == 1) ans = data_label[s];
		else ans = r[ke] + p;
	}
	void MA()
	{
		rr = (datar[ans].num);
	}
	void WB()
	{
		f[key] = h;
		r[key] = rr;
		//	if (type == 2) cout << ke << ' ' << r[ke] << ' ' << p << ' '<<r[key]<<endl;
	}
};
class sb
{
private:
	int key, ans, type, ke, h = 0, rr, p;
	string s;
public:
	void DP(string str)
	{
		s = "";
		for (k = str.find("sb", 0) + 4; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
		else key = to_register[s]; s = "";
		for (k = str.find(",", 0) + 1; k < str.size(); ++k) if (str[k] != ' ') s += str[k];

		if (s.find("($", 0) == s.npos)
		{
			type = 1;
			s += ':';
			//ans = data_label[s];
		}
		else
		{
			string ss = "";
			for (k = 0; k < s.find("($", 0); ++k) if (s[k] != ' ') ss += s[k];
			p = atoi(ss.c_str()); ss = "";
			for (k = s.find("($", 0) + 2; k < s.size() - 1; ++k) if (s[k] != ' ') ss += s[k];
			if (ss[0] >= '0' && ss[0] <= '9') ke = atoi(ss.c_str());
			else ke = to_register[ss];
			//int t = r[ke] + p;
			type = 2;
			h = maxx(h, DH(ke));
			//ans = t;
		}
		h = maxx(h, DH(key));
	}
	void EX()
	{
		if (type == 1) ans = data_label[s];
		else ans = r[ke] + p;
	}
	void MA()
	{
		datar[ans].chr = char(r[key]);
	}
	void WB()
	{
	}
};
class sw
{
private:
	int key, ans, type, ke, h = 0, rr, p;
	string s;
public:
	void DP(string str)
	{
		s = "";
		for (k = str.find("sw", 0) + 4; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
		else key = to_register[s]; s = "";
		for (k = str.find(",", 0) + 1; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key));
		if (s.find("($", 0) == s.npos)
		{
			type = 1;
			s += ':';
			//ans = data_label[s];
		}
		else
		{
			string ss = "";
			for (k = 0; k < s.find("($", 0); ++k) if (s[k] != ' ') ss += s[k];
			p = atoi(ss.c_str()); ss = "";
			for (k = s.find("($", 0) + 2; k < s.size() - 1; ++k) if (s[k] != ' ') ss += s[k];
			if (ss[0] >= '0' && ss[0] <= '9') ke = atoi(ss.c_str());
			else ke = to_register[ss];
			//int t = r[ke] + p;
			type = 2;
			h = maxx(h, DH(ke));
			//ans = t;
		}
	}
	void EX()
	{
		if (type == 1) ans = data_label[s];
		else ans = r[ke] + p;
	}
	void MA()
	{
		datar[ans].num = r[key];
	}
	void WB()
	{
		//	if (type == 2) cout << ke << ' ' << r[ke] << ' ' << p <<' '<<key<<' '<<r[key]<< endl;
	}
};
class mov
{
private:
	int key1, key2, ans;
	int h = 0;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("move", 0) + 6; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";
		for (k = str.find('$', k) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		else key2 = to_register[s]; s = "";

		h = maxx(h, DH(key2));
		h = maxx(h, LDH(key1));
	}
	void EX() { ans = r[key2]; }
	void WB()
	{
		f[key1] = h;
		r[key1] = ans;
	}
};
class mfhi
{
private:
	int key, ans;
	int h = 0;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("mfhi", 0) + 6; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
		else key = to_register[s];

		h = maxx(h, DH(32));
		h = maxx(h, LDH(key));
	}
	void EX() { ans = hi; }
	void WB()
	{
		f[key] = h;
		r[key] = ans;
	}
};
class mflo
{
private:
	int key, ans;
	int h = 0;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("mflo", 0) + 6; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
		else key = to_register[s];

		h = maxx(h, DH(33));
		h = maxx(h, LDH(key));
	}
	void EX() { ans = lo; }
	void WB()
	{
		f[key] = h;
		r[key] = ans;
	}
};
class syscall
{
private:
	int v0, a0;
	int h = 0;
	int abs(int x)
	{
		if (x >= 0) return x;
		else return -x;
	}
public:
	void DP()
	{
		h = maxx(h, DH(2));
		h = maxx(h, DH(4));
		if (r[2] == 5 || r[2] == 9) h = maxx(h, LDH(2));
	}
	void EX() {}
	void MA() {}
	int WB()
	{

		if (r[2] == 5 || r[2] == 9) f[2] = h;
		//cout << r[2] << ' ' << r[4] << endl;
		if (r[2] == 1) printf("%d",r[4]); else
			if (r[2] == 4) {
				int j = r[4];
				while (datar[j].chr != '\0') {printf("%c", datar[j].chr); ++j; }
			}
			else
				if (r[2] == 5) {
					//fscanf(stdin2, "%d", &r[2]);
					cin >> r[2];
				}
				else
					if (r[2] == 8)
					{
						char chr[1000];
						//fscanf(stdin2, "%s", &chr);
						cin >> chr;
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
						if (r[2] == 10) return 0; else
							if (r[2] == 17) return abs(r[4]); else
								if (r[2] == 9)
								{
									r[2] = datanum;
									datar[datanum].mark = 6;
									datar[datanum].size = r[4];
									datar[datanum].current_size = 0;
									datanum += r[4];
								}
		return -1;
	}
};
ofstream fout("array_test1-mahaojun.out");
bool try_tbp(int x)
{
	if (all[x].size() <= 3) return false;
	else
	{
		int z = all[x].size();
		int y = (all[x][z - 4] * 8 + all[x][z - 3] * 4 + all[x][z - 2] * 2 + all[x][z - 1]);
		if (tbp[x][y] >= 3 || (tbp[x][y] == 2 && (rand() % 2 == 0))) return true;
		else return false;
	}
}
int main()
{
	srand(time(0));
	r[29] = N;
	ready();
	for (int ii = 0; ii < 120; ++ii) 
	for (int jj = 0;jj < 16;++jj)
	tbp[ii][jj] = 2;
	FILE *stdin1 = fopen("heapsort-5100379110-daibo.s", "r");
	//	FILE *stdin2 = fopen("array_test1-mahaojun.in", "r");
	char chr[100];
	while (fscanf(stdin1, "%[^\n]", &chr) != EOF)
	{
		++i;
		string s = chr;
		while (s[0] == '\t' || s[0] == ' ') s.erase(s.begin());
		str.push_back(s);
		//cout<<i <<' '<<s<<endl;
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
	int status[5] = { 0 };
	string s[5];
	int name[5] = { 0 };

	add adder[5];
	addu adduer[5];
	sub suber[5];
	subu subuer[5];
	mul muler[5];
	mulu muluer[5];
	divv divver[5];
	divvu divvuer[5];
	xxor xxorer[5];
	xxoru xxoruer[5];
	neg neger[5];
	negu neguer[5];
	rem remer[5];
	remu remuer[5];
	li lier[5];
	seq seqer[5];
	sge sgeer[5];
	sgt sgter[5];
	sle sleer[5];
	slt slter[5];
	sne sneer[5];
	bb bber[5];
	beq beqer[5];
	bne bneer[5];
	bge bgeer[5];
	blt blter[5];
	ble bleer[5];
	bgt bgter[5];
	beqz beqzer[5];
	bnez bnezer[5];
	blez blezer[5];
	bgez bgezer[5];
	bgtz bgtzer[5];
	bltz bltzer[5];
	jj jjer[5];
	jr jrer[5];
	jal jaler[5];
	la laer[5];
	lb lber[5];
	lw lwer[5];
	sb sber[5];
	sw swer[5];
	mov mover[5];
	mfhi mfhier[5];
	mflo mfloer[5];
	syscall syscaller[5];
	int i = 5, i0, t0, laststone = 0, j0[5] = { 0 }, ma[5] = { 0 }, mar = 0;
	string jum[5];
	while (true)
	{
		--i;
		if (i < 0) i += 5;
		if (mar == 1)
		{
			for (int ii = 0; ii <= 4; ++ii) { status[ii] = 0; s[ii] = ""; ma[ii] = 0; j0[ii] = 0; name[ii] = 0; ha[ii] = 0; jum[ii] = ""; }
			mar = 0;
		}
		if (hazard == 1 || hazard == 2)
		{
			bool b = true;
			for (int ii = 0; ii <= 4; ++ii) if (status[ii] == 1) b = false;
			if (b == true)
			{
				i = 4;
				for (int ii = 0; ii <= 4; ++ii) {
					status[ii] = 0; s[ii] = ""; name[ii] = 0;
				}
				for (int ii = 0; ii <= 33; ++ii) f[ii] = 0;
				if (hazard == 1)
				{
					if (laststone == 1) ++j;
					laststone = 0;
				}
				else --j;
				hazard = 0;
			}
		}
		else
		{
			++j;

		}
		if (j == 563)
			j = 563;

		for (int k = 4; k >= 0; --k)
		{
			int t = (k + i) % 5;

			if (k == 0)
			{
				if (status[t] != 0 || hazard != 0) continue;
				//if (j > str.size() - 1) continue;
				//	cout << j << ' ' << hazard << endl;
				while (label[str[j]] != 0)
					++j;
				s[t] = str[j];
				string ss = "";
				for (int k = 0; k < s[t].size() && s[t][k] != ' '; ++k) ss += s[t][k];
				name[t] = to_int[ss];
				status[t] = 1;
				//cout << j << '\t' << str[j] << ' '<<r[8]<<' '<<r[9]<<' '<<r[10]<<' '<<r[11]<<' '<<r[12]<<endl;
				//for (int k = 0; k < 32; ++k) fout << k << '\t'; fout << endl;
				//for (int k = 0; k < 32; ++k) fout << r[k] << '\t'; fout << endl;
				//	cout << status[0] << ' ' << status[1] << ' ' << status[2] << ' 'syscall << status[3] << ' ' << status[4] << endl;
			}
			else
				if (k == 1)
				{
					if (status[t] <= 0) continue;
					if (hazard != 0) continue;
					switch (name[t])
					{
					case 1: adder[t].DP(s[t]);  break;
					case 2: adduer[t].DP(s[t]);  break;
					case 3: suber[t].DP(s[t]); break;
					case 4: subuer[t].DP(s[t]);  break;
					case 5: muler[t].DP(s[t]);  break;
					case 6: muluer[t].DP(s[t]);  break;
					case 7: divver[t].DP(s[t]);  break;
					case 8: divvuer[t].DP(s[t]);  break;
					case 9: xxorer[t].DP(s[t]);  break;
					case 10: xxoruer[t].DP(s[t]);  break;
					case 11: neger[t].DP(s[t]);  break;
					case 12: neguer[t].DP(s[t]);  break;
					case 13: remer[t].DP(s[t]);  break;
					case 14: remuer[t].DP(s[t]);  break;
					case 15: lier[t].DP(s[t]);  break;
					case 16: seqer[t].DP(s[t]);  break;
					case 17: sgeer[t].DP(s[t]);  break;
					case 18: sgter[t].DP(s[t]);  break;
					case 19: sleer[t].DP(s[t]);  break;
					case 20: slter[t].DP(s[t]);  break;
					case 21: sneer[t].DP(s[t]);  break;
					case 22: bber[t].DP(s[t]);  break;
					case 23: ha[t] = 3; beqer[t].DP(s[t]);  break;
					case 24: ha[t] = 3; bneer[t].DP(s[t]);  break;
					case 25: ha[t] = 3; bgeer[t].DP(s[t]);  break;
					case 26: ha[t] = 3; bleer[t].DP(s[t]);  break;
					case 27: ha[t] = 3; bgter[t].DP(s[t]);  break;
					case 28: ha[t] = 3; blter[t].DP(s[t]);  break;
					case 29: ha[t] = 3; beqzer[t].DP(s[t]);  break;
					case 30: ha[t] = 3; bnezer[t].DP(s[t]);  break;
					case 31: ha[t] = 3; bgezer[t].DP(s[t]);  break;
					case 32: ha[t] = 3; blezer[t].DP(s[t]);  break;
					case 33: ha[t] = 3; bgtzer[t].DP(s[t]);  break;
					case 34: ha[t] = 3; bltzer[t].DP(s[t]);  break;
					case 35: jjer[t].DP(s[t]);  break;
					case 36: jrer[t].DP(s[t]);  break;
					case 37: jaler[t].DP(s[t], j - 1);  break;
					case 38: laer[t].DP(s[t]);  break;
					case 39: lber[t].DP(s[t]);  break;
					case 40: lwer[t].DP(s[t]);  break;
					case 41: sber[t].DP(s[t]);  break;
					case 42: swer[t].DP(s[t]);  break;
					case 43: mover[t].DP(s[t]);  break;
					case 44: mfhier[t].DP(s[t]);  break;
					case 45: mfloer[t].DP(s[t]);  break;
					case 46: syscaller[t].DP();   break;
					}
					if (hazard == 2)
					{
						i0 = i;
						t0 = t;
						status[t] = -1;
						status[(t + 4) % 5] = -1;
						status[(t + 3) % 5] = -1;
						ha[t] = 0;
					}
					else
						if (hazard == 1)
						{
							//	cout << "!!!!" << j << endl;
							i0 = i;
							t0 = t;
							status[(t + 4) % 5] = -1;
							status[(t + 3) % 5] = -1;
							ha[t] = 0;
						}
						else
							if (ha[t] == 3)
							{
								++snum;
								jum[t] = jump;
								if (try_tbp(name[t]))
								{
									ma[t] = 1;
									j0[t] = j;
									j = label[jum[t]];
								}
								else
								{
									ma[t] = 0;
									j0[t] = j;
								}
							}
				}
				else
					if (k == 2)
					{
						bool tmp;
						if (status[t] <= 0) continue;
						switch (name[t])
						{
						case 1: adder[t].EX(); break;
						case 2: adduer[t].EX();  break;
						case 3: suber[t].EX();  break;
						case 4: subuer[t].EX();  break;
						case 5: muler[t].EX();  break;
						case 6: muluer[t].EX();  break;
						case 7: divver[t].EX();  break;
						case 8: divvuer[t].EX();  break;
						case 9: xxorer[t].EX();  break;
						case 10: xxoruer[t].EX();  break;
						case 11: neger[t].EX();  break;
						case 12: neguer[t].EX();  break;
						case 13: remer[t].EX();  break;
						case 14: remuer[t].EX();  break;
						case 15: lier[t].EX();  break;
						case 16: seqer[t].EX();  break;
						case 17: sgeer[t].EX();  break;
						case 18: sgter[t].EX();  break;
						case 19: sleer[t].EX();  break;
						case 20: slter[t].EX();  break;
						case 21: sneer[t].EX();  break;
						case 22: bber[t].EX();  break;
						case 23: tmp = beqer[t].EX();  break;
						case 24: tmp = bneer[t].EX();  break;
						case 25: tmp = bgeer[t].EX();  break;
						case 26: tmp = bleer[t].EX();  break;
						case 27: tmp = bgter[t].EX();  break;
						case 28: tmp = blter[t].EX();  break;
						case 29: tmp = beqzer[t].EX();  break;
						case 30: tmp = bnezer[t].EX();  break;
						case 31: tmp = bgezer[t].EX();  break;
						case 32: tmp = blezer[t].EX();  break;
						case 33: tmp = bgtzer[t].EX();  break;
						case 34: tmp = bltzer[t].EX();  break;
						case 35: jjer[t].EX();  break;
						case 36: jrer[t].EX();  break;
						case 37: jaler[t].EX();  break;
						case 38: laer[t].EX();  break;
						case 39: lber[t].EX();  break;
						case 40: lwer[t].EX();  break;
						case 41: sber[t].EX();  break;
						case 42: swer[t].EX();  break;
						case 43: mover[t].EX();  break;
						case 44: mfhier[t].EX();  break;
						case 45: mfloer[t].EX();  break;
						case 46: syscaller[t].EX(); break;
						}
						if (ha[t] == 3)
						{
							all[name[t]].push_back(tmp);
							if (ma[t] == 1)
							{
								if (tmp == true) { ++cnum; inc(name[t]); }
								else
								{
									mar = 1;
									j = j0[t] - 1;
									dec(name[t]);
									break;
								}
							}
							else
							{
								if (tmp == false) { ++cnum; dec(name[t]); }
								else
								{
									mar = 1;
									j = label[jum[t]];
									inc(name[t]);
									break;
								}
							}
						}
					}
					else
						if (k == 3)
						{
							if (status[t] <= 0) continue;
							switch (name[t])
							{
							case 39: lber[t].MA();  break;
							case 40: lwer[t].MA();  break;
							case 41: sber[t].MA();  break;
							case 42: swer[t].MA();  break;
							case 46: syscaller[t].MA();  break;
							}
						}
			if (k == 4)
			{
				if (status[t] <= 0) continue;
				int tmp = 0, mark = 0;
				switch (name[t])
				{
				case 1: adder[t].WB(); status[t] = 0;  break;
				case 2: adduer[t].WB(); status[t] = 0;  break;
				case 3: suber[t].WB(); status[t] = 0;  break;
				case 4: subuer[t].WB(); status[t] = 0;  break;
				case 5: muler[t].WB(); status[t] = 0;  break;
				case 6: muluer[t].WB(); status[t] = 0;  break;
				case 7: divver[t].WB(); status[t] = 0;  break;
				case 8: divvuer[t].WB(); status[t] = 0;  break;
				case 9: xxorer[t].WB(); status[t] = 0;  break;
				case 10: xxoruer[t].WB(); status[t] = 0;  break;
				case 11: neger[t].WB(); status[t] = 0;  break;
				case 12: neguer[t].WB(); status[t] = 0;  break;
				case 13: remer[t].WB(); status[t] = 0;  break;
				case 14: remuer[t].WB(); status[t] = 0;  break;
				case 15: lier[t].WB(); status[t] = 0;  break;
				case 16: seqer[t].WB(); status[t] = 0;  break;
				case 17: sgeer[t].WB(); status[t] = 0;  break;
				case 18: sgter[t].WB(); status[t] = 0;  break;
				case 19: sleer[t].WB(); status[t] = 0;  break;
				case 20: slter[t].WB(); status[t] = 0;  break;
				case 21: sneer[t].WB(); status[t] = 0;  break;
				case 22: tmp = bber[t].WB(); status[t] = 0;   break;
				case 23: tmp = beqer[t].WB(); status[t] = 0;  break;
				case 24: tmp = bneer[t].WB(); status[t] = 0;  break;
				case 25: tmp = bgeer[t].WB(); status[t] = 0;  break;
				case 26: tmp = bleer[t].WB(); status[t] = 0;  break;
				case 27: tmp = bgter[t].WB(); status[t] = 0;  break;
				case 28: tmp = blter[t].WB(); status[t] = 0;  break;
				case 29: tmp = beqzer[t].WB(); status[t] = 0;  break;
				case 30: tmp = bnezer[t].WB(); status[t] = 0;  break;
				case 31: tmp = bgezer[t].WB(); status[t] = 0;  break;
				case 32: tmp = blezer[t].WB(); status[t] = 0;  break;
				case 33: tmp = bgtzer[t].WB(); status[t] = 0;  break;
				case 34: tmp = bltzer[t].WB(); status[t] = 0;  break;
				case 35: tmp = jjer[t].WB(); status[t] = 0;  break;
				case 36: tmp = jrer[t].WB(); status[t] = 0;  break;
				case 37: tmp = jaler[t].WB(); status[t] = 0;  break;
				case 38: laer[t].WB(); status[t] = 0;  break;
				case 39: lber[t].WB(); status[t] = 0;  break;
				case 40: lwer[t].WB(); status[t] = 0;  break;
				case 41: sber[t].WB(); status[t] = 0;  break;
				case 42: swer[t].WB(); status[t] = 0;  break;
				case 43: mover[t].WB(); status[t] = 0;  break;
				case 44: mfhier[t].WB(); status[t] = 0;  break;
				case 45: mfloer[t].WB(); status[t] = 0;  break;
				case 46: mark = syscaller[t].WB(); status[t] = 0;  break;
				}
				if (ha[t] == 3) ha[t] = 0; else
					if (tmp != 0)
					{
						laststone = 1; j = tmp;
					}

				if (name[t] == 46 && mark != -1)
				{
					cout << cnum << ' ' << snum << ' ' << (double(cnum) / snum) * 100 << "%" << endl;
					//	for (int ii = 22; ii <= 37;++ii)
					//	{
					//		for (int jj = 0;jj <= 3;++jj) cout<<tbp[ii][jj]<<' ';
					//		cout<<endl;
					//	}
					return mark;
				}
			}
		}
	}
}
