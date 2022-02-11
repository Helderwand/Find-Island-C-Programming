/*
We saved the first line of input.txt as an integer. We took the remaining 512*512 input as an integer and saved it as a char matrix (we chose char to take up less space because it ranges from 0-128)
We inserted our matrix and x,y values into our recursion function by inserting it into another loop, if it specifies an island (if it is not within the path of another island), then check the next (bottom, right, left and above) islands.
We understand if there is a path by doing it. If there is a path, we mark 2 . (in order not to enter it again in the main function). As a result, if the x and y sent from the main function specifies, we print it to output.txt.
*/
#include <stdio.h>
#define MAX 512
#define MAX_ISLAND 100

int checkIsIsland(int x , int y , char (*arr)[MAX] ){
	if( (arr[x][y] == 2  || arr[x][y] == 0) || ( x>=MAX || y>=MAX )  ){	/*Check if it's above water level or already looked after.And we restricted it to MAX(512) to check for points in the class regions of the matrix.*/
		return 0 ;					/*If it doesn't show as an island, return 0 .*/
	}
	else{
		arr[x][y]= 2 ;				/*Mark as viewed.*/
		checkIsIsland(x,y+1,arr);	/*Check the number to the right if it creates a path.(recursion)	*/
		checkIsIsland(x,y-1,arr);	/*Check the number on the left to see if it creates a path .(recursion)	*/
		checkIsIsland(x+1,y,arr);	/*Check the number below to see if it creates a path.(recursion)	*/
		checkIsIsland(x-1,y,arr);	/*Check the number above to see if it creates a path.(recursion) 	*/
		return 1 ;					/*When all functions are provided return that here is an island(1) and make sure it doesn't come in again as the views are pointed out. */
	}
}
int main(){
    int L , i = 0 ,x = 0 , y = 0 ,island_founded = 0 ,check_island , temp ;
    char matrix[MAX][MAX];
	FILE *fr = fopen("input.txt","r");/*Open input.txt for reading.*/
	FILE *fw = fopen("output.txt","w");/*Open output.txt to output on it.*/
	if (fr == NULL )/*If there is no file to read.*/
	{
		fprintf(fw,"The input.txt file doesn't exist.");/*Print that there is no existing input.txt.*/
		return 0 ;
	}
	else{
		while(feof(fr) == 0 ){
			if(x == MAX){
				fprintf(fw ,"!!! MORE ENTRIES THAN EXPECTED !!! ");/*Check an input of more than 512x512.*/
				return 0;
			}
            if(i == 0 ){
                fscanf(fr,"%d",&L);/* We read L character and save it as integer .*/
                if( L <= 0 || 128 <= L ){/*Check if L is given values.*/
                	fprintf(fw,"!!! WATER LEVEL ERROR !!! ");
                	return 0 ;
				}
                i = 1 ;
            }
			else {
                fscanf(fr,"%d",&temp);	/*Temporarily assign values as integers.*/
                matrix[x][y] = temp; 	/*Save the assigned values in the char matrix so that it takes up little space .*/
                if(matrix[x][y]< 0 || matrix[x][y] >= 128 ){
                	fprintf(fw,"!!! TERRAIN ERROR !!! ");/*Check if it is below 0 or exceeding 128. */
                	return 0 ;
				}
				if(matrix[x][y] > L){/*Check if the value given is greater than L . And save them as 1 or 0 .( 1--above the water level . 0--At or below the water level. )*/
					matrix[x][y] =  1;
				}
				else{
					matrix[x][y] = 0 ;
				} 
                if(y == MAX-1){
                    x++;
                    y = 0 ;
                }
                else{
                	y++;
				}
			}
		}
		for(x=0;x<MAX;x++){ 			/*Print the filled matrix back to output.txt in the form of any coordinate of the island from 0 to 512.*/
			for(y=0;y<MAX;y++){
				check_island = checkIsIsland(x , y, matrix);/*Save the value from the function as an integer. */
				if(check_island == 1 ){
					island_founded++;
					if(island_founded == MAX_ISLAND+1){
						fprintf(fw,"There are MORE ISLAND than wanted");
						return 0 ;
					}
					fprintf(fw,"x_coordinate\t:%d\ty_coodinate\t:%d\n",x,y);/*Print the x and y coordinates of the island to output.txt .*/
				}	
			}
		}
	}
	fclose(fr);/*Close input and output files. */
	fclose(fw);
	return 0 ;
}
