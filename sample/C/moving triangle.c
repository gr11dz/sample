#include <stdlib.h>
#include <stdio.h>

void right(int tri, int border);
void down(int tri, int border);
void left(int tri, int border);
void up(int tri, int border);

int main()
{
	int border,tri;
	printf("insert your border size(recommend 12): ");
	scanf("%d", &border);
	printf("insert your triangle size(recommend 3): ");
	scanf("%d", &tri);
	system("cls");
   while(1){
       right(tri, border);
       down(tri, border);
	   left(tri, border);
	   up(tri,border);
   }
}

void right(int tri, int border)
{
	int i,j,k;	
	for(i = 0; i <= border ; i++){
		for(j =1; j <= tri ; j++){
		 for(k =1; k < i ; k++){
		      printf("   ");
	       }
		 for(k =0; k<j ; k++){
        	  printf("* ");
		    } 
	     printf("\n");	   
	   }
    	for(j =1; j <= tri ; j++){
    	 for(k =1; k < i ; k++){
    	      printf("   ");
   	       }
	     for(k =tri; k > j ; k--){
		    	printf("* ");
	    	} 
		   printf("\n");
    	}
    	_sleep(100);
    	system("cls");
	}
}

void down(int tri, int border)
{
	int i,j,k;
    for(i =0; i <= border ; i++){
		for(k =0; k <= i ; k++){
			printf("\n");
		}
		for(j =0 ; j < tri ; j++){
		    for(k =0; k <= border ; k++){
			   printf("   ");
	     	}			
        	for(k= 0; k < j ; k++){
    		  printf("  ");
		    }
		    for(k =0; k < 2*tri-1 - (2*j) ; k++){
			   printf("* ");
		    }
		 printf("\n");
       }
		_sleep(100);
		system("cls");
	}
}

void left(int tri ,int border)
{
	int i,j,k;	
	for(i = 0; i <= border ; i++){
		for(k =0; k <= border; k++){
			printf("\n");
		}
		for(j =0 ; j < tri ; j++){
	    	for(k =i; k <= border ; k++){
	 		  printf("   ");
	    	}
		    for(k =1; j < tri -k ; k++){
			  printf("  ");
		   }
	    	for(k =0; k <= j ; k++){
		    	printf("* ");
	        }
	    	printf("\n");
	    }
    	for(j =0 ; j < tri ; j++){
    		for(k =i; k <= border ; k++){
	 		  printf("   ");
	    	}
	    	for(k =0 ; k <= j ; k++){
			  printf("  ");
	        }
	    	for(k =0; k < tri -j-1 ; k++){
		    	printf("* ");
		    }
	    	printf("\n");
	    }
		_sleep(100);
		system("cls");
	}
}

void up(int tri, int border)
{
	int i,j,k;
	for(i =0 ; i <=border ; i++){
		for(j =0; j <= border-i ;j++){
			printf("\n");
		}
		for(j =0; j < tri ; j++){
    	  for(k =1; k < tri -j ; k++){
              printf("  ");
		   }
	      for(k =0 ; k < 2*(j+1) -1 ;k++){
		      printf("* ");
	       }
	    	printf("\n");	
	   }
		_sleep(100);
		system("cls");
	}
}
