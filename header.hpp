#include "mainheader.h"
#include <stdio.h>
/*NOTE ..........................Calling std::cin.ignore() before calling getline() because it was not working without it

*/


Network::Network(){ // ctr	
	index_for_chat_List = -1;//keep index for chat_List			
}
	//message
//void send_message(chat my_chat){
//}


	//connecting users
void Network::connect_Users(){
					
	if(user.empty())
		return;
	else{

		for( int i=0; i<user.size(); i++){ // loop for traversal in the main vector contains all users
		
			for(int j = 0;j<user[i]->friend_list.size();++j){	//traversing in a specific user's friend Network pair_for_friendName_address extrctd frm file
				for(int k=0; k<user.size(); k++){//filling friend list of a user ...finding friends in main user vector acc to 2nd for loop
					if(user[i]->friend_list[j].first==user[k]->name){//string name == friend's Name
						user[i]->friend_list[j].second=user[k];
						//user[k]->Friend_Address.push_back(user[i]);
						break;
					}
				}
			}
		}	
	}
}
//Sorting friend_list
void Network::sort_friend_list(int index){
		//sorting func
	std::sort(user[index]->friend_list.begin(), user[index]->friend_list.end());		
}


/*------------Login------------------------------------------------------------------------------
All Functions working  under control_for_user() after Login()...
*/

/*Function returns bool for validy of info and Node* for user address*/
//checking info entered

bool Network::check_info(std::string userName,std::string password){
	for(int i =0;i<user.size();++i ){
		if((user[i]->userName==userName && user[i]->password==password) && user[i]->is_deleted != true){
			Login_result = user[i]; //stores address of the user to login
			return true; // user found
		}
	}
	Login_result = NULL;
	return false;//user not found
}

void Network::delete_account(){
	Login_result->is_deleted = true;
	std::cout<<Login_result->name<<" , Your account has been deleted"<<std::endl;
	Login_result=NULL;
}

void Network::Logout(){
	Login_result=NULL;
}


//takes 2 strings
void Network::Login(){
	std::string userName, password, name;
	
	
	std::cout<<"Enter User name"<<std::endl;
	//std::cin.ignore();
	std::cin>>userName;
	
	std::cout<<"Enter password"<<std::endl;
	std::cin.ignore();
	std::getline(std::cin,password);
	
	if(!(check_info(userName,password))){
		std::cout<<"\n\nInvalid info"<<std::endl;
		Login_validation = false; //invalid information
	}
	else{
	std::cout<<"\n\nWelcom Bea Head "<<Login_result->name<<" !!!!"<<std::endl;	
	Login_validation = true;
	}
	
}


//checking info entered for signing up

bool Network::check_info(std::string userName){
	for(int i =0;i<user.size();++i ){
		if(user[i]->userName==userName && user[i]->is_deleted!=true)
			return false; // userName used before
	}
	
	return true;//userName not used before
}

							/*******************SigneUp*******************/
//takes 2 strings
void Network::SigneUp(){
	
	std::string userName, password, name;
	std::cout<<"Enter User name"<<std::endl;
	std::cin>>userName;
	std::cout<<"Enter password"<<std::endl;
	std::cin>>password;
	std::cout<<"Enter name"<<std::endl;
	std::cin.ignore();
	std::getline(std::cin,name);
	//userName is not used before
	if(!(check_info(userName)))
		std::cout<<userName<<" already used , try another"<<std::endl;
	else{
		std::cout<<name<<" , you have signed up"<<std::endl;
		Node* node = new Node; //creating new node for the new user
		node->name=name;
		node->userName=userName;
		node->password=password;
		user.push_back(node);
	}
	
}


/*giving control to user*/
bool Network::control_for_user(){
	if(!Login_validation)
		return false; //No controll is given
	char option;
	while(1){
		std::cout<<"----------------------OPTIONS-----------------------------"<<std::endl;
		std::cout<<"'s' for see friends\n'c' for start chat\n'p' for people You May Know\n'l' for Logout\n'd' for delete account"<<std::endl;
		
		
		std::cin>>option;
		
		switch(option){
			case 's' :see_friends();
			break;
			case 'c' :start_chat();
			break;
			case 'p' :people_You_May_Know();
			break;
			case 'l' :Logout();
			break;
			case 'd' :delete_account();
			break;
		}
		if(Login_result==NULL) //if logged out
		{
			return false;
		}

	}
}	


void Network::see_friends(){
	if(Login_result->friend_list.empty()){
		std::cout<<"\nYour Friend List is empty"<<std::endl;
		return;
	}
	std::cout<<"\nYour Friend List"<<std::endl;
	for(int i =0 ; i< Login_result->friend_list.size()-1;++i){
		if(Login_result->friend_list[i].second->is_deleted ==true)
			continue;
		std::cout<<Login_result->friend_list[i].first<<std::endl;
	}
}

