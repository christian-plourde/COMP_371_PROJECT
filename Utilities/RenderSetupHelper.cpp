#include "RenderSetupHelper.h"

RenderSetupHelper::RenderSetupHelper()
{
    save_image = false;
    cast_shadows = true;
}

RenderSetupHelper::~RenderSetupHelper()
{

}

void RenderSetupHelper::setup()
{
    //method to allow the user to set the path to the scene file and the image file and if he wishes to
    //save the image file on render
    std::cout << "Please enter the path to the directory where the scene files are stored:" << std::endl;
    std::getline(std::cin, scene_directory);
    std::cout << "Please enter the name of the scene file to render:" << std::endl;
    std::getline(std::cin, scene_filepath);
    std::cout << "The path to the scene file is: " << scene_directory << "/" << scene_filepath << std::endl;
    //next we should ask the user if he/she wants to save the image
    std::cout << "Please indicate if you would like a copy of the image to be saved to a file (Y/N):" << std::endl;
    std::string answer;
    std::getline(std::cin, answer);
    if(answer == "Y")
        save_image = true;

    if(save_image)
    {
        //if the user wants to save, he needs to indicate where to save
        std::cout << "Please enter the name of the directory where you would like the image to be saved:" << std::endl;
        std::getline(std::cin, image_directory);
        std::cout << "Please enter the name of the file that will be saved:" << std::endl;
        std::getline(std::cin, image_filepath);
    }

    //the final question is whether or not the user wants to cast shadows
    std::cout << "Would you like the scene to be rendered with shadows (Y/N):" << std::endl;
    std::getline(std::cin, answer);
    if(answer == "Y")
        cast_shadows = true;
    else
        cast_shadows = false;
}

std::ostream& operator<<(std::ostream& os, RenderSetupHelper& render_setup)
{
    os << "Image File Path: " << render_setup.image_filepath << std::endl <<
    "Scene File Path: " << render_setup.image_filepath;
    return os;
}

std::string RenderSetupHelper::getSceneFilePath()
{
    return scene_directory + "/" + scene_filepath;
}

std::string RenderSetupHelper::getImageFilePath()
{
    return image_directory + "/" + image_filepath;
}
