/*
 *  
 *  Controls a two wheel robot that can find blobs
 *
 *  Author: Phillip Okon
 *  
 */


#include <iostream>
#include <cstdlib>
#include <libplayerc++/playerc++.h>
#include <stdint.h>

int main(int argc, char *argv[])
{  
  using namespace PlayerCc;  

  // Set up proxies
  PlayerClient    robot("localhost");  
  BumperProxy     bp(&robot,0);  
  Position2dProxy pp(&robot,0);
  PlayerClient    blobfinder("localhost");
  BlobfinderProxy bf(&blobfinder,0);

  // Variables

  player_blobfinder_data_t  blobList;   // Structure holding the blobs found
  player_blobfinder_blob_t* theBlobs;   // A point to a list of blobs
  player_blobfinder_blob_t  myBlob;     // A single blob
  int x, y, area;
 
  pp.SetMotorEnable(true);


  // Control loop
  while(true) 
    {    
      double turnrate, speed;

      // Read from the proxies
      robot.Read();
      blobfinder.Read();

      // We only want to drive if the bumpers are not pressed
      if ((bp[0] == 0)&&(bp[1] == 0))
	{
	  if (bf.GetCount() > 0){

	    // Here the blobfinder has found some color blobs

	    std::cout << std::endl;
	    std::cout << bf.GetCount() << " Blobs found!" << std::endl;
	
	    for(int i = 0; i < bf.GetCount(); i++){
	      std::cout << "Id: "    << bf.GetBlob(i).id    << std::endl;
	      std::cout << "Color: " << (short)bf.GetBlob(i).color << std::endl;
	      std::cout << "Area: "  << bf.GetBlob(i).area  << std::endl;
	      std::cout << "X: "     << bf.GetBlob(i).x     << std::endl;
	      std::cout << "Y: "     << bf.GetBlob(i).y     << std::endl;
	      std::cout << std::endl;
	      if(bf.GetBlob(i).color == 0){
		if(bf.GetBlob(i).area > area){
		  area = bf.GetBlob(i).area;
	   	  x = bf.GetBlob(i).x;
		  y = bf.GetBlob(i).y;
              }
	    }
	  }
	  else
	    {
	      // Here the blobfinder doesn;t see any blobs

	    }
	}
      
      // If bumpers are pressed, do nothing.

      else{
	speed = -.1;
	turnrate = 0;
      }
      if(bf.GetCount() > 0){
	if(!(pp.GetXPos() == x)){
	  while(!pp.GetXPos() == x){
	    robot.read();
	    if(pp.GetXPos() > x){
	      while(!pp.GetYaw() == 180){
		robot.read();
		speed = 0;
	 	turnrate = dtor(1);
		pp.SetSpeed(speed,turnrate);
	      }	
	    }
	    if(pp.GetXPos() < x){
	      while(!pp.GetYaw() == 0){
		robot.read();
		speed = 0;
	 	turnrate = dtor(1);
		pp.SetSpeed(speed,turnrate);
	      }	
	    }	
	    speed = .1;
	    turnrate = 0;
	    pp.SetSpeed(speed,turnrate);
	  }
	if(!(pp.GetYPos() == y)){
	  while(!pp.GetXPos() == x){
	    robot.read();
	    if(pp.GetYPos() > y){
	      while(!pp.GetYaw() = -90){
		robot.read();
		speed = 0;
	 	turnrate = dtor(1);
		pp.SetSpeed(speed,turnrate);
	      }	
	    }
	    if(pp.GetYPos() < y){
	      while(!pp.GetYaw() == 90){
		robot.read();
		speed = 0;
	 	turnrate = dtor(1);
		pp.SetSpeed(speed,turnrate);
	      }	
	    }	
	    speed = .1;
	    turnrate = 0;
	    pp.SetSpeed(speed,turnrate);
	  }
	}
    
      std::cout << "Speed: " << speed << std::endl;      
      std::cout << "Turn rate: " << turnrate << std::endl << std::endl;
	speed = 0 ;
	turnrate = dtor(1);
	std::cout << pp.GetYaw() << std::endl;
	pp.SetSpeed(speed,turnrate);  
    } // end of while(true) loop
}


