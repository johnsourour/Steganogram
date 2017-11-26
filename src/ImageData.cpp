#include "ImageData.h"

ImageData::ImageData()
{}

ImageData::ImageData(string name, string path, int count)
{

    this->path = path;
    this->name = name;
    string image_extension = path + name + ".JPEG";

    if(name.find(seperator)!=-1)
    {
        perror("Invalid file name\n");
    }

    // Creat hidden textfile containing image count
    string count_file =  path + ".count.txt";
    ofstream of;
    of.open(count_file);
    of<< count <<endl;
    of.close();

    // Use steganography to hide count in image
    string command = "steghide embed -ef " + count_file + " -cf " + image_extension + " -p 0 -f";
    char* command_char = new char[command.length()+1];
    strcpy(command_char, command.c_str());
    system(command_char);

    if(remove(count_file.c_str())!=0)cout<<"Couldn't delete file\n";

    ifstream in;
    in.open(image_extension);
    if(!in){
        perror("Error opening file\n");
    }
    else
    {
        char c;
        image="";
        while(in.get(c))
        {
            image+=c;
        }
        in.close();
    }
}



void ImageData::setCount(int count)
{

    string image_extension = path  + name + ".JPEG";

    string image_count = path + ".count.txt";

    // Use steganography to extract the encrypted file
    string command =  "steghide extract -sf " + image_extension + " -xf " + image_extension + " -p 0 -f";

    char* command_char = new char[command.length()+1];
    strcpy(command_char, command.c_str());
    system(command_char);

    // Use steganography to extract current count from image
    command = "steghide extract -sf " + image_extension + " -xf " + image_count + " -p 0 -f";

    char* command_char1 = new char[command.length()+1];
    strcpy(command_char1, command.c_str());
    system(command_char1);

    //set count
    ofstream of;
    of.open(image_count);
    of<<count;
    of.close();

    // Use steganography to hide count in image
    command = "steghide embed -ef " + image_count + " -cf " + image_extension + " -p 0 -f";


    char* command_char2 = new char[command.length()+1];
    strcpy(command_char2, command.c_str());
    system(command_char2);

    command = "steghide embed -ef " + image_extension + " -cf default.JPEG -sf " + image_extension + " -p 0 -f";

    char* command_char3 = new char[command.length()+1];
    strcpy(command_char3, command.c_str());
    system(command_char3);
    if(remove(image_count.c_str())!=0)cout<<"Couldn't delete file\n";

}


int ImageData::getCount()
{
    int count;

    string image_extension = path + name + ".JPEG";

    string image_count = path  + ".count.txt";

    // Use steganography to extract the encrypted file
    string command =  "steghide extract -sf " + image_extension + " -xf " + image_extension + " -p 0 -f";

    char* command_char = new char[command.length()+1];
    strcpy(command_char, command.c_str());
    system(command_char);

    // Use steganography to extract current count from image
    command = "steghide extract -sf " + image_extension + " -xf " + image_count + " -p 0 -f";

    char* command_char1 = new char[command.length()+1];
    strcpy(command_char1, command.c_str());
    system(command_char1);

    //get count
    ifstream inFile;
    inFile.open(image_count);
    inFile >> count;
    cout<<count <<endl;
    inFile.close();

    // // Use steganography to hide count in image
    // command = "steghide embed -ef " + image_count + " -cf " + image_extension + " -p 0 -f";

    // char* command_char2 = new char[command.length()+1];
    // strcpy(command_char2, command.c_str());
    // system(command_char2);

    command = "steghide embed -ef " + image_extension + " -cf default.JPEG "+ " -sf  " + image_extension + " -p 0 -f";

    char* command_char3 = new char[command.length()+1];
    strcpy(command_char3, command.c_str());
    system(command_char3);
    if(remove(image_count.c_str())!=0)cout<<"Couldn't delete file\n";

    return count;
}


bool ImageData::setName(string name)
{
    if(name.find(seperator)!=-1)
    {
        perror("Invalid file name\n");
        return false;
    }
    this->name=name;
    return true;
}
bool ImageData::setImage(string path)
{
    ifstream in;
    in.open(path);
    if(!in){
        perror("Error opening file\n");
        return false;
    }
    else
    {
        char c;
        image="";
        while(in.get(c))
        {
            image+=c;
        }
        in.close();
        return true;
    }
}
string ImageData::getImage()
{
    return image;
}
string ImageData::getName()
{
    return name;
}

bool ImageData::Flatten()
{
    flattened="";
    flattened+=name;;
    flattened+=seperator;
    flattened+=image;
    return true;
}
bool ImageData::unFlatten(string s)
{
    if(s=="")
    {
        perror("Nothing to unFlatten\n");
        return false;
    }
    stringstream ss(s);
    string tmp;
    ss>>name;
    image="";
    char c;

    while(ss.get(c))
    {
        image+=c;
    }

    image.erase(0,1);

//    string command = "steghide embed -ef ./" + name + ".txt -cf default.JPEG -sf " + name + ".JPEG -p 0 -f";

//    char* command_char = new char[command.length()+1];
//    strcpy(command_char, command.c_str());
//    system(command_char);

    return true;
}

void ImageData::embeddInDefault(){


    string image_extension = path + name + ".JPEG";

    string command = "steghide embed -ef " + image_extension + " -cf default.JPEG "+ " -sf  " + image_extension + " -p 0 -f";

    char* command_char = new char[command.length()+1];
    strcpy(command_char, command.c_str());
    system(command_char);

}


string ImageData::getPath(){
    return path;
}

void ImageData::setPath(string path){
    this->path = path;
}

ImageData::~ImageData(){}
