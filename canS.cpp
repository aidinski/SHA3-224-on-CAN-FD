#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <stdio.h>
#include <pstream.h>


using namespace std;


int main () 
{
  remove("/home/pi/Projects/masterProject/messageCanWithKey.bin");
  remove("/home/pi/Projects/masterProject/messageCanWithDigest.bin");
  char * buffer;
  char * bufferCan;
  char * message;
  int digest;
  int lengthBuffer, lengthBufferCan;
  std::string fileName1 = "key.bin";
  std::ifstream is (fileName1.c_str(), ios::app |ios::out | ios::binary );
  if (is) {
    // get length of file:
    is.seekg (0, is.end);
    lengthBuffer = is.tellg();
    is.seekg (0, is.beg);

    buffer = new char [lengthBuffer];
    std::cout << "Reading " << lengthBuffer << " bytes long key\n";
    // read data as a block:
    is.read (buffer,lengthBuffer);

    if (is)
      std::cout << "key read successfully.\n";
    else
      std::cout << "error: only " << is.gcount() << " could be read.";
    is.close();
    }
    
  std::string fileName2 = "canMessage.bin";
  std::ifstream canMessage (fileName2.c_str(), ios::app |ios::out | ios::binary );
  if (canMessage) {
    // get length of file:
    canMessage.seekg (0, canMessage.end);
    lengthBufferCan = canMessage.tellg();
    canMessage.seekg (0, canMessage.beg);

    bufferCan = new char [lengthBufferCan];

    std::cout << "Reading " << lengthBufferCan << " bytes long key\n";
    // read data as a block:
    canMessage.read (bufferCan,lengthBufferCan);

    if (canMessage)
      std::cout << "CAN message read successfully.\n";
    else
      std::cout << "error: only " << canMessage.gcount() << " could be read.";
    canMessage.close();
    }
    
    std::string fileName3 = "messageCanWithKey.bin";
    std::ofstream messageCanWithKey (fileName3.c_str(), ios::app | ios::in | ios::binary );
    if (messageCanWithKey)
    {
    messageCanWithKey.write (buffer,lengthBuffer);
    messageCanWithKey.write (bufferCan,lengthBufferCan);
    messageCanWithKey.close();
    }

    /*delete[] bufferCan;*/
    delete[] buffer;

    /*std::stringstream stream;
    stream << "sha3-224sum"
	   << " "
           << "messageCanWithKey.bin";
    system (stream.str().c_str());
*/    

   
  FILE *fp;
  char buff[128];
  if(!(fp = popen("sha3-224sum --binary messageCanWithKey.bin", "r")))
  {
  	return 1;
  }
  while(fgets(buff, sizeof(buff), fp)!=NULL)
  {
    std::string fileName4 = "messageCanWithDigest.bin";
    std::ofstream messageCanWithDigest (fileName4.c_str(), ios::app | ios::in | ios::binary );
    if (messageCanWithDigest)
    {
     messageCanWithDigest.write (bufferCan, lengthBufferCan);
     messageCanWithDigest.write (buff, 28 );
     
     messageCanWithDigest.close();
    }

  }
  fclose(fp);


  FILE *canS;
  if(!(canS = popen("cansend vcan0 213##311bb3addccffeebbaaddccffeebbaaddccffeebbaaddccffeebbaaddccffeebbaaddccffee416c654f1d50dbb240a4f30ee5d9aa11ddfa4baff682cce2721c23", "r")))
  {
        return 1;
  }
  fclose(canS);

//Reciever
/*
  FILE *canR;
  if(!(canS = popen("candump vcan0", "r")))
  {
        return 1;
  }
  printf("%s\n", &canR);
  fflush(stdout);
  fclose(canR);
*/
  return 0;
}
