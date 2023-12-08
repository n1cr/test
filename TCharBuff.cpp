//---------------------------------------------------------------------------

#pragma hdrstop
#include "TCharBuff.h"

#pragma package(smart_init)

__fastcall TCharBuff::TCharBuff(unsigned int size)//default = 0
{
	curSize = 0;
	curPosition = 0;
	fullSize = 0;
	data = NULL;
	resize(size);
}

__fastcall TCharBuff::~TCharBuff()
{
	deleteData();
}

void __fastcall TCharBuff::deleteData()
{
	if (data !=NULL)
	{
//		char* buff = (char*)data;
//        delete []buff;
//		delete []data;
		free(data);
		//HeapFree(GetProcessHeap(), 0, data);
		data = NULL;
		curSize = 0;
		curPosition = 0;
        fullSize = 0;
	}
}


void __fastcall TCharBuff::clearData()
{
	if (data !=NULL)
	{
		curSize = 0;
		curPosition = 0;
	}
}

void __fastcall TCharBuff::allignSize(unsigned int &size)
{
	unsigned int result = size % ALIGN_RANGE;
	if (result != 0)
		size = size + ALIGN_RANGE - result;

}

void __fastcall TCharBuff::resize(unsigned int newSize)
{
	if (data == NULL)
	{
		fullSize = newSize + CHARBUFF_MIN_FULL_SIZE;
		allignSize(fullSize);
//		data = new char[fullSize];
		data = malloc(fullSize);//HeapAlloc(GetProcessHeap(), 0, fullSize); //
//		if (data == NULL)
//		{
//            data = malloc(fullSize);
//            int f = 0;
//		}
		curPosition = 0;
	}
	else
	{
		if (newSize <= fullSize)
		{
			if (curPosition > newSize)
			{
                curPosition = newSize;
			}
		}
		else
		{
//			char* newData;
			unsigned int oldPos = curPosition;
			unsigned int minSize;// = std::min<int>(curSize, newSize);
			if (curSize <= newSize)
			{
				minSize = curSize;
			}
			else
			{
				minSize = newSize;
			}
//			fullSize = newSize + CHARBUFF_MIN_FULL_SIZE;
//			newData = new char[fullSize];
//			Move(data,newData,minSize);
//			//memcpy(newData, data, minSize);
//			deleteData();
			fullSize = newSize + CHARBUFF_MIN_FULL_SIZE;
			allignSize(fullSize);
			data = realloc(data, fullSize);//HeapReAlloc(GetProcessHeap(), 0,data, fullSize); //
//			data = newData;
			if (oldPos > newSize)
			{
				curPosition = newSize;
			}
			else
			{
				curPosition = oldPos;
			}
		}
	}
	curSize = newSize;
}

void __fastcall TCharBuff::trimFromStart()
{
	if (data == NULL || curSize == 0 || curPosition == 0)
	{
        return;
	}

	unsigned int sizeToEnd = getSizeToEnd();

	if (sizeToEnd == 0)
	{
        clearData();
        return;
	}

	//fullSize = sizeToEnd + CHARBUFF_MIN_FULL_SIZE;

	//char* newData = new char[fullSize];
	read(data, sizeToEnd);
//	deleteData();
//    fullSize = sizeToEnd + CHARBUFF_MIN_FULL_SIZE;
//	data = newData;
	curSize = sizeToEnd;
    curPosition = 0;
}

void __fastcall TCharBuff::setSize(unsigned int size)
{
	if (size != curSize)
	{
		resize(size);
	}
}

unsigned int __fastcall TCharBuff::getSize()
{
	return curSize;
}

void __fastcall TCharBuff::setPosition(unsigned int pos)
{
	if (pos > curSize)
	{
		resize(pos);
	}

	curPosition = pos;
}

unsigned int __fastcall TCharBuff::getPosition()
{
	return curPosition;
}

void __fastcall TCharBuff::write(void* source, unsigned int count)
{
	if (curPosition + count > curSize)
	{
		resize(curPosition + count);
	}

	memcpy(&((char*)data)[curPosition], source, count);
	//Move(source, &((char*)data)[curPosition], count);
	curPosition = curPosition + count;
}

unsigned int __fastcall TCharBuff::read(void* dest, unsigned int count)
{
	unsigned int maxRead;// = std::min<int>(count, getSizeToEnd());
	if(count <= getSizeToEnd())
	{
		maxRead = count;
	}
	else
	{
		maxRead = getSizeToEnd();
    }

	if (maxRead == 0)
	{
		return 0;
	}
	memcpy(dest,&((char*)data)[curPosition],maxRead);
//	Move(&((char*)data)[curPosition], dest, maxRead);
	curPosition = curPosition + maxRead;
    return maxRead;
}

void* __fastcall TCharBuff::getPointerFromCurPos()
{
	if (curPosition == curSize)
	{
		return NULL;
	}
	return &((char*)data)[curPosition];
}

unsigned int __fastcall TCharBuff::getSizeToEnd()
{
    return curSize - curPosition;
}