void Network::people_You_May_Know(){
	std::vector<std::string> namesOfFriend;
	bool is_friend = true;
	Node* temp1 =NULL;
	Node* temp2 =NULL;
	std::cout<<"\nPeople you may know"<<std::endl;
	for( int i=0; i<Login_result->friend_list.size(); i++){ // loop for traversal in the in the friend list of user
		temp1 = Login_result->friend_list[i].second; //friend of friend
		if(temp1->friend_list[i].second->is_deleted ==true)
			continue;
		for(int j = 0;j<temp1->friend_list.size();++j){	//traversing in a friend's friend list
		temp2=temp1->friend_list[j].second; //friend of friend of friend
		if(temp2->friend_list[i].second->is_deleted ==true)
			continue;
			for(int k=0; k<temp2->friend_list.size(); k++){//traversing in a  friend list  of  2nd for loop
			//checking for mutual friends and deleted user
				if((temp2->friend_list[k].second==Login_result ||temp2->userName ==Login_result->userName) || temp2->friend_list[k].second->is_deleted ==true){
					
					is_friend = false;
					break;
				}
				else
					is_friend = true;
			}
			namesOfFriend.push_back(temp2->name);
			if(is_friend){
				for(int l = 0 ;l<namesOfFriend.size();++l)
				if(namesOfFriend[l]==temp2->name)
					break;
				std::cout<<temp2->name<<std::endl;
			}
		}
	}
	
}




/*chat */
void Network::start_chat(){
	std::cout<<"\n---------This is your chat board---------"<<std::endl;
	std::cout<<"\n (a) to select a friend you want to chat with\n(b) to see your friends\n(m) to go to main menue"<<std::endl;
	
	
	char option;
	std::cin>>option;
	switch(option){
		case 'a' :select_friend(); //sets selected_friend
		break;
		case 'b' : see_friends();
		break;
		case 'm' :return;
		break;
	}
	
	if(selected_friend == NULL) 
		return;
	
	//here we have found ourdesired friend to start chat with
	else{ 
		while(option !='e'){
			std::cout<<" write message to "<<selected_friend->name<<std::endl;
			show_chat();// it shows the chat bw them
			write_message(); // it has a string to be sent 
			std::cout<<" press 'e' to end chat or 'y' to continue"<<std::endl;
			std::cin>>option;
		}
	}
}


//select a friend you wanna chat with
void Network::select_friend(){
	
	std::string search_string;
	std::cout<<"\nwrite a friend's name you want to chat with"<<std::endl;
	std::cin.ignore();
	std::getline (std::cin, search_string);
	//search_string = "Maaz Bin Mustaqeem";
	std::cout<<search_string<<std::endl;
	for(int i =0 ; i< Login_result->friend_list.size();++i){ //!!!!!!!!!!!!!!!!!!!change it name to userName
	
			if(search_string==Login_result->friend_list[i].first){
				selected_friend=Login_result->friend_list[i].second;//stores address of the friend to selected_friend
				return;
			}	
			
	}
	std::cout<<"No such friend !!"<<std::endl;  // show this message 
	selected_friend=NULL;
}


//showing chat done b/w users
void Network::show_chat(){
	for(int i =0;i<Login_result->chat_List.size();++i ){
		if(Login_result->chat_List[i].first==selected_friend->name){//if chat is done bw them
			std::cout<<Login_result->chat_List[i].second<<std::endl;
			index_for_chat_List = i;//keep index for chat_List
			return;
		}
	}
	
	index_for_chat_List = -1; //if no previous chat
}

//write message
void Network::write_message(){
	// current date/time based on current system
   time_t now = time(0);
   
   // convert now to string form
   char* dt = ctime(&now);
	std::string message; //to store message
	std::string charec; //to store charecters
	charec  = "\n\n\n";
	charec  +=dt;
	charec  +=" "+ Login_result->name+" says : \n\n";
	std::cin.ignore();
	std::getline (std::cin, message);
	message =charec + message; 
	send_message(message); // it finds and sends message
	
}




void Network::send_message(std::string message){
	//creating a chat if no message sent
	if(index_for_chat_List<0){
	//	std::cout<<"\tchat is created"<<std::endl;
		std::pair<std::string,std::string > pair_to_create_a_new_chat;
		
		pair_to_create_a_new_chat.first = selected_friend->name;
		pair_to_create_a_new_chat.second = message;
		Login_result->chat_List.push_back(pair_to_create_a_new_chat); //create a new index..stores userName of friend on .first and message on .second
		index_for_chat_List =(Login_result->chat_List.size()-1); //saving the last index
		//for reciever
		pair_to_create_a_new_chat.first = Login_result->name;
		selected_friend->chat_List.push_back(pair_to_create_a_new_chat); //create a new index..stores userName of friend on .first and message on .second
		index_for_chat_List_of_reciever = (selected_friend->chat_List.size()-1);//saving last index
		//show_chat(); //to keep index
		
	}
	else{
		
	
		Login_result->chat_List[index_for_chat_List].first=selected_friend->name; //stores userName of friend
		Login_result->chat_List[index_for_chat_List].second += message; //stores message
		selected_friend->chat_List[index_for_chat_List_of_reciever].first=Login_result->name; //stores userName of friend
		selected_friend->chat_List[index_for_chat_List_of_reciever].second += message; //stores message
	}
}






 //for own friends in friend list
