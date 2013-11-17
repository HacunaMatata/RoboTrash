#ifndef CMEMMANAGER_H
#define CMEMMANAGER_H

#include <iostream>
#include <cstdlib>
#include <stdio.h>

#undef new
#undef delete

namespace MEMORY
{


struct DATA
{
    void*        Address;
    unsigned int Lenght;
    bool         Free;
};

enum MM_LOG_MODE
{
    MMLM_NONE = 0x0,
    MMLM_DEST = 0x1,
    MMLM_COMM = 0x2,
    MMLM_EXTD = 0x3,
    MMLM_TOTL = 0x4,
};

//!-----------------------------------------------------------------
class Array
{
public:

    Array()
    {
        TotalSize = 0;
        Size = 0;

        NEW_calls = 0;
        DELETE_calls = 0;

        byte_allocated = 0;

        ArrayRealocated = 0;

        Allocating_step = 25;

        LogMode = MMLM_DEST;
    }

    ~Array()
    {
        free(array);
        if(LogMode >= MMLM_DEST)
        {
            double inmegabyte = byte_allocated / 1024 / 1024;
            std::cout << "\n" << std::endl;
            if(inmegabyte <= 0.1)
            {
                std::cout << "Memory leak: " << byte_allocated << " byte" << std::endl;
            }
            else
            {
                std::cout << "Memory leak: " << inmegabyte << " MB ("<< byte_allocated << " byte)" << std::endl;
            }
        if(LogMode >= MMLM_EXTD)
        {
            std::cout << "Pointer storage reloaded " << ArrayRealocated << " times" << std::endl;
        }
        }
    }

//-----------------------------------------

//-----------------------------------------
    void Add(DATA data)
    {
        if(TotalSize == Size)
        {
            ReAllocateArray();
        }

        if(LogMode >= MMLM_COMM)
        {
            std::cout << "Add memory block:" << data.Address << " Size:" <<data.Lenght << std::endl;
        }

        array[Size] = data;
        Size++;
        NEW_calls++;
        byte_allocated += data.Lenght;
    }
//-----------------------------------------
    void Remove(void* Address)
    {
        if(LogMode >= MMLM_EXTD)
        {
            std::cout << "Try to delete memory block:" << Address << std::endl;
        }

        for(unsigned int c = 0; c < Size; c++)
        {
            if(LogMode >= MMLM_TOTL)
            {
                std::cout << "Finded memory block:" << array[c].Address << " Size:" << array[c].Lenght << " Free:" << array[c].Free<< std::endl;
            }
            if(array[c].Address == Address && !array[c].Free)
            {

                    array[c].Free = true;
                    byte_allocated -= array[c].Lenght;

                    if(LogMode >= MMLM_COMM)
                    {
                        std::cout << "Deleting memory block:" << array[c].Address << " Size:" <<array[c].Lenght << std::endl;
                    }

            }

        }
        DELETE_calls++;
    }
//-----------------------------------------
    void ReAllocateArray()
    {
        if(LogMode >= MMLM_EXTD)
        {
            std::cout << "Try to reallocate pointer storage" << std::endl;
        }
        bool MustReAllocate = false;
        int  RelesedMemoryCounter = 0;

        for(unsigned int c = 0; c < Size; c++)
        {
            if(array[c].Free == true)
            {
                RelesedMemoryCounter++;
            }
        }

        if(RelesedMemoryCounter <= 25)
        {
            MustReAllocate = true;
        }

        if(LogMode >= MMLM_EXTD)
        {
            std::cout << "  Total " << TotalSize << " records.(" << RelesedMemoryCounter << " records rejected and erased)" << std::endl;
        }
        //--------------------------------
        unsigned int New_TotalSize  = 0;
        unsigned int New_Size       = 0;

        if(MustReAllocate == true)
        {
            New_TotalSize = TotalSize + Allocating_step;
        }
        else
        {
            New_TotalSize = TotalSize;
        }

        DATA* NewArray = reinterpret_cast<DATA*>(malloc(sizeof(DATA)*New_TotalSize));

        for(unsigned int c = 0; c < Size; c++)
        {

            if(array[c].Free != true)
            {
                NewArray[New_Size] = array[c];
                New_Size++;
            }

        }

        free(array);
        array = NewArray;
        TotalSize = New_TotalSize;
        Size = New_Size;
        ArrayRealocated++;
    }

    //-------------------------GETS
    unsigned int getMemoryAllocated()
    {
        return byte_allocated;
    }
    void SaveInFile(const char* filename)
    {
        FILE* file;
        file = fopen(filename,"w");

        for(unsigned int c = 0; c < Size; c++)
        {
            if(array[c].Free == 0)
                fprintf(file,"Memory block:0x%x Size:%i Free:%x\n",int(array[c].Address),array[c].Lenght,array[c].Free);
        }

        fclose(file);
    }
    //-------------------------sets
    void setAllocatingStep(unsigned int NewStep)
    {
        Allocating_step = NewStep;
        ReAllocateArray();
    }
    void setLogMode(MM_LOG_MODE logmode)
    {
        LogMode = logmode;
    }
private:

    DATA* array;

    unsigned int TotalSize;
    unsigned int Size;

    unsigned int NEW_calls;
    unsigned int DELETE_calls;

    unsigned int byte_allocated;

    unsigned int ArrayRealocated;

    unsigned int Allocating_step;

    unsigned int LogMode;


};

static Array MemoryManager;
}

//!----------------------------------------------------------------------------------------

void * operator new(size_t size)
{
    void* pointer = malloc(size);
    MEMORY::DATA cell;

    cell.Address = pointer;
    cell.Lenght = size;
    cell.Free = false;

    MEMORY::MemoryManager.Add(cell);
    return pointer;
}

void operator delete(void *p)
{
    MEMORY::MemoryManager.Remove(p);
    free(p);
}
//------------------------------------
void * operator new[](size_t size)
{
    void* pointer = malloc(size);
    MEMORY::DATA cell;

    cell.Address = pointer;
    cell.Lenght = size;
    cell.Free = false;

    MEMORY::MemoryManager.Add(cell);
    return pointer;
}

void operator delete[](void *p)
{
    MEMORY::MemoryManager.Remove(p);
    free(p);
}
//-------------------------------------


#endif // CMEMMANAGER_H
