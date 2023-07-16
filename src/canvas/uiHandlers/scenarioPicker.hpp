#ifndef SCENARIOPICKER_HPP
#define SCENARIOPICKER_HPP

#include <vector>
#include <list>
#include <string>

#include "../../objects/definitions/objectsMasterInclude.hpp"

float POINTSIZE = 0.005f;

/*****************************
 * SCENARIOS
 * 1.   circles, 
 * 2.   rectangles, 
 * 3.   points, 
 * 4.   circle to rectangle, 
 * 5.   circle to point, 
 * 6.   rectangle to point,
 * 7.   all shapes,
 * 8.   SRS scenario 1
 * 9.   SRS scenario 2
 * 10.  SRS scenario 3
 * 11.  SRS scenario 4
*****************************/

std::vector<GLFWobject> scenarioPicker(std::string scenario, std::list<std::string> scenarioEntries, std::string &outFile);

std::vector<GLFWobject> scenarioPicker(std::string scenario, std::list<std::string> scenarioEntries, std::string &outFile)
{
    std::vector<GLFWobject> objects;
    bool flag = true;
    while (flag)
    {
        if (scenario == "circles" || scenario == "1")
        {
            flag = false;
            outFile = "circleDemo.ophy";
            GLFWobject circle1      ('c',               //Shape 
                                    0.1f,               //Size
                                    1000,               //NumSegments
                                    {0.85f, 0.5f},      //Starting Position -- {x,y}
                                    {0.003f, 0.003},    //Starting Velocity -- {x,y}
                                    0,                  //Rotation -- in degrees
                                    true);              //Gravity
            objects.push_back(circle1);

            GLFWobject circle2      ('c',               //Shape 
                                    0.1f,               //Size
                                    1000,               //NumSegments
                                    {0.3f, -0.1f},      //Starting Position -- {x,y}
                                    {0.002f, -0.003f},  //Starting Velocity -- {x,y}
                                    0,                  //Rotation -- in degrees 
                                    true);              //Gravity
            objects.push_back(circle2);
        }
        else if (scenario == "rectangles" || scenario == "2")
        {
            flag = false;
            outFile = "rectangleDemo.ophy";
            GLFWobject rectangle1   ('r',               //Shape 
                                    0.3f,               //Size
                                    1000,               //NumSegments
                                    {0.6f, 0.6f},       //Starting Position -- {x,y}
                                    {-0.01f, 0.0f},     //Starting Velocity -- {x,y}
                                    0,                  //Rotation -- in degrees 
                                    true);              //Gravity
            objects.push_back(rectangle1);
            GLFWobject rectangle2   ('r',               //Shape 
                                    0.3f,               //Size
                                    1000,               //NumSegments
                                    {-0.3f, -0.2f},     //Starting Position -- {x,y}
                                    {0.003f, 0.005f},   //Starting Velocity -- {x,y}
                                    0,                  //Rotation -- in degrees 
                                    true);              //Gravity
            objects.push_back(rectangle2);
        }
        else if (scenario == "points" || scenario == "3")
        {
            flag = false;
            outFile = "pointDemo.ophy";
            GLFWobject point1       ('p',               //Shape 
                                    POINTSIZE,          //Size
                                    1000,               //NumSegments
                                    {0.5f, 0.0f},       //Starting Position -- {x,y}
                                    {-0.005f, 0.0f},  //Starting Velocity -- {x,y}
                                    0,                  //Rotation -- in degrees 
                                    true);              //Gravity
            objects.push_back(point1);
            GLFWobject point2       ('p',               //Shape 
                                    POINTSIZE,          //Size
                                    1000,               //NumSegments
                                    {-0.5f, 0.0f},     //Starting Position -- {x,y}
                                    {0.005f, 0.0f},  //Starting Velocity -- {x,y}
                                    0,                  //Rotation -- in degrees 
                                    true);              //Gravity
            objects.push_back(point2);
        }
        else if (scenario == "circle to rectangle" || scenario == "4")
        {
            flag = false;
            outFile = "circleRectangleDemo.ophy";
            GLFWobject circle      ('c',                //Shape 
                                    0.1f,               //Size
                                    1000,               //NumSegments
                                    {0.85f, 0.5f},      //Starting Position -- {x,y}
                                    {0.003f, 0.003},    //Starting Velocity -- {x,y}
                                    0,                  //Rotation -- in degrees
                                    true);              //Gravity
            objects.push_back(circle);
             GLFWobject rectangle   ('r',               //Shape 
                                    0.3f,               //Size
                                    1000,               //NumSegments
                                    {0.6f, 0.6f},       //Starting Position -- {x,y}
                                    {-0.01f, 0.0f},     //Starting Velocity -- {x,y}
                                    0,                  //Rotation -- in degrees 
                                    true);              //Gravity
            objects.push_back(rectangle);
        }
        else if (scenario == "circle to point" || scenario == "5")
        {
            flag = false;
            outFile = "circlePointDemo.ophy";
            GLFWobject circle      ('c',                //Shape 
                                    0.1f,               //Size
                                    1000,               //NumSegments
                                    {0.85f, 0.5f},      //Starting Position -- {x,y}
                                    {0.003f, 0.003},    //Starting Velocity -- {x,y}
                                    0,                  //Rotation -- in degrees
                                    true);              //Gravity
            objects.push_back(circle);
            GLFWobject point       ('p',                //Shape 
                                    POINTSIZE,          //Size
                                    1000,               //NumSegments
                                    {0.0f, 0.0f},       //Starting Position -- {x,y}
                                    {0.0001f, 0.002f},  //Starting Velocity -- {x,y}
                                    0,                  //Rotation -- in degrees 
                                    true);              //Gravity
            objects.push_back(point);
        }
        else if (scenario == "rectangle to point" || scenario == "6")
        {
            flag = false;
            outFile = "rectanglePointDemo.ophy";
            GLFWobject rectangle   ('r',                //Shape 
                                    0.3f,               //Size
                                    1000,               //NumSegments
                                    {-0.3f, -0.2f},     //Starting Position -- {x,y}
                                    {0.003f, 0.005f},   //Starting Velocity -- {x,y}
                                    0,                  //Rotation -- in degrees 
                                    true);              //Gravity
            objects.push_back(rectangle);
            GLFWobject point       ('p',                //Shape 
                                    POINTSIZE,          //Size
                                    1000,               //NumSegments
                                    {-0.95f, 0.8f},     //Starting Position -- {x,y}
                                    {0.005f, -0.004f},  //Starting Velocity -- {x,y}
                                    0,                  //Rotation -- in degrees 
                                    true);              //Gravity
            objects.push_back(point);
        }
        else if (scenario == "all shapes" || scenario == "7")
        {
            flag = false;
            outFile = "allShapesDemo.ophy";
            GLFWobject circle      ('c',                //Shape 
                                    0.1f,               //Size
                                    1000,               //NumSegments
                                    {0.85f, 0.5f},      //Starting Position -- {x,y}
                                    {0.003f, 0.003},    //Starting Velocity -- {x,y}
                                    0,                  //Rotation -- in degrees
                                    true);              //Gravity
            objects.push_back(circle);
            GLFWobject rectangle   ('r',                //Shape 
                                    0.3f,               //Size
                                    1000,               //NumSegments
                                    {0.6f, 0.6f},       //Starting Position -- {x,y}
                                    {-0.01f, 0.0f},     //Starting Velocity -- {x,y}
                                    0,                  //Rotation -- in degrees 
                                    true);              //Gravity
            objects.push_back(rectangle);
            GLFWobject point       ('p',                //Shape 
                                    POINTSIZE,          //Size
                                    1000,               //NumSegments
                                    {0.0f, 0.0f},       //Starting Position -- {x,y}
                                    {0.0001f, 0.002f},  //Starting Velocity -- {x,y}
                                    0,                  //Rotation -- in degrees 
                                    true);              //Gravity
            objects.push_back(point);
        }
        else if (scenario == "SRS scenario 1" || scenario == "8")
        {
            flag = false;
            outFile = "srsDemo1.ophy";
            GLFWobject circle      ('c',                //Shape 
                                    0.1f,               //Size
                                    1000,               //NumSegments
                                    {-0.85f, -0.85f},   //Starting Position -- {x,y}
                                    {0.008f, 0.01},     //Starting Velocity -- {x,y}
                                    0,                  //Rotation -- in degrees
                                    true);              //Gravity
            objects.push_back(circle);
        }
        else if (scenario == "SRS scenario 2" || scenario == "9")
        {
            flag = false;
            outFile = "srsDemo2.ophy";
            GLFWobject rectangle   ('r',                //Shape 
                                    0.3f,               //Size
                                    1000,               //NumSegments
                                    {-0.84f, -0.8f},    //Starting Position -- {x,y}
                                    {0.01f, 0.02f},     //Starting Velocity -- {x,y}
                                    0,                  //Rotation -- in degrees 
                                    true);              //Gravity
            objects.push_back(rectangle);
        }
        else if (scenario == "SRS scenario 3" || scenario == "10")
        {
            flag = false;
            outFile = "srsDemo3.ophy";
            GLFWobject point       ('p',                //Shape 
                                    POINTSIZE,          //Size
                                    1000,               //NumSegments
                                    {-0.9f, -0.9f},     //Starting Position -- {x,y}
                                    {0.002f, 0.002f},   //Starting Velocity -- {x,y}
                                    0,                  //Rotation -- in degrees 
                                    true);              //Gravity
            objects.push_back(point);
        }
        else if (scenario == "SRS scenario 4" || scenario == "11")
        {
            flag = false;
            outFile = "srsDemo4.ophy";
            GLFWobject circle      ('c',                //Shape 
                                    0.1f,               //Size
                                    1000,               //NumSegments
                                    {-0.85f, -0.85f},   //Starting Position -- {x,y}
                                    {0.008f, 0.03},     //Starting Velocity -- {x,y}
                                    0,                  //Rotation -- in degrees
                                    true);              //Gravity
            objects.push_back(circle);
            GLFWobject rectangle    ('r',               //Shape 
                                    0.3f,               //Size
                                    1000,               //NumSegments
                                    {0.5f, -0.4f},       //Starting Position -- {x,y}
                                    {0.0f, 0.0f},       //Starting Velocity -- {x,y}
                                    0,                  //Rotation -- in degrees 
                                    false);             //Gravity
            objects.push_back(rectangle);
            GLFWobject point       ('p',                //Shape 
                                    POINTSIZE,          //Size
                                    1000,               //NumSegments
                                    {0.0f, 0.0f},       //Starting Position -- {x,y}
                                    {0.0f, 0.005f},  //Starting Velocity -- {x,y}
                                    0,                  //Rotation -- in degrees 
                                    true);              //Gravity
            objects.push_back(point);
        }
        else
        {
            std::cout << "No valid scenario given. Available scenarios; " << std::endl;
            for (std::string i : scenarioEntries)
            {
                std::cout << i << std::endl;
            }
            std::cin >> scenario;
        }
        
    }
    
    
    return objects;
}
#endif //SCENARIOPICKER_HPP