#ifndef ELIST_H
#define ELIST_H

template <class T>
class ENode
{
	public:
			int Id;
			T *Data;
			ENode *NextPtr;
			ENode *PrevPtr;
	public:
			ENode() : Id(0), Data(0), NextPtr(NULL), PrevPtr(NULL)
			{

			}

			ENode(int id, T *data) : Id(id), Data(data), NextPtr(NULL), PrevPtr(NULL)
			{

			}

			~ENode()
			{
				cout<<"Destroying Node : "<<this->Id<<endl;	

				Id = 0;
				
				if(Data != NULL)
				{
					SAFE_DELETE(Data);
				}

				NextPtr = NULL;
				PrevPtr = NULL;				
			}			
};

template <class T>
class EList
{
	private:
			ENode<T> *HeadPtr;
	public:
			int Count;
	public:
			EList() : HeadPtr(NULL), Count(0)
			{

			}

			~EList()
			{
				this->Clear();
				Count = 0;
			}

			ENode<T>* GetNode(int index)
			{
				ENode<T> *iter = HeadPtr;
				int i = 0;

				while(iter != NULL)
				{
					if(index < 0 || index >= Count)
					{
						cout<<"Wrong Index"<<endl;
						break;
					}

					if(i == index)
					{
						return iter;
					}

					iter = iter->NextPtr;
					i++;
				}

				cout<<"The node does not exist"<<endl;
				return NULL;
			}

			T* GetNodeData(int index)
			{
				ENode<T> *iter = HeadPtr;
				int i = 0;

				while(iter != NULL)
				{
					if(index < 0 || index >= Count)
					{
						cout<<"Wrong index"<<endl;
						break;
					}

					if(i == index)
					{
						return iter->Data;
					}

					iter = iter->NextPtr;
					i++;
				}

				cout<<"The node does not exist"<<endl;
				return NULL;
			}

			bool Find(T *itemData)
			{
				ENode<T> *iter = HeadPtr;
				
				while(iter != NULL)
				{
					if(iter->Data == itemData)
					{
						cout<<"Item Found"<<endl;
						return true;
					}

					iter = iter->NextPtr;
				}

			//	cout<<"The node does not exist"<<endl;
				return false;
			}

			void Add(T *data) 
			{
				ENode<T> *newItem = new ENode<T>(0, data);

				if(HeadPtr == NULL)
				{
					HeadPtr = newItem;
				}
				else
				{
					ENode<T> *iter = HeadPtr;

					while(iter->NextPtr != NULL)
					{
						iter = iter->NextPtr;
					}

					iter->NextPtr = newItem;
					newItem->PrevPtr = iter;
				}

				newItem->Id = Count;
				Count++;
			}

			void AddReference(ENode<T> *item)
			{
				ENode<T> *newItem = item;

				if(HeadPtr == NULL)
				{
					HeadPtr = newItem;
				}
				else
				{
					ENode<T> *iter = HeadPtr;

					while(iter->NextPtr != NULL)
					{
						iter = iter->NextPtr;
					}

					iter->NextPtr = newItem;
					newItem->PrevPtr = iter;
				}

				newItem->Id = Count;
				Count++;
			}

			void Remove(ENode<T> *item)
			{
				if(item == NULL)
				{
					return;
				}

				ENode<T> *nextPtr = NULL;
				ENode<T> *prevPtr = NULL;

				if(item->NextPtr != NULL)
				{
					nextPtr = item->NextPtr;
				}

				if(item->PrevPtr != NULL)
				{
					prevPtr = item->PrevPtr;
				}

				if(nextPtr != NULL && prevPtr != NULL)
				{
					nextPtr->PrevPtr = prevPtr;
					prevPtr->NextPtr = nextPtr;
				}
				else
				if(nextPtr == NULL && prevPtr != NULL)
				{
					prevPtr->NextPtr = NULL;
				}
				else
				if(nextPtr != NULL && prevPtr == NULL)
				{
					nextPtr->PrevPtr = NULL;
				}

				SAFE_DELETE(item);
				Count--;
			}

			void Remove(T *itemData)
			{
				if(itemData == NULL)
				{
					return;
				}

				ENode<T> *iter = HeadPtr;

				while(iter != NULL)
				{
					if(iter->Data == itemData)
					{
						break;
					}

					iter = iter->NextPtr;
				}

				if(iter == NULL)
				{
					cout<<"Data does not match any of the list nodes"<<endl;
					return;
				}

				ENode<T> *item = iter;

				ENode<T> *nextPtr = NULL;
				ENode<T> *prevPtr = NULL;

				if(item->NextPtr != NULL)
				{
					nextPtr = item->NextPtr;
				}

				if(item->PrevPtr != NULL)
				{
					prevPtr = item->PrevPtr;
				}

				if(nextPtr != NULL && prevPtr != NULL)
				{
					nextPtr->PrevPtr = prevPtr;
					prevPtr->NextPtr = nextPtr;
				}
				else
				if(nextPtr == NULL && prevPtr != NULL)
				{
					prevPtr->NextPtr = NULL;
				}
				else
				if(nextPtr != NULL && prevPtr == NULL)
				{
					nextPtr->PrevPtr = NULL;
				}

				SAFE_DELETE(item);
				Count--;
			}

			void RemoveReference(ENode<T> *item)
			{
				if(item == NULL)
				{
					return;
				}

				ENode<T> *nextPtr = NULL;
				ENode<T> *prevPtr = NULL;

				if(item->NextPtr != NULL)
				{
					nextPtr = item->NextPtr;
				}

				if(item->PrevPtr != NULL)
				{
					prevPtr = item->PrevPtr;
				}

				if(nextPtr != NULL && prevPtr != NULL)
				{
					nextPtr->PrevPtr = prevPtr;
					prevPtr->NextPtr = nextPtr;
				}
				else
				if(nextPtr == NULL && prevPtr != NULL)
				{
					prevPtr->NextPtr = NULL;
				}
				else
				if(nextPtr != NULL && prevPtr == NULL)
				{
					nextPtr->PrevPtr = NULL;
				}

				item->NextPtr = NULL;
				item->PrevPtr = NULL;

				cout<<"Removing reference"<<endl;
				Count--;
			}

			void Clear() 
			{
				ENode<T> *iter = HeadPtr;

				while(iter != NULL)
				{
					if(Count != 0)
					{
						ENode<T> *delPtr = iter;
						iter = iter->NextPtr;
						SAFE_DELETE(delPtr);
						Count--;
					}
					else
					{
						break;
					}
				}

				HeadPtr = NULL;
			}
			
			void Print() 
			{
				ENode<T> *iter = HeadPtr;

				while(iter != NULL)
				{
					cout<<iter->Id<<endl;
					iter = iter->NextPtr;
				}
			}
};

#endif 