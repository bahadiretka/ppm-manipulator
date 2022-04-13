#include<iostream>
#include<vector>
#include<fstream>
using namespace std;
/* a generic pixel class that holds red,green and blue values
    It has neccessary setters and getters functions.
*/
class pixel{
public:
    /* Constructors */
    pixel(); // sets red, green and blues values with 0
    pixel(unsigned char red, unsigned char green, unsigned char blue); // sets RGB values with a paramaters
    /* Setters */
    void setRed(unsigned char r);
    void setGreen(unsigned char g);
    void setBlue(unsigned char b);
    /* Getters */
    const unsigned char& getRed() const{return red;}
    const unsigned char& getGreen()const{return green;}
    const unsigned char& getBlue()const{return blue;}
private:
    const static int maxValue = 255; // for all instances the RGB max value
    unsigned char red,blue,green; // RGB values
};
/* ppmImage is a class that can manipulate and read and write images in .ppm format. */
class ppmImage{
public:
    /* Constructors */
    ppmImage(); // a constructor for default values
    ppmImage(string filename);// a constructor to read a file
    ppmImage(int width, int height); // a constructor for inital width and height
    /* Setters */
    void setWidth(int width);
    void setHeight(int height);
    /* Getters */
    int getWidth() const{return width;}                         
    int getHeight() const{return height;}
    const string& getVersion()const{return version;}
    /* Neccessary functions */
    void createImage(int width, int height); // creates an image with default pixels which is 0
    int savePPM(string filename) const; // writes image data to a file
    int readPPM(string filename); // reads image data from a file
    void printDimensions(); // prints dimensions of image(width and height)
    const pixel& getPixel(int row, int column) const; // gets pixel of required row and column
    void changePixel(int row, int column, pixel value); // changes pixel values with a new value
    ppmImage singleColor(int choice) const; // creates a new object and takes single color of object with a choice then returns that new object
    int swapChannels(int choice); // Swaps RGB values with choice
    /* overloaded operators */
    const ppmImage operator+(const ppmImage& other); //  Adds two ppmImage objects pixel-by-pixel
    const ppmImage operator-(const ppmImage& other); // Subtracts one image from the other pixel-by-pixel
    int operator()(int row, int column, int rgb); //  This operator returns a reference to the pixel value
    friend ostream& operator<<(ostream& out, const ppmImage& object); // Prints image details and image data to stdout

private:
    int width; // width of image
    int height; // height of image
    string version = "P3"; // format of image (Default P3)
    int maxValue = 255; // max value of RGB
    vector<vector<pixel> > image; // the vector which holds pixels 
    void setImageSize(); // private allocater function for image data
};

int read_ppm(const string source_ppm_file_name, ppmImage& destination_object);
int write_ppm(const string destination_ppm_file_name, const ppmImage& source_object);
int swap_channels(ppmImage& image_object_to_be_modified, int swap_choice);
int test_addition(const string filename_image1, const string filename_image2, const string filename_image3);
int test_subtraction(const string filename_image1, const string filename_image2, const string filename_image3);
int test_print(const string filename_image1);
ppmImage single_color(const ppmImage& source, int color_choice);

int main(int argc, char** argv){
   string input = argv[1];
   ppmImage image; 
   ppmImage newImage;
   
   if(input.compare("1") == 0){
        // if choice number is 1
        // check the existance of the optional arguments. If they are not given, exit
        if(argc != 5)
            exit(-1);
        test_addition(argv[2],argv[3],argv[4]);
    }
   else if(input.compare("2") == 0){
        // if choice number is 2
        // check the existance of the optional arguments. If they are not given, exit
        if(argc != 5)
            exit(-1);
        test_subtraction(argv[2],argv[3],argv[4]);
    }
   else if(input.compare("3") == 0){
        // if choice number is 3
        // read ppm_file_name using function read_ppm
        // swap red and blue channels
        // write the updated data to a file named "o3.ppm". use write_ppm function.
        input = argv[2];
        read_ppm(input,image);
        swap_channels(image,2);
        write_ppm("o3.ppm",image);
   }
   else if(input.compare("4") == 0){
        // if choice number is 4
        // read ppm_file_name using function read_ppm
        // swap green and blue channels. use swap_channels function
        // write the updated data to a file named "o4.ppm". use write_ppm function.
        input = argv[2];
        read_ppm(input,image);
        swap_channels(image,3);
        write_ppm("o4.ppm",image);
   }
   else if(input.compare("5") == 0){
        // if choice number is 5
        // read ppm_file_name using function read_ppm
        // create a new object which only contains red channel data of the file read. ue single_color
        // write the data of the new object to a file named "o5.ppm". use write_ppm function.
        input = argv[2];
        read_ppm(input,image);
        newImage = single_color(image,1);
        write_ppm("o5.ppm",newImage);
   }
   else if(input.compare("6") == 0){
        // if choice number is 6
        // read ppm_file_name using function read_ppm
        // create a new object which only contains green channel data of the file read. ue
        input = argv[2];
        read_ppm(input,image);
        newImage = single_color(image,2);
        write_ppm("o6.ppm",newImage);
   }
   else if(input.compare("7") == 0){
        // write the data of the new object to a file named "o6.ppm". use write_ppm function.
        // if choice number is 7
        // read ppm_file_name using function read_ppm
        // create a new object which only contains blue channel data of the file read. ue single_color
        // write the data of the new object to a file named "o7.ppm". use write_ppm function.
        input = argv[2];
        read_ppm(input,image);
        newImage = single_color(image,3);
        write_ppm("o7.ppm",newImage);
   }
   else{
       exit(-1);
   }


    return 0;
}

int read_ppm(const string source_ppm_file_name, ppmImage& destination_object){
    return destination_object.readPPM(source_ppm_file_name);
}
int write_ppm(const string destination_ppm_file_name, const ppmImage& source_object){
    return source_object.savePPM(destination_ppm_file_name);
}
int swap_channels(ppmImage& image_object_to_be_modified, int swap_choice){
    return image_object_to_be_modified.swapChannels(swap_choice);
}
ppmImage single_color(const ppmImage& source, int color_choice){
    return source.singleColor(color_choice);
}
int test_addition(const string filename_image1, const string filename_image2, const string filename_image3){
    ppmImage image1(filename_image1);
    ppmImage image2(filename_image2);
    ppmImage image3;
    
    image3 = image1 + image2;
    return image3.savePPM(filename_image3);

}
int test_subtraction(const string filename_image1, const string filename_image2, const string filename_image3){
    ppmImage image1(filename_image1);
    ppmImage image2(filename_image2);
    ppmImage image3;
    
    image3 = image1 - image2;
    return image3.savePPM(filename_image3);
}
int test_print(const string filename_image1){
    ppmImage image(filename_image1);
    cout << image;
    return 1;
}



pixel::pixel(){
    setRed(0);
    setGreen(0);
    setBlue(0);
}
pixel::pixel(unsigned char red, unsigned char green, unsigned char blue){
    setRed(red);
    setGreen(green);
    setBlue(blue);
}
void pixel::setRed(unsigned char r){
    if(r >= 0 && r <= maxValue){
        red = r;
    }
    else{
        exit(-1);
    }
}
void pixel::setGreen(unsigned char g){
    if(g >= 0 && g <= maxValue){
        green = g;
    }
    else{
        exit(-1);
    }
}
void pixel::setBlue(unsigned char b){
    if(b >= 0 && b <= maxValue){
        blue = b;
    }
    else{
        exit(-1);
    }
}
ppmImage::ppmImage(){
    setWidth(0);
    setHeight(0);
    createImage(0,0);
}
ppmImage::ppmImage(string filename){
    readPPM(filename);
}
ppmImage::ppmImage(int width, int height){
    setWidth(width);
    setHeight(height);
    createImage(width,height);
}
void ppmImage::setImageSize(){
    image.resize(getHeight());
    for(int i=0; i < getHeight(); ++i){
        image[i].resize(getWidth());
    }
}
void ppmImage::setWidth(int width){
    if(width < 0){
        exit(-1);
    }
    this->width = width;    
}
void ppmImage::setHeight(int height){
    if(width < 0){
        exit(-1);
    }
    this->height = height; 
}
void ppmImage::printDimensions(){
    cout << "Image Width : " << getWidth() << endl;
    cout << "Image Height : " << getHeight() << endl;
}
void ppmImage::createImage(int width, int height){
    setImageSize();
    for(int i=0; i<getHeight(); ++i){
        for(int j=0; j<getWidth(); ++j){
            image[i][j] = pixel();
        }
    }
}
int ppmImage::savePPM(string filename) const{
    fstream file(filename,ios::out);
    int flag = 1;
        if(file.is_open()){
            file << version << '\n';
            file << getWidth() << ' ' << getHeight()  << '\n';
            file << maxValue << '\n';
            
            for(int i=0; i<getHeight(); ++i){
                for(int j=0; j<getWidth(); ++j){

                        file << static_cast<int>(image[i][j].getRed()) << ' ';

                        file << static_cast<int>(image[i][j].getGreen()) << ' ';

                        file << static_cast<int>(image[i][j].getBlue()) << ' ';
                }
                file << '\n';
            }
        }
        else{
            flag = 0;
            exit(-1);
        }
        file.close();
        return flag;
}
int ppmImage::readPPM(string filename){
    fstream file(filename,ios::in);
    int flag = 1;
    if(file.is_open()){
        file >> version;
        if(version != "P3"){
            flag = 0;
            exit(-1);
        }
        int inp;
        file >> inp;
        setWidth(inp);
        file >> inp;
        setHeight(inp);
        setImageSize();
        file >> inp;
        if(inp >= 0 && inp <= 255){
            maxValue = inp;
        }
        else{
            exit(-1);
        }
        for(int i=0; i<getHeight(); ++i){
            for(int j=0; j<getWidth(); ++j){
                file >> inp;
                image[i][j].setRed(inp);
                file >> inp;
                image[i][j].setGreen(inp);
                file >> inp;
                image[i][j].setBlue(inp);
            }
        }
        file.close();
    }
    else{
        flag = 0;
        exit(-1);
    }
    return flag;
}
ppmImage ppmImage::singleColor(int choice) const{
    ppmImage result(getWidth(),getHeight());
    result.setImageSize();
    if(choice == 1){
        for(int i=0; i<getHeight(); ++i){
            for(int j=0; j<getWidth(); ++j){
                result.changePixel(i,j,pixel(getPixel(i,j).getRed(),0,0)); 
            }
        }
    }
    else if(choice == 2){
        for(int i=0; i<getHeight(); ++i){
            for(int j=0; j<getWidth(); ++j){
                result.changePixel(i,j,pixel(0,getPixel(i,j).getGreen(),0)); 
            }
        }
    }
    else if(choice == 3){
        for(int i=0; i<getHeight(); ++i){
            for(int j=0; j<getWidth(); ++j){
                result.changePixel(i,j,pixel(0,0,getPixel(i,j).getBlue()));
            }
        }
    }
    else{
        exit(-1);
    }
    return result;
}
int ppmImage::swapChannels(int choice){
    int flag = 1;
    if(choice == 1){
        for(int i=0; i<getHeight(); ++i){
            for(int j=0; j<getWidth(); ++j){
                changePixel(i,j,pixel(getPixel(i,j).getGreen(),getPixel(i,j).getRed(),getPixel(i,j).getBlue()));
            }
        }
    }
    else if(choice == 2){
        for(int i=0; i<getHeight(); ++i){
            for(int j=0; j<getWidth(); ++j){
                changePixel(i,j,pixel(getPixel(i,j).getBlue(),getPixel(i,j).getGreen(),getPixel(i,j).getRed())); 
            }
        }
    }
    else if(choice == 3){
        for(int i=0; i<getHeight(); ++i){
            for(int j=0; j<getWidth(); ++j){
                changePixel(i,j,pixel(getPixel(i,j).getRed(),getPixel(i,j).getBlue(),getPixel(i,j).getGreen()));
            }
        }
    }
    else{
        flag = 0;
        exit(-1);
    }
    return flag;   
}
void ppmImage::changePixel(int row, int column, pixel value){
    if(row < getHeight() && column < getWidth()){
        image[row][column] = value;
    }
    else{
        exit(-1);
    }
}
const pixel& ppmImage::getPixel(int row, int column) const{
    if(row >= 0 && row <  getHeight() && column >= 0 && column < getWidth()){
        return image[row][column];
    }
    else{
        exit(-1);
    }
}
const ppmImage ppmImage::operator+(const ppmImage& other){
    if(this->getWidth() != other.getWidth() || this->getHeight() != other.getHeight()){
        ppmImage result;
        return result;
    }
    ppmImage result;
    result.setHeight(this->getHeight());
    result.setWidth(this->getWidth());
    result.setImageSize();
    
    int red,green,blue;
    
    for(int i=0; i<this->getHeight(); ++i){
        for(int j=0; j<this->getWidth(); ++j){
            
            red = (this->getPixel(i,j)).getRed() + other.getPixel(i,j).getRed();
            if(red > this->maxValue){
                red = maxValue;
            }
            green = (this->getPixel(i,j)).getGreen() + other.getPixel(i,j).getGreen();
            if(green > this->maxValue){
                green = maxValue;
            }
            blue = (this->getPixel(i,j)).getBlue() + other.getPixel(i,j).getBlue();
            if(blue > this-> maxValue){
                blue = maxValue;
            }
            result.changePixel(i,j,pixel(red,green,blue));
        }
    }
    return result;
}
const ppmImage ppmImage::operator-(const ppmImage& other){
    if(this->getWidth() != other.getWidth() || this->getHeight() != other.getHeight()){
        ppmImage result;
        return result;
    }
    ppmImage result;
    result.setHeight(this->getHeight());
    result.setWidth(this->getWidth());
    result.setImageSize();
    
    int red,green,blue;
    
    for(int i=0; i<this->getHeight(); ++i){
        for(int j=0; j<this->getWidth(); ++j){
            
            red = (this->getPixel(i,j)).getRed() - other.getPixel(i,j).getRed();
            if(red < 0){
                red = 0;
            }
            green = (this->getPixel(i,j)).getGreen() - other.getPixel(i,j).getGreen();
            if(green < 0){
                green = 0;
            }
            blue = (this->getPixel(i,j)).getBlue() - other.getPixel(i,j).getBlue();
            if(blue < 0){
                blue = 0;
            }
            result.changePixel(i,j,pixel(red,green,blue));
        }
    }
    return result;
}
ostream& operator<<(ostream& out, const ppmImage& object){

    out << object.getVersion() << '\n';
    out << object.getWidth() << ' ' << object.getHeight()  << '\n';
    out << object.maxValue << '\n';
            
    for(int i=0; i<object.getHeight(); ++i){
        for(int j=0; j<object.getWidth(); ++j){

            out << static_cast<int>(object.getPixel(i,j).getRed()) << ' ';

            out << static_cast<int>(object.getPixel(i,j).getGreen()) << ' ';

            out << static_cast<int>(object.getPixel(i,j).getBlue()) << ' ';
        }
        out << '\n';
    }

    return out;
}
int ppmImage::operator()(int row, int column, int rgb){
    if(row < this->getHeight() && row >= 0 && column < this->getWidth() && column >= 0 && rgb > 0 && rgb < 4){
        if(rgb == 1){
            return this->getPixel(row,column).getRed();
        }
        if(rgb == 2){
            return this->getPixel(row,column).getGreen();
        }
        if(rgb == 3){
            return this->getPixel(row,column).getGreen();
        }
    }
    return -1;
}


