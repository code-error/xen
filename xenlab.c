#include<stdio.h>
#include<stdlib.h>
#include<libvirt/libvirt.h>
int main()
{
  virConnectPtr connection;
  virDomainPtr domain;
  int num_domains,i,choice,value=-1,id;
  int *active_domains;
  int c=1;
  connection=virConnectOpen("xen:///");
  if(connection==NULL)
  {
    fprintf(stderr,"could not open xen:///\n");
    exit(0);
  }
  else
  {
    num_domains=virConnectNumOfDomains(connection);
    active_domains=malloc(sizeof(int) * num_domains);
    num_domains = virConnectListDomains(connection, active_domains, num_domains);

    printf("Active domain IDs : \n");
    for(i=0;i<num_domains;i++) 
    {
      printf("  %d\n", active_domains[i]);
    }

    free(active_domains);
    printf("List of operation;\n");
    printf(" 1)suspend \n 2)resume \n 3)shutdown \n 4)start\n");
    printf("Enter yor choice");
    scanf(" %d ",&choice);
    while(c==1)
    {
      
      printf("Enter the active id:");
      scanf("%d",&id);
      domain=virDomainLookupByID(connection,id);
      switch(choice)
      {
        case 1 : value=virDomainSuspend(domain);
                 if(value==0)
                   printf("successful \n");
                 else
                   printf("failed\n");
                 break;
        case 2 : value=virDomainResume(domain);
                 if(value==0)
                   printf("successful\n");
                 else
                   printf("failed\n");
                 break;
        case 3 : value=virDomainDestroy(domain);
                 if(value==0)
                   printf("successful \n");
                 else
                   printf("failed\n");
                 break;
        case 4 : value=virDomainCreate(domain);
                 if(value==0)
                   printf("successful\n");
                 else
                   printf("failed\n");
                 break;
        default : printf("Enter any valid choice (1-4)\n");
                  break;
      }
      printf("Do you want to enter again :");
      scanf("%d",&c);
    }
    virConnectClose(connection);

  }
  return 0;
}
