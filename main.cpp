/*Social media in a nutshell
	By
Maaz Bin Mustaqeem	

*/
#include "header.hpp"




int main ()
{	
	
	Network N1; //crearing object of Network
	N1.data_extract_from_file(); //extracting data from file
	N1.connect_Users(); // creating a network
	
	//Sorting friend_list
	//for (int i = 0; i < N1.user.size()-1; i++){
		//N1.sort_friend_list(i);
	//}
	char option;
	while(1){
		std::cout<<"(l) for Login\n(s) for signe up\n(e) to exit"<<std::endl;
		std::cin>>option;
		switch(option){
			case 'l' : N1.Login();
					   N1.control_for_user();
			break;
			
			case 's':N1.SigneUp();
			break;
			
			case 'e' :N1.data_write_in_file();
					  return 0;		
		}
	
	}
}
