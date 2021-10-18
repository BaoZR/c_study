#include <stdio.h>
#include <dlfcn.h>
#include "wcr_splitter.h"

int wcr_dyna_split(const char* lib_name, const char* texts, size_t length)
{
	void * handle = NULL;
	int(*pfn_wcr_split)(const char*, size_t);

	handle = dlopen(lib_name,RTLD_LAZY);
	if(handle == NULL)
	{
		printf("failed to open(%s)\n",lib_name);
		return -1;
	}
	*(void**)&pfn_wcr_split = dlsym(handle, "wcr_split");
	if(pfn_wcr_split == NULL)
	{
		printf("failed to find split function\n");
	}else{
		pfn_wcr_split(texts, length);
	}
	dlclose(handle);
	return 0;
}



int main(int argc, char* argv[])
{
	const char* texts = "this is a   long line to split.  \n";
	if(argc > 1)
	{
		return wcr_dyna_split(argv[1], texts, 0);
	}
	else{
		return wcr_split(texts, 0);
	}
}

