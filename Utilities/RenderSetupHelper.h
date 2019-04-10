#ifndef COMP_371_PROJECT_RENDERSETUPHELPER_H
#define COMP_371_PROJECT_RENDERSETUPHELPER_H

#include <string>
#include <iostream>

class RenderSetupHelper
{
    //this class initializes all of the things we need to know in order to render by accepting user input from
    //the command line. This includes selecting which scene file to render, whether or not to draw shadows, and whether
    //or not to save the image and where to save it.

    public:
        RenderSetupHelper();
        ~RenderSetupHelper();
        void setup();
        friend std::ostream& operator<<(std::ostream& os, RenderSetupHelper& render_setup);
        std::string getSceneFilePath();
        std::string getImageFilePath();
        inline bool getCastShadows(){return cast_shadows;}
        inline bool getSaveImage(){return save_image;}

    private:
        bool save_image;
        bool cast_shadows;
        std::string image_filepath; //the path to the saved image
        std::string scene_filepath; //the path to the scene file to use when rendering
        std::string scene_directory;
        std::string image_directory;
};

#endif