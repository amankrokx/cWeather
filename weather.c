#include<stdio.h>
#include<stdlib.h>

int main(){

    //-start
    //-check internet connection :- 

    //if internet not present
    int ch=0;
    printf("\nInternet connection is unavailable\n1.Retry\n2.Exit ");
    scanf("%d",&ch);
        switch(ch)
            {
                case 1: //retry check connection again;
                        break;
                case 2: printf("\nHave a GOOD DAY !!");   exit(0);
                default: printf("\nInvalid Input aborting ...");
                         exit(0);
            }

    //if internet present
    //check for files :-
    //if not present --> new user
    printf("\nWelcome, Dear :\n");
    char addr[20]; ch=0;
    printf("1.Please Enter your location\n2.Exit ");
    scanf("%d",&ch);
        switch(ch)
            {
                case 1: scanf("%s",addr);
                        break;
                        //get coordinates with GEOCODING API    
                        // Add to file as Home location
                case 2: printf("\nHave a GOOD DAY !!");   exit(0);
                default: printf("\nInvalid Input aborting ...");
                         exit(0);
            }

    //Existing user and internet available
    int n1,n2;  char new_addr[20];
    for(;;)
    {
        ch=0;
        printf("\n\t\tMAIN MENU\n\n1. Show Current Weather\n2. Show by Address\n3. Edit Saved Locations\n4. Exit ");
        scanf("%d",&ch);
        switch(ch){
            case 1: //show detailed weather
                    //check saved lcoation from files
                    //get info for saved locations
                    for(;;){
                    printf("\n1.Show 5 Days Forecast\n2.Go Back");
                    scanf("%d",n1);
                    switch(n1)
                        {
                            case 1: //show 5 days forecast
                                    break;
                            case 2: exit(0);
                            default: printf("\nInvalid Input aborting ...");
                                    exit(1);
                        }
                    }
                    break;

            case 2: 
                    for(;;){
                    printf("\n1.Enter Any Location\n2.Get Weather\n3.BACK ");
                    scanf("%d",n2);
                    switch(n2)
                        {
                            case 1: //Add entered location to favourites
                                    break;
                            case 2: //find weather at provided location
                                    break;
                            case 3: exit(1);
                            default: printf("\nInvalid Input aborting ...");
                                    exit(0);
                        }
                    }
                    break;

            case 3:
                    for(;;){
                    printf("\n1.Enter location\n2.Show favourite\n3.Edit favourite "); 
                    scanf("%d",n2);
                    switch(n2)
                        {
                            case 1: scanf("%s",new_addr);      //entered location use geocoding to store coordinates
                                    break;
                            case 2: //show favourite
                                    break;
                            case 3: //edit favourites
                                    break;
                            default: printf("\nInvalid Input aborting ...");
                                    exit(0);
                        }
                    }

                    break;
            case 4: printf("\nHave a GOOD DAY !!");   exit(0);
                    break;

            default: printf("\nInvalid Input aborting ...");
                         exit(0);
        }
    }
}