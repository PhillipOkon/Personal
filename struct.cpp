//Sample Code creating a Struct and interacting with it
#include <iostream>
#include <cmath>

struct Rectangle {
    float length, width;
    float epsilon = 0.01f;

	void setLength(float len){
		length = len;
	}
	
	void setWidth(float wid){
		width = wid;
	}

	float perimeter(){
		return  (length * 2) + (width * 2);
	}

	float area(){
		return length * width;
	}
	
	void show(){
		std::cout<< "length: " << length << " width: " << width << std::endl;
	}

	int sameArea(Rectangle rec){
		if(fabs((length * width)- rec.area()) <= epsilon) {
			return 1;
		}
		else{
			return 0;
		} 
	} 
} ;

int main(){
    Rectangle rec1, rec2;
    rec1.length = 5;
    rec1.width = 2;
    rec2.setLength(5);
    rec2.setWidth(18.9);

    rec1.show();
    std::cout << "Perimeter: " << rec1.perimeter() << " Area: " << rec1.area() << std::endl;

    rec2.show();
    std::cout << "Perimeter: " << rec2.perimeter() << " Area: " << rec2.area() << std::endl;

    if(rec1.sameArea(rec2) >0){
        std::cout << "They have the same area" << std::endl << std::endl;
    }
    else{
        std::cout << "They don't have the same area" << std::endl << std::endl;
    }

    rec1.setLength(15);
    rec1.setWidth (6.3);

    rec1.show();
    std::cout << "Perimeter: " << rec1.perimeter() << " Area: " << rec1.area() << std::endl;

    rec2.show();
    std::cout << "Perimeter: " << rec2.perimeter() << " Area: " << rec2.area() << std::endl;

    if(rec1.sameArea(rec2) >0){
        std::cout << "They have the same area" << std::endl << std::endl;
    }
    else{
        std::cout << "They don't have the same area" << std::endl << std::endl;
    }

    return 0;
}
