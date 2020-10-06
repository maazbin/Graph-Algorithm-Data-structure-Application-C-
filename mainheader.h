#include <iostream>
#include <fstream>
#include <string>
#include<vector>
#include <bits/stdc++.h>
//#include <memory>
#include <utility>   // pair
#include <ctime>
#include<iomanip>


struct Node{
	
	std::string userName,password,name;
	std::vector< std::pair <std::string, Node*> > friend_list; //pair of friend name and address
	std::vector< std::pair<std::string,std::string> > chat_List; // friend(name),message.
	bool is_deleted = false;
};


class Network {

	public  :
			Network();//ctr
			Node* Login_result; //saves Login Results... user that has control of program
			bool Login_validation;
			
			/*keep index for chat_List*/
			int index_for_chat_List;//for sender
			int index_for_chat_List_of_reciever = 0;//for reciever
			
			//send or recieve message
			Node* selected_friend; //to select a friend
			std::vector<Node*>user; //contains all nodes address
			
			void data_extract_from_file();
			void data_write_in_file();
			void connect_Users(); // connecting Users		
			void people_You_May_Know();
			
			void sort_friend_list(int index);//Sorting friend_list   
			bool check_info(std::string userName,std::string password); // For login checks info if user name exists
			void delete_account();
			void Login();    
			void SigneUp(); 
			bool check_info(std::string userName); // (Over loaded function) for signe up checks info if user name exists
			bool control_for_user();  // Gives program control to user
			void see_friends(); //See all friends you have
			void search_own_friends(std::string search_string); // searching for a specific name
			void start_chat();  
			void select_friend(); //returns index of chat_List   
			void show_chat(); //showing chat done b/w users    
			void write_message();
			void send_message(std::string message);
			void Logout(); 				
			
};//Network class ends