void Network::search_own_friends(std::string search_string){
	std::string holder_for_search_string;
	int count_result=0;
	std::cout<<"\n\n--------Search called------------"<<std::endl;
	
	for(int i =0 ; i< Login_result->friend_list.size();++i){
		holder_for_search_string[0]='\0';
		for(int j= 0; j<search_string.length();++j){
			if(search_string[j]==Login_result->friend_list[i].first[j])
				holder_for_search_string[j]=search_string[j];
		}
		if(holder_for_search_string[0]!='\0'){
			std::cout<<Login_result->friend_list[i].first<<std::endl;
			count_result++;
		}	
	}
	
	std::cout<<count_result<<" searh results for ' "<<search_string<<" '"<<std::endl;
}


/*Data extraction from file*/
void Network::data_extract_from_file(){
	
	std::pair<std::string, Node*> pair_for_friendName_address; //pair for name and address 
	
	Node* node=NULL; //Node pointer to create nodes
	std::string dataRead; // to read data from file
	std::ifstream myfile("A2.csv");
	std::getline( myfile,dataRead);
	
	char c; // To maintain \n check
	
	while(!( myfile.eof() )){ //extracting data from file and putting to correct positions
		myfile.get(c);
		if( c=='!' ){
			node = new Node;
			node->is_deleted = true;
			std::getline( myfile, node->userName, ',' ); //user name
			std::getline( myfile, node->password, ',' ); //password
			std::getline( myfile, node->name, ',' ); //name
		}	
		else{	
			node = new Node;
			std::getline( myfile, node->userName, ',' ); //user name
			node->userName =c+node->userName; 
			std::getline( myfile, node->password, ',' ); //password
			std::getline( myfile, node->name, ',' ); //name
		}
		//loop for loading friends
		myfile.get(c); 
		while(c!='\n'){
			std::getline( myfile, dataRead, '*' );
			dataRead = c+dataRead;
			pair_for_friendName_address.first = dataRead; // stores friend's name on first in a local var where .second is still vacant
			node->friend_list.push_back(pair_for_friendName_address); //stores local var in friend Network (only name strings)
			myfile.get(c);
		}
		//pair_for_friendName_address.second = NULL; // 
		node->friend_list.push_back(pair_for_friendName_address); //NULL to last index
		
		user.push_back(node); // saving all nodes dynamicly
		
	}
	
}



void Network::data_write_in_file(){
	

	std::string dataWrite="User name,Password,Name,Friend List\n"; // to read data from file
	std::ofstream myfile("A2.csv");
	std::ofstream append_message;  // Create Object of Ofstream
	myfile<<dataWrite;
	
	int i = 0;
	int j = 0;
	while(i<user.size()-1){ //dumping in file
		if(user[i]->is_deleted){ //if deleted
			dataWrite="!"+user[i]->userName+","; //user name
			myfile<<dataWrite;
			dataWrite=user[i]->password+","; //user name
			myfile<<dataWrite;
			dataWrite=user[i]->name+","; //user name
			myfile<<dataWrite;
		}
		else{
			dataWrite=user[i]->userName+","; //user name
			myfile<<dataWrite;
			dataWrite=user[i]->password+","; //user name
			myfile<<dataWrite;
			dataWrite=user[i]->name+","; //user name
			myfile<<dataWrite;
			
		}
		//loop for dumping message
			dataWrite=user[i]->name+".txt";
			append_message.open (dataWrite,std::ios::app); // write mode
			while(j<user[i]->chat_List.size()){
				dataWrite=user[i]->chat_List[j].first+"*"; //dumping names
				append_message<<dataWrite;
				dataWrite=user[i]->chat_List[j].second+"*\n"; //dumping message
				append_message<<dataWrite;
				j++;
			}
			append_message.close();
			j=0;
		//loop for loading friends
		while(j<user[i]->friend_list.size()-1){
//			std::cout<<user[i]->friend_list[j].first<<std::endl;
			dataWrite=user[i]->friend_list[j].first+"*"; //dumping names
			myfile<<dataWrite;
			j++;
		}
		 j = 0;
		myfile<<"\n";
		i++;
	}
	
}
