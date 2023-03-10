#include"game.h"

int who_won=555;//white won=1;blackwon=2;
bool time_to_send_sever=false; 
bool to_trigger_event=false;
//operator overloading for passing packet in array:
sf::Packet& operator <<(sf::Packet& packet, const int(&arr)[8][8])
{
	
    for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		 packet<<arr[i][j];
	}
	return packet;
}
sf::Packet& operator >>(sf::Packet& packet, int(&arr)[8][8])
{
	
    for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		 packet>>arr[i][j];
	}
	return packet;
}



void game::main_game(int a)
{
	int game_array[8][8] = {
	  { -1,-2,-3,-4,-5,-3,-2,-1 },
	  { -6,-6,-6,-6,-6,-6,-6,-6 },
	  {  0, 0, 0, 0, 0, 0, 0, 0 },
	  {  0, 0, 0, 0, 0, 0, 0, 0 },
	  {  0, 0, 0, 0, 0, 0, 0, 0 },
	  {  0, 0, 0, 0, 0, 0, 0, 0 },
	  {  6, 6, 6, 6, 6, 6, 6, 6 },
	  {  1, 2, 3, 4, 5, 3, 2, 1 }
	};

	// int game_array[8][8] = {
	//   { 1,2,3,4,5,3,2,1 },
	//   { 6,6,6,6,6,6,6,6 },
	//   {  0, 0, 0, 0, 0, 0, 0, 0 },
	//   {  0, 0, 0, 0, 0, 0, 0, 0 },
	//   {  0, 0, 0, 0, 0, 0, 0, 0 },
	//   {  0, 0, 0, 0, 0, 0, 0, 0 },
	//   {  -6, -6, -6, -6, -6, -6, -6, -6 },
	//   {  -1, -2, -3, -4, -5, -3, -2, -1 }
	// };

	// int game_array[8][8]={
	//   { -1,-2,-3,-4,-5,-3,0,-1 },
	//   { -6,6,-6,-6,-6,-6,6,-6 },
	//   {  0, 0, 0, 0, 0, 0, 0, 0 },
	//   {  0, 0, 0, 0, 0, 0, 0, 0 },
	//   {  0, 0, -6, 4, 0, 0, 0, 0},
	//   {  0, 0, 0, 0, 0, 0, 0, 0 },
	//   {  -1, -6, 0, 0, 6, 0,-6, 6 },
	//   {  1, 0, 3, 4, 5, 0, 0, 1 }
	// };

	RectangleShape square[8][8];   //for board
	Texture tex;       //for pieces img
	Sprite sp;         //for displaying those images


	RenderWindow window(VideoMode(Added_width+800, 640), "THE BOARD", Style::Close | Style::Titlebar);
	//window.setPosition(sf::Vector2i(10, 10));
	window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width/2-400,
                                  sf::VideoMode::getDesktopMode().height / 2 -360));

	window.setFramerateLimit(60); 

	chessboard chessboard1;
	
    //initial clear:
	window.clear();
	
	//initial drawing the board in starting position:
	chessboard1.draw_baseboard(window, square);
	chessboard1.set_piece_to_board(window, game_array,square, tex, sp);

	//for handling events: EventHandler class
	EventHandler eventhandler1;
	eventhandler1.gameleftsidescreen(window,0,0);
	eventhandler1.gamerightsidescreen(window);
	//display the initial postion board:
	window.display();


	//initilizing other variables:
	
	

	//main game loop:
	while (window.isOpen()) {
		
		//Event handler section:
		
		
		eventhandler1.event_function(window,game_array,square,current_side_to_play);

		

	}

}//end of main_game function:


void game::network_game(int a)
{

    sf::Time t1 = sf::seconds(5.0f); //to set time limit for connecting to the sever:
    sf::TcpSocket socket;
    sf::Socket::Status status = socket.connect("192.168.184.21",53000);
    if (status != sf::Socket::Done) //if connection fails:
    {
        // error...
        std::cout<<"Connection failed, status: "<<status<<endl;
        //std::cout<<"COnnection failed, status: "<<WSAGetLastError()<<std::endl;
        std::cout << "Connection failed" << endl;
            //socket.disconnect();
    }
    else //if connection succeed:
    {
        sf::Packet packet1;
        socket.receive(packet1);
        int game_array[8][8];
        packet1>>game_array>>white_up_or_down>>my_turn;//no need to send "black_up_or_down" since it's complement of "white_up_or_down" 
        black_up_or_down=!white_up_or_down;
        packet1.clear();     
        time_to_send_sever=false;  

        RectangleShape square[8][8];   //for board
	    Texture tex;       //for pieces img
	    Sprite sp;         //for displaying those images
        RenderWindow window(VideoMode(Added_width+800, 640), "THE BOARD", Style::Close | Style::Titlebar);
	    window.setFramerateLimit(60); 
        chessboard chessboard1;
        //initial clear:
	    window.clear();
	    //initial drawing the board in starting position:
	    chessboard1.draw_baseboard(window, square);
	    chessboard1.set_piece_to_board(window, game_array,square, tex, sp);
        //for handling events: EventHandler class
	    EventHandler eventhandler1;
	    eventhandler1.gameleftsidescreen(window,0,0);
	    eventhandler1.gamerightsidescreen(window);
	    //display the initial postion board:
	    window.display();
        
		
        bool request_connection;
		bool response_connection=false;
    
	//main game loop:
	while (window.isOpen()) 
	{
		

	    packet1.clear();
        socket.receive(packet1);
        packet1>>request_connection>>who_won;
        packet1.clear();  

		

		

		if(request_connection==true)
	   {
		//cout<<"request_connection received: "<<endl;
	    packet1.clear();
        socket.receive(packet1);
        packet1>>game_array>>my_turn>>current_side_to_play;
		if((who_won==1)||(who_won==2))
		{

		

		socket.disconnect();
		window.close();
		check check1;
		check1.game_over_window();
		

		}
		EventHandler eventhandler1;
		eventhandler1.function_after_getting_position(window,game_array,square,current_side_to_play,11,12);
		
		packet1.clear();  
        request_connection=false;
		
	   }

		if(time_to_send_sever==true)
		{
		//cout<<"time_tosend_sever invoked: "<<endl;
		response_connection=true;
		time_to_send_sever=false;
		my_turn=false;
		}

		packet1.clear();
		packet1<<response_connection<<who_won;
		socket.send(packet1);
		packet1.clear();
	  

		if(response_connection==true)
		{
			//cout<<"response_connection sent: "<<endl;
		packet1.clear();
		packet1<<game_array;
		socket.send(packet1);
		packet1.clear();
		response_connection=false;
		}
		
		
		 
            
		
        
//cout<<"2 :";
     
		//cout<<"3 :";
		
		eventhandler1.event_function(window,game_array,square,current_side_to_play);

		

		

		}//end of while loop: "window.isOpen()":

    }

    

}//end of network_game function: