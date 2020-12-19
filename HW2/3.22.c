#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<sys/mman.h>
#include<fcntl.h> 

int main()
{
	const char *shm_name = "shared memory object";
	int shm_fd = shm_open(shm_name, O_CREAT|O_RDWR, 0);
	int ftrunc_res = ftruncate(shm_fd, 64);	


	int *sh_mm = mmap(0, 64, PROT_READ|PROT_WRITE, MAP_SHARED, shm_fd, 0);

	pid_t pid=fork();
	
	if(pid==0)
	{
		printf("Child process created \n Enter an integer: ");
		int n;
		scanf("%d",&n);
		sh_mm[0]=n;
		int i=1;
		while(n>1)
		{
			if(n%2==0)
			{
				sh_mm[i]=n/2;
				n=n/2;
				i++;
			}
			else{
				sh_mm[i]=3*n+1;
				n=3*n+1;
				i++;
			}
		}
		sh_mm[i]=-1;
		return 0;
	}
	else{
		wait(NULL);
		printf("Child terminated \n Outputting contents of shared memory: ");
		int i=0;
		while(sh_mm[i]!=-1)
		{
			printf("%d ",sh_mm[i]);
			i++;
		}
		int res=shm_unlink(shm_name);
		if(res==0)
			printf("\n Removed shared memory object. \n");
	}
	return 0;
}