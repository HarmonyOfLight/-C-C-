#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
using namespace std;
string key_word[32]={
	"auto","break","case","char","const","continue","default","double",
	"do","else","enum","extern","float","for","goto","if","int","long",
	"register","return","short","signed","sizeof","static","struct",
	"switch","typedef","union","unsigned","void","volatile","while"};
int keyword_num=0;
int switch_num=0;
int flag=0;
int switch_case[100]={0};
int ifelse_num=0;
int if_elseif_else_num=0;
int stack[500]={0};
int top=-1;
int main ()
{
	int level;
	string file_name;
	cout<<"输入文件路径:";				
	cin>>file_name;						
	//输入文件路径C:\\Users\\86199\\Desktop\\keyword.txt
	cout<<"输入完成等级:";
	cin>>level;
	ifstream myfile(file_name.c_str());	//打开文件 
	string temp;
	int judge1(string str,string str1);
	int judge2(char str);
	void level_1(string word1);		//关键字数量 
	void level_2(string word2);		//switch case数量 
	void level_34(string word3);		//if-else 数量 
	int line=0;
	while(getline(myfile,temp))		//逐行读取 
	{
		istringstream is(temp);	
		string s;
		if(level>=3)
			level_34(temp);
		while(is>>s)				//去除空格,例如:   a = b   分三次读取为a,b,c 
		{
		if(level>=1)
			level_1(s);
		if(level>=2)
			level_2(s);
		}
		line++;
	}
	if(level>=1)
		cout<<"total num: "<<keyword_num<<endl;
	if(level>=2)
	{
		cout<<"switch num: "<<switch_num<<endl;
		cout<<"case num: ";
		for(int a=1;a<=switch_num;a++)
			cout<<switch_case[a]<<" ";
		cout<<endl;
	}
	if(level>=3)
	{
		cout<<"if-else num: "<<ifelse_num<<endl;
	}
	if(level>=4)
	{
		cout<<"if-elseif-else num: "<<if_elseif_else_num;
	}
}
int judge1(string str,string str1)	//在str中寻找str1 
{
	int judge2(char str);
	int loc=str.find(str1,0);
	int len=str1.length();
	if(loc!=string::npos)
	{
		if(loc==0)
		{
			if(judge2(str[loc+len])==0)
				return 1;
			else 
				return 0;
		}
		else
		{
			if(judge2(str[loc-1])==0&&judge2(str[loc+len])==0)
				return 1;
			else
				return 0;
		}
	}
	return 0;
}
int judge2(char str)
{
	if(str>='a'&&str<='z')
		return 1;
	if(str>='A'&&str<='Z')
		return 1;
	return 0;
}
void level_1(string word1)		//关键字数量 
{
	for(int a=0;a<32;a++)			//找到关键词 
	{
		if(judge1(word1,key_word[a])==1)
		{
			keyword_num++;
			break;
		}
	}
}	
void level_2(string word2)		//switch case数量 
{
	if(flag)
	{
		if(judge1(word2,"case")==1)
		{
			switch_case[switch_num]++;
		}
	}	
	if(judge1(word2,"switch")==1)		//找到switch
	{
		switch_num++;
		flag=1;
	}
}
void level_34(string word3)		//if-else 数量 
{
	if(judge1(word3,"else if"))
	{
		top++;
		stack[top]=2;
	}
	else
	{
		if(judge1(word3,"if"))
		{
			top++;
			stack[top]=1;
		}
		else
		{
			if(judge1(word3,"else"))
			{
				if(stack[top]==1)
				{
					ifelse_num++;
					top--;
				}
				else	
				{
					if(stack[top]==2)
					{
						if_elseif_else_num++;
						top--;
					}
				}
			}
		}
	}
}
