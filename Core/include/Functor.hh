//
// C++ Interface: Functor
//
// Description: Implements a Functor class
//
//
// Author:  <alex@asmodehn.net>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//

#ifndef FUNCTOR_HH
#define FUNCTOR_HH



namespace RAGE
{

	//Generic functor implementing any return type, with no arguments
	template <typename returnType = void>
	class TFunctor
	{
		public:
			virtual returnType operator()(void) = 0 ; //operator used for calling the function
			virtual returnType call(void) = 0 ;//specific call function
	};

	template <class TClass,typename returnType = void>
	class TSpecificFunctor : public TFunctor<returnType>
	{
		private:
			returnType (TClass::*_ptfunc) (void); //member function pointer
			TClass *_ptobj;//instance pointer
		public:
			TSpecificFunctor(TClass* ptobj, returnType (TClass::*ptfunc) (void))
			{
				_ptobj = ptobj;
				_ptfunc = ptfunc;
			}
	
			virtual returnType operator()(void)
			{
				return (_ptobj->*_ptfunc)();
			}
			
			virtual returnType call(void)
			{
				return (_ptobj->*_ptfunc)();
			}
				
	};

	
	//Generic functor implementing any return type, with a void* as arguments
	template <typename returnType = void, typename arg1Type = void* >
	class TFunctor1
	{
		public:
			virtual returnType operator()(arg1Type arg) = 0 ; //operator used for calling the function
			virtual returnType call(arg1Type arg) = 0 ;//specific call function
	};

	template <class TClass,typename returnType = void, typename arg1Type = void *>
			class TSpecificFunctor1 : public TFunctor1<returnType,arg1Type>
	{
		private:
			returnType (TClass::*_ptfunc) (arg1Type arg); //member function pointer
			TClass *_ptobj;//instance pointer

		public:
			TSpecificFunctor1(TClass* ptobj, returnType (TClass::*ptfunc) (arg1Type arg))
			{
				_ptobj = ptobj;
				_ptfunc = ptfunc;
			}
			
			virtual returnType operator()(arg1Type arg)
			{
				return (_ptobj->*_ptfunc)(arg);
			}
			
			virtual returnType call(arg1Type arg)
			{
				return (_ptobj->*_ptfunc)(arg);
			}
				
	};

	//Generic functor implementing any return type, with a void* as arguments
	template <typename returnType = void,typename arg1Type = void*, typename arg2Type = void*>
	class TFunctor2
	{
		public:
			virtual returnType operator()(arg1Type,arg2Type) = 0 ; //operator used for calling the function
			virtual returnType call(arg1Type,arg2Type) = 0 ;//specific call function
			virtual ~TFunctor2() {}
	};

	template <class TClass,typename returnType, typename arg1Type = void*, typename arg2Type = void *>
			class TSpecificFunctor2 : public TFunctor2<returnType,arg1Type,arg2Type>
			{
				private:
					returnType (TClass::*_ptfunc) (arg1Type arg1,arg2Type arg2); //member function pointer
					TClass *_ptobj;//instance pointer

				public:
					TSpecificFunctor2(TClass* ptobj, returnType (TClass::*ptfunc) (arg1Type ,arg2Type))
					{
						_ptobj = ptobj;
						_ptfunc = ptfunc;
					}
			
					virtual returnType operator()(arg1Type arg1,arg2Type arg2)
					{
						return (_ptobj->*_ptfunc)(arg1,arg2);
					}
			
					virtual returnType call(arg1Type arg1,arg2Type arg2)
					{
						return (_ptobj->*_ptfunc)(arg1,arg2);
					}
				
			};


		//Generic functor implementing any return type, with a void* as arguments
			template <typename returnType = void,typename arg1Type = void*, typename arg2Type = void*, typename arg3Type = void*>
					class TFunctor3
					{
						public:
							virtual returnType operator()(arg1Type,arg2Type,arg3Type) = 0 ; //operator used for calling the function
							virtual returnType call(arg1Type,arg2Type,arg3Type) = 0 ;//specific call function
					};

					template <class TClass,typename returnType, typename arg1Type = void*, typename arg2Type = void *, typename arg3Type = void *>
							class TSpecificFunctor3 : public TFunctor3<returnType,arg1Type,arg2Type,arg3Type>
							{
								private:
									returnType (TClass::*_ptfunc) (arg1Type arg1,arg2Type arg2,arg3Type arg3); //member function pointer
									TClass *_ptobj;//instance pointer

								public:
									TSpecificFunctor3(TClass* ptobj, returnType (TClass::*ptfunc) (arg1Type ,arg2Type,arg3Type))
									{
										_ptobj = ptobj;
										_ptfunc = ptfunc;
									}
			
									virtual returnType operator()(arg1Type arg1,arg2Type arg2,arg3Type arg3)
									{
										return (_ptobj->*_ptfunc)(arg1,arg2,arg3);
									}
			
									virtual returnType call(arg1Type arg1,arg2Type arg2,arg3Type arg3)
									{
										return (_ptobj->*_ptfunc)(arg1,arg2,arg3);
									}
				
							};



}

#endif
