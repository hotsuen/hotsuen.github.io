#include<stdlib.h>
#include<stdio.h>
#include<string.h>


#define MEMBER 10
#define MAXWORD 25


typedef struct Patient{
  char name[MAXWORD];
  int age;
  int vaccination_status;
  struct Patient *next;

}Patient;


int main()
{
  char name[MEMBER];
  int age;
  int vaccination_status;
  int y,z=0,search;
  float uninoculated=0;
  float first_dose=0;
  float second_dose=0;
  float third_dose=0;

  
  Patient *Members = NULL;

  while(z < 1){
    search = 0;
    
    printf("|1:Register patient data                              |\n");
    printf("|2:Update vaccination status for enrolled patient data|\n");
    printf("|3:Display patient data                               |\n");
    printf("|4:Delete data                                        |\n");
    printf("|5:finish                                             |\n");
    printf("Please enter a number:");
    scanf("%d",&y);
    printf("\n");
    
    if(y ==1){
      printf("Enter name: "); 
      
      scanf("%s", name); 
      
      printf("Enter age: "); 
      
      scanf("%d", &age); 
      
      printf("Enter vaccination status (1/2/3): "); 
      
      scanf("%d", &vaccination_status); 
      
      Patient *newPatient = (Patient *)malloc(sizeof(Patient)); 
      
      strcpy(newPatient->name, name); 
      
      newPatient->age = age; 
      
      newPatient->vaccination_status = vaccination_status; 
      
      newPatient->next = Members; 
      
      Members = newPatient; 
     
  }
    
    else if(y == 2){//ワクチン状態を更新
      int new_status;
      
      printf("Enter name: "); 
      
      scanf("%s", name); 
      
      printf("Enter age: "); 
      
      scanf("%d", &age); 
      
      printf("Enter new vaccination status (1/2/3): "); 
      
      scanf("%d", &new_status); 
      
     
      while (Members != NULL) { 

	Patient *now =Members;
	
        if (strcmp(now->name, name) == 0 && now->age == age) { 
	  
	  now->vaccination_status = new_status; 

	  search++;
	  
	  break; 
	  
        } 
	
        now = now->next;

	
      }
      if(search == 0){
	printf("\n error\n\n");
      }
    }
    
    else if(y == 3){
      
      printf("Enter name: "); 
      
      scanf("%s", name); 
      
      printf("Enter age: "); 
      
      scanf("%d", &age); 

      Patient *now = Members;
      
      while (now != NULL) { 
	
        if (strcmp(now->name, name) == 0 && now->age == age) { 
	  
	  printf("\n\nName: %s\n", now->name); 
	  
	  printf("Age: %d\n", now->age); 
	  
	  printf("Vaccination Status: %d\n\n", now->vaccination_status); 

	  search++;
	  
	  break;
	  
        } 
	
        now = now->next; 
	
      } 
      if(search == 0){
	printf("error\n\n"); 
      }
    }
    else if(y == 4){
      
      printf("Enter name: "); 
      
      scanf("%s", name); 
      
      printf("Enter age: "); 
      
      scanf("%d", &age);
      
      Patient *now = Members; 
      
      Patient *prev_member = NULL; 
      
      
      while (now != NULL) { 
	
        if (strcmp(now->name, name) == 0 && now->age == age) { 
	  
	  if (prev_member == NULL) { 
	    
	    Members = now->next; 
	    
	  } else { 
	    
	    prev_member->next = now->next; 
	    
	  } 
	  
	  free(now); 
	  
	  printf("completion\n");
	  
	  search++;
        } 
	
        prev_member = now; 
	
        now = now->next; 
	
      } 
      
      
      if(search == 0){
      printf("error\n\n"); 
      }
      
    }
    else if(y == 5){
      printf("good bye\n");
      z++;
    }
    else {
      printf("error\n\n");
      y = 5;
    }
  }
  return 0;
}

