#ifndef DEBUGENGINE_H
#define DEBUGENGINE_H

class DebugEngine
{
	public:
			DebugEngine()
			{
				cout<<"------------------Engine Logs Start-------------------"<<endl;
				cout<<endl;
			}

			virtual ~DebugEngine()
			{
				cout<<endl;
				cout<<"------------------Engine Logs End-------------------"<<endl;
			}

			void Log()
			{
				cout<<endl;
			}

			void Log(string str)
			{
				cout<<str<<endl;
			}

			void Log(char c)
			{
				cout<<c;
			}
};

#endif