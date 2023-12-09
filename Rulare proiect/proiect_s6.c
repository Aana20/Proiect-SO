#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>
#include<aio.h>
#include <string.h>
#include<time.h>



int main(int argc, char * argv[])
{

	if(argc != 2)
	{
		printf("Usage /.program  <fisier_intrare>\n");
		return 1;
	}
	
	int input =open(argv[1],O_RDONLY );
		if(input == -1 )
		{
			perror("Eroare la deschidere");
			exit(-1);
		}	
	
	int output=creat("statistica.txt",S_IRUSR|S_IWUSR|S_IWOTH);
		if(output == -1)
		{
			perror("Eroare la crearea fisierului statistica.txt");
			int inchidere=close(input);
			
			if(inchidere == -1)
		{
			perror("Eroare la inchidere");
			exit(-4);
		}
		}
		
		
		ssize_t bytes=0;
		char aux[100];
		
		bytes=read(input,aux,18);
		
			if(bytes == -1)
			{
				perror("eroare la citire");
				exit(-5);
			}
			
		int lungime;	
		bytes=read(input,&lungime,4 );
		if(bytes == -1)
			{
				perror("eroare la citire");
				exit(-6);
			}
		
		
			
		
		
		int inaltime;
		bytes=read(input,&inaltime,4 );
		
		
		if(bytes == -1)
			{
				perror("eroare la citire");
				exit(-6);
			}
		
		
		struct stat file_stat;
		
		
		fstat(input,&file_stat);
	
         
		int size=file_stat.st_size; //dimensiune: <dimensiune in octeti>

		
		 int id_owner =file_stat.st_uid; //identificatorul utilizatorului
		 
		
		 
		struct timespec  st_mtim;
		
		//st_mtim = file_stat.st_mtim; //timpul ultimei modificari: 28.10.2023
		
		//printf("%s", ctime(&st_mtim));
		char mtime[80];
		time_t t = file_stat.st_mtime;
		
		struct tm lt;
    localtime_r(&t, &lt); /* convert to struct tm */
    strftime(mtime, sizeof mtime,"%d %b %Y ", &lt);
   // printf("%s\n",mtime);
		
		int contor_legaturi =file_stat.st_nlink; //contorul de legaturi: <numar legaturi>
		
			char stru[4]="",strg[4]="",stro[4]="";
			char r='R',w='W',no='-',x='X';
       
         int fileMode = file_stat.st_mode;
        /* Check owner permissions */
        if ((fileMode & S_IRUSR) && (fileMode & S_IREAD))
        	strncat(stru,&r,1);
        	else
        	strncat(stru,&no,1);
        
        if ((fileMode & S_IWUSR) && (fileMode & S_IWRITE)) 
           strncat(stru,&w,1);
        	else
        	strncat(stru,&no,1);
        if ((fileMode & S_IXUSR) && (fileMode & S_IEXEC))
          strncat(stru,&x,1);
        	else
        	strncat(stru,&no,1);
        /* Check group permissions */
        if ((fileMode & S_IRGRP) && (fileMode & S_IREAD))
          
          strncat(strg,&r,1);
        	else
        	strncat(strg,&no,1);
        
        if ((fileMode & S_IWGRP) && (fileMode & S_IWRITE))

          strncat(strg,&w,1);
        	else
        	strncat(strg,&no,1);
        if ((fileMode & S_IXGRP) && (fileMode & S_IEXEC))
         
          strncat(strg,&x,1);
        	else
        	strncat(strg,&no,1);
        /* check other user permissions */
        if ((fileMode & S_IROTH) && (fileMode & S_IREAD))
        strncat(stro,&r,1);
        	else
        	strncat(stro,&no,1);
        if ((fileMode & S_IWOTH) && (fileMode & S_IWRITE))
       strncat(stro,&w,1);
        	else
        	strncat(stro,&no,1);
        if ((fileMode & S_IXOTH) && (fileMode & S_IEXEC))
          
	strncat(stro,&x,1);
        	else
        	strncat(stro,&no,1);
		
	
       
		
		char buffer1[320];
		
	sprintf(buffer1,"nume fisier:  %s\n inaltime:  %d \n lungime: %d \n dimensiune: %d \n indentificatorul utilizatorului: %d\n timpul ultimei modificari : %s\n contorul de legaturi: %d\n drepturi de acces user: %s\n drepturi de acces grup: %s\n drepturi de acces altii : %s\n",argv[1],inaltime,lungime,size,id_owner,mtime,contor_legaturi,stru,strg,stro);
		size_t nbyte;
		
		nbyte = strlen(buffer1);
		//printf("%ld",nbyte);
		int fd=open("statistica.txt",O_RDWR);
		
		//eroare daca nu se deschide
		if(fd == -1 )
		{
			perror("Eroare la deschidere");
			exit(-1);
		}	
		
		write(fd,buffer1,nbyte);
		//printf("b=%s\n",buffer1);
		
		
		
	int c=close(input);
		if(c == -1)
		{
			perror("Eroare la inchidere");
			exit(-3);
		}
return 0;
}































