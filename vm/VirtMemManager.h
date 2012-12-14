#ifndef VIRTMEMMANAGER_H
#define VIRTMEMMANAGER_H

#include "openfile.h"
#include "translate.h"
#include "addrspace.h"

#define MAX_VIRT_PAGES 4096

//// The following class defines an entry in virtual memory table. Each process 
//// has a related virtual memory entry because thread has its own address space.
//
//class VirtMemEntry
//{
//	public:
//		int mainThreadId;	// The main thread which hold address space.
//		int refCount;		// Reference count for threads' sharing.
//							// Threads in process share address space, so many 
//							// threads may point to one entry.
//		int size;			// Page table size.
//		TranslationEntry* pageTable; 	// Page table which contain
//										// thread's address space.
//};

// The following class defines a manager of virtual memory. It takes over the
// creation and initialization of thread's page table, so it contains all
// virtual pages in system including page status.

class VirtMemManager
{
	public:
		VirtMemManager(int size);
		~VirtMemManager();

		AddrSpace** getVirtMemCtrlTable() { return (virtMemCtrlTable); }

		AddrSpace* createAddrSpace(int mainThreadId, OpenFile* executable);
		AddrSpace* shareAddrSpace(int mainThreadId, int currThreadId);
		void deleteAddrSpace(int threadId);

	private:
		int virtPageNums;		// Virtual page numbers.
		int virtMemCtrlTableSize;	// Virtual memory table size.
		AddrSpace** virtMemCtrlTable; // Virtual memory table.
};

#endif
