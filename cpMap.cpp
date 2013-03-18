/*
  The idea is to rea in the header define if it is binary (as should).
  Then read in binary coordinates.

 */

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
using namespace std;


int main(int argc, char *argv[] )
{
  string line;
  int nLines;
  const char* qualifier = "nonuniform List<";
  const string newline = "\n";
  size_t search_term_size = strlen(qualifier);
  if ( argc != 2 ) // argc should be 2 for correct execution
    // We print argv[0] assuming it is the program name
    cout<<"usage: "<< argv[0] <<" <filename>\n";
  else {
  ifstream xcoord;
  cout << "The file to be opened is: " << argv[1] << endl;
  xcoord.open(argv[1]);
  if (xcoord.is_open(),ios::binary)
    {
      xcoord.seekg(0, ios::end);
      size_t file_size = xcoord.tellg();
      xcoord.seekg(0, ios::beg);
      string file_content;
      file_content.reserve(file_size);
      char buffer[16384];
      streamsize chars_read;
      
      while (xcoord.read(buffer, sizeof(buffer)), chars_read = xcoord.gcount())
	file_content.append(buffer, chars_read); //Read the binary into a string

      cout << "size of binary: " << file_size << endl;
      cout << "Length of string: " << file_content.length()<<endl;
      cout << "Size of char: " << sizeof(char) << endl;

      if (xcoord.eof())
	{
    	xcoord.clear(); // If the final bit is read can't seekg anymore
    	//cout << "Is the stream alive? "<< xcoord.tellg() << endl;
    	string::size_type eol1, eol2;
    	string nNodes, dumpName;
    	int listNo=0;
    	for (string::size_type offset = 0, found_at;
	       file_size > offset &&(found_at = file_content.find(qualifier, offset)) !=
		 std::string::npos;
	       offset = found_at + search_term_size)
	    {
	      cout << found_at << std::endl;
	      eol1=file_content.find_first_of(newline,found_at);
	      eol2=file_content.find_first_of(newline,eol1+1);
	      cout << eol1 << " and " << eol2 - eol1 << endl;
	      nNodes=file_content.substr(eol1+1,(eol2-eol1-1));
	      cout << "Number of Nodes: " << nNodes << endl;
	      nLines=stoi(nNodes);
	      double* coords= new double[nLines];
	      xcoord.seekg(eol2+2); // The entry start with ( thus +2
	      cout << "Starting to read coordinates from: " << xcoord.tellg() << endl;
	      // xcoord.read((char*)coords, sizeof(double)*nLines);
	      xcoord.read((char*)coords, sizeof(double)*nLines);
	      cout << "Finished reading coordinates at: " << xcoord.tellg() << endl;
	      cout << "First coordinate is: " << coords[0] <<
	    		  " and last is: " << coords[nLines-1] << endl;
	      switch(listNo){
	      case 0:
	    	  dumpName="dump1.bin";
	    	  break;
	      case 1:
	    	  dumpName="dump2.bin";
	    	  break;
	      case 2:
	      	  dumpName="dump3.bin";
	      	  break;
	      default:
	    	  cout << "Too many dumps, quitting" << endl;
	    	  return -1;
	      }
	      ofstream dump(dumpName, ios::in | ios::out | ios::binary);
	      // dump.seekg(0,ios::beg);
	      dump.write((char *)coords, sizeof(double)*nLines);
	      // for (int i=0; i < nLines; i++)
	      // 	cout << coords[i]<<endl;
	      dump.close();
	      delete[] coords;
	      listNo++;
	    }
	}

      // while ( string::npos == line.find(qualifier))
      // 	{
      // 	  getline(xcoord,line);
      // 	  cout << line << endl;
      // 	}
      // getline(xcoord,line);
      // nLines=stoi(line);
      // cout << "There are "<< nLines << " Lines" << endl;
    }
  xcoord.close();

  }
  return 0;
}
