
#ifndef TCharBuffH
#define TCharBuffH

#define CHARBUFF_MIN_FULL_SIZE 64

#ifdef _WIN64
	#define ALIGN_RANGE 8
#else
	#define ALIGN_RANGE 4
#endif

class TCharBuff
{
	private:
		unsigned int curSize;
		unsigned int curPosition;
		unsigned int fullSize;
		//bool isFromDelete;
		void __fastcall resize(unsigned int newSize);
		void __fastcall deleteData();
		void __fastcall allignSize(unsigned int &size);
	public:
		void* data;
		__fastcall TCharBuff(unsigned int size = 0);
		__fastcall ~TCharBuff();

		void __fastcall setSize(unsigned int size);
		unsigned int __fastcall getSize();
		void __fastcall setPosition(unsigned int pos);
		unsigned int __fastcall getPosition();
		void __fastcall write(void* source, unsigned int count);
		unsigned int __fastcall read(void* dest, unsigned int count);
		void* __fastcall getPointerFromCurPos();
		void __fastcall clearData();
		unsigned int __fastcall getSizeToEnd();
        void __fastcall trimFromStart();

};

#endif
