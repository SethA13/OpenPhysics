#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <stdio.h>


/****************
 * PROTOTYPES
****************/
// collision detection
bool isColliding(char *); // probably not needed

// circle formulas
bool circleToCircleCollision(char *);
bool circleToRectangleCollision(char *);
bool circleToPointCollision(char *);

// rectangle formulas
bool rectangleToRectangleCollision(char *);
bool rectangleToPointCollision(char *);

// point formula
bool pointToPointCollision(char *);

// sat Theorem for collisions not between these 3
bool satTheorem(char *);



// check if colliding
// TODO: find more elegant solution than if statements
bool isColliding(char *objects)
{
    // Check circle cases
    if ((objects[1] == 'c') && objects[2] == 'c')
    {
       return circleToCircleCollision(objects);
    }
    else if ((objects[1] == 'c') && objects[2] == 'r')
    {
        return circleToRectangleCollision(objects);
    }
    else if ((objects[1] == 'c') && objects[2] == 'p')
    {
        return circleToPointCollision(objects);
    }

    // Check rectangle cases
    else if ((objects[1] == 'r') && objects[2] == 'r')
    {
        return rectangleToRectangleCollision(objects);
    }
    else if ((objects[1] == 'r') && objects[2] == 'p')
    {
        return rectangleToPointCollision(objects);
    }

    // Check point case
    else if ((objects[1] == 'r') && objects[2] == 'p')
    {
        return rectangleToPointCollision(objects);
    }

    // Handle extraneous case
    else
        return satTheorem(objects);
}


/*******************************
 * Handle collision types
 * These are hardcoded types
*******************************/
bool circleToCircleCollision(char *objects)
{
    return false;
}

bool circleToRectangleCollision(char *objects)
{
    return 0;
}

bool circleToPointCollision(char *objects)
{
    return 0;
}

bool rectangleToRectangleCollision(char *objects)
{
    return 0;
}

bool rectangleToPointCollision(char *objects)
{
    return 0;
}

bool pointToPointCollision(char *objects)
{
    return 0;
}
/******************************
******************************/

bool satTheorem(char *objects)
{
    return 0;
}

#endif