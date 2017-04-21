#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <stdio.h>
#include <pstream.h>
#include <cstring>


using namespace std;


int main ()
{

    int i;
    uint64_t x, n;
    clock_t bg, us;
    int run = 10000;
    bg = clock();
    n = 0;
    do {
        for (i = 0; i < run; i++)
        {

		remove("/home/pi/Projects/masterProject/Receiver/canMwithDigest.txt");
 	 	string msg, receivedDigest;
  		// run a process and create a streambuf that reads its stdout and stderr
 	 	redi::ipstream proc("candump -n 1 vcan0", redi::pstreams::pstdout | redi::pstreams::pstderr);
	 	std::string line;
  		// read child's stdout
  		if (std::getline(proc.out(), line))
  		{
    			char *cstr = new char[line.length() + 1]; 
    			strcpy(cstr, line.c_str());
    		//	std::cout << "stdout: " << line << '\n';    
    			std::string fileName1 = "canMwithDigest.txt";
    			std::ofstream canMwithDigest (fileName1.c_str(), ios::app | ios::in | ios::binary );
    			if (canMwithDigest)
    			{
    				canMwithDigest.write (cstr,line.length() + 1);
    				msg = line.substr (23,104);
    				receivedDigest = line.substr(128);
    		//		cout <<"the msg is " <<msg <<endl;
    		//		cout <<"the received digest is "<< receivedDigest<<endl;
    				canMwithDigest.close();
    			}	   
  		}	
 		char* nodeMessage = "BB CC DD EE FF AA BB CC DD EE FF AA BB CC DD EE FF AA BB CC DD EE FF AA BB CC DD EE FF AA BB CC DD EE FF";
		//cout <<nodeMessage<<endl;
 		char* key1 = "adabdcfecdabdcfecdabdcfecdab";
 		char* key2 = "bdabdcfecdabdcfecdabdcfecdab";
 		char* key3 = "ddabdcfecdabdcfecdabdcfecdab";
 		char* key4 = "cdabdcfecdabdcfecdabdcfecdab";
 		if (nodeMessage =="ab3addccffeebbaaddccffeebbaaddccffeebbaaddccffeebbaaddccffeebbaaddccffee")
 		{
			char* key = "adabdcfecdabdcfecdabdcfecdab";
			//printf("The key is %s\n",key); 
 		}
 		else if (nodeMessage =="cb3addccffeebbaaddccffeebbaaddccffeebbaaddccffeebbaaddccffeebbaaddccffee")
 		{
        		char* key = "bdabdcfecdabdcfecdabdcfecdab";
        		//printf("The key is %s\n",key);
 		}
 		else if (nodeMessage =="db3addccffeebbaaddccffeebbaaddccffeebbaaddccffeebbaaddccffeebbaaddccffee")
 		{
        		char* key = "ddabdcfecdabdcfecdabdcfecdab";
        		//printf("The key is %s\n",key);
 		}	
 		else if (nodeMessage == msg )
 		{
        		char* key = "cdabdcfecdabdcfecdabdcfecdab";
        	//	printf("The key is %s\n",key);
 		}
 		else
 		{
			//printf("\nthe wrong key\n");
			continue;
 		}	
 
 		
    	}
    n += i;
    us = clock() - bg;
    } while (us < 3 * CLOCKS_PER_SEC);

    x = 0;

    printf("(%016lX) %.3f received CAN FD messages / Second. by running %d times\n",
        (unsigned long) x, (CLOCKS_PER_SEC * ((double) n)) / ((double) us),run);
    return 0;
}
