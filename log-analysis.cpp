# include <cstdlib>
# include <iostream>
# include <cmath>
# include <ctime>
# include <omp.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

using namespace std;
int result1[2];
int result2[2];
int main ( );
int *get_error_line (char *fileName, char* searchString );
int *get_error_line2 (char *fileName, char* searchString );


int main ( void )
{

	int *output1;
	int *output2;

	double task_time;
  double task1_time;
	double task2_time;

	string file_Name = "NDPTSP.LOG";
	string keyword1 = "SyncDriverRequest";
	string keyword2 = "CommitNegotiatedTSPIVersion";
	char *f = &file_Name[0];
	char *k1 = &keyword1[0];
	char *k2 = &keyword2[0];

	//
	task_time = omp_get_wtime ( );
	# pragma omp parallel shared ( output1, output2 )
	{
	  # pragma omp sections
	  {
	    # pragma omp section
	    {
	      task1_time = omp_get_wtime ( );
	      output1 = get_error_line(f, k1);
	      task1_time = omp_get_wtime ( ) - task1_time;
	    }
	    # pragma omp section
	    {
	      task2_time = omp_get_wtime ( );
	      output2 = get_error_line2(f, k2);
	      task2_time = omp_get_wtime ( ) - task2_time;
	    }
	  }
	}

	  task_time = omp_get_wtime ( ) - task_time;
	cout << "******************** Task 1 ************************\n";
	cout << "\n";
  cout << "  Keyword '"<< keyword1 <<"' is present at:" << "\n";
  cout << "  Line no. " << *(output1+0) << "\n";
  cout << "  Number of times error '"<< keyword1 <<"' found was " << *(output1+1) << "\n";
	cout << "\n";
	cout << "******************** Task 2 ************************\n";
  cout << "  Keyword '"<< keyword2 <<"' is present at:" << "\n";
  cout << "  Line no. " << *(output2+0) << "\n";
  cout << "  Number of times '"<< keyword2 <<"' found was " << *(output2+1) << "\n";
	cout << "  Output file is stored with name output2.log. '\n";
	cout << "\n";
	cout << "**************** Analysis of both tasks *****************\n";
	cout << "\n";
  cout << "  Total time taken by task1 and task2  = " << task_time << "\n";
  cout << "  Time taken by task1 = " << task1_time << "\n";
  cout << "  Time taken by task2 = " << task2_time << "\n";

	cout << "\n";
  cout << "  Execution Ended Normally...\n";
  cout << "\n";

  //timestamp ( );

  return 0;
}

int* get_error_line ( char* fileName, char* searchString )
{
	/* * Declare File pointer and other variables
		 * line_num is a counter for counting the number of lines.
		 * last_line is for storing the number of last line.
		 * buffer is a character array which will store entire line from the given line.
		 * noOfResult is a counter for getting the total count of keywords matched.
	*/
  FILE *fp1;
  int line_num=1;
  int last_line=0;
  char buffer[512];
  int noOfResult= 1;

	// This is to check whether the file is present or not!
  if((fp1 = fopen(fileName, "r")) == NULL) {
		cout << "no file present..";
	}

	// Traverse entire file line by line and search for the 'keyword' in a single line.
	// If keyword match is found increment the noOfResult counter and store the latest line number in result2 array
  while(fgets(buffer, 512, fp1) != NULL) {
		if((strstr(buffer, searchString)) != NULL) {

      result1[0]=line_num;
      result1[1]=noOfResult++;
		}
		line_num++;
	}

	//return the result
  return result1;
}


int* get_error_line2 ( char* fileName, char* searchString )
{
	/* * Declare File pointer and other variables
		 * line_num is a counter for counting the number of lines.
		 * last_line is for storing the number of last line.
		 * buffer is a character array which will store entire line from the given line.
		 * noOfResult is a counter for getting the total count of keywords matched.
	*/
  FILE *fp1, *fp2;
  int line_num=1;
  int last_line=0;
  char buffer[512];
  int noOfResult= 1;

	// This is to check whether the file is present or not!
  if((fp1 = fopen(fileName, "r")) == NULL) {
		cout << "no file present..";
	}
	fp2 = fopen("output2.log", "w");
	// Traverse entire file line by line and search for the 'keyword' in a single line.
	// If keyword match is found increment the noOfResult counter and store the latest line number in result2 array.
  while(fgets(buffer, 512, fp1) != NULL) {
		if((strstr(buffer, searchString)) != NULL) {

      result2[0]=line_num;
      result2[1]=noOfResult++;
			strcat(buffer, "\n");
			fputs(buffer, fp2); //output is stored in output2.log
		}
		line_num++;
	}

	//return the result
  return result2;
}
