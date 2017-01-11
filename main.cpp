/*It's a projectile simulator project when user enters inputs for a ball which we'll track its way after being thrown with 
an initial speed,angle, and from a certain height */
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <cstdio>
#include <conio.h>
using namespace std;
double Mass , intspeed , angle , height , diameter , frco , resco;
float x , y , vx , vy , ax , ay , ux , uy , deltavx , deltavy , deltax , deltay ,time;
float g = 9.81, pi = 3.14 ;
//-----------------------------------------------------------------------------------------------------------
 void Load(){
ifstream loadfile;
loadfile.open("projectilesim.txt");
while(!loadfile.eof()){
    loadfile >> Mass;
    loadfile >> diameter;
    loadfile >> frco;
    loadfile >> resco;
}
loadfile.close();
}
//----------------------------------------------------------------------------------------------------------
void Save(){
ofstream savefile;
savefile.open("projectilesim.txt");
ofstream file("projectilesim.txt");
    if(file.is_open()){
  file <<  Mass << endl;
  file << diameter << endl;
  file << resco << endl;
  file << frco << endl;
  file.close();
  }
    else
    cout << "error opening the file " << endl;

}
//----------------------------------------------------------------------------------------------------------
void Addsave(){
cout << "please, Enter the mass of the ball " << endl;
cin >> Mass;
cout << "please, Enter ball diameter " << endl;
cin >> diameter;
cout << "please, Enter the coefficient of restitution of the ball and the ground" << endl;
cin >> resco;
cout << "please, Enter the coefficient of friction " << endl;
cin >> frco;
Save();
}
//------------------------------------------------------------------------------------------------------------
void keyboard(){
   bool i=true;
   while(i){
  if(kbhit()){
    int j = getch();
    if(j==224){  // 224 for using arrows
    int k = getch();
        if(k==72){ // to increase angle using up arrow
            angle +=1;
            cout << angle << endl;
        }
        else if (k==80){  // to decrease angle using down arrow
            angle -= 1;
            cout << angle << endl;
        }
    }
    else if (j==32){  //to increase initial speed using space bar
        intspeed +=1;
        cout << intspeed << endl;
    }
    else if (j ==27){   // to decrease initial speed using escape button
        intspeed -=1;
        cout << intspeed << endl;
    }
    else if (j==13){ // to finish the loop after adjusting inputs by user
        i =false;
    }

  }

}
}
//-------------------------------------------------------------------------------------------------------------
void simulate(){
    int w;
    cout << "enter 1 to insert inputs by hand or 2 to adjust inputs using arrows in keyboard" << endl;
    cin >> w;
    if (w==1){
        cout << "enter initial speed " << endl;
        cin >> intspeed;
        cout << "enter throwing angle " << endl;
        cin >> angle;
        cout << "enter height " << endl;
        cin >> height;
    }
    else if (w==2) {
        keyboard();
    }
     vx = intspeed*cos(angle*(pi/180)); //initial speed in x direction
     vy = intspeed*sin(angle*(pi/180)); // initial speed in y direction
     time = 0;
     float x=0; //initial value for x
     float y=height+ (diameter/2); //initial value for y
     ofstream excelfile;
     excelfile.open("projectilesim.csv"); //creating excel file to tabulate data
     while(vx > 0.00001){
      ax = (- 0.8 * vx) / Mass;
      ay = (- (Mass *  g) - (0.8 * vy )) / Mass;
      deltavx = ax * 0.1;
      deltavy =  ay * 0.1;
      vx += deltavx;
      vy += deltavy;
      deltax = vx * 0.1;
      deltay = vy * 0.1;
      time += 0.1;
      x += deltax;
      y += deltay;
      excelfile << x << "," << y << "," << time << endl;
     if (y <= diameter/2)
        {
            vy = - resco * uy;
            vx = ux + frco*(resco - 1)*ux;
            y=diameter /2;
        }
}
        excelfile.close();
}
//-------------------------------------------------------------------------------------------------------------
int main(){
    int x;
    cout << "                    Welcome to the Projectile Simulator \n" << endl;
    cout << "         1* Load parameters" << endl;
    cout << "         2* Enter values of parameters and values will be saved " << endl;
    cout << "         3* Do Simulation" << endl;
    cin >> x;
    if (x>0 && x<4){
        switch(x){
    case 1:
      Load();
      break;
    case 2:
      Addsave();
      break;
    case 3:
      simulate();
      break;
        }
    }
    else {
        return 1;
    }

return 0;

}
