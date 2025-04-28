##############################################################################
Chapter 8 Obstacle Avoiding Robot Ant
##############################################################################

In this chapter, we will learn how to make the robot ant avoid obstacles when crawling.

Sketch
********************************************

Open 08.1.Ultrasonic_Ant.ino in **Freenove_Robot_Ant_Kit\\Sketches\\08.1.Ultrasonic_Ant.**

.. image:: ../_static/imgs/Chapter7_Infrared_Controlled_Robot/Chapter07_01.png
    :align: center   

Compile and upload the code. When the code is uploaded successfully, put the robot on the floor and turn ON the switch. After 2 seconds, the ant will be in obstacle avoidance mode.

.. note::
    
    Please be careful when taking it back, a moving ant may pinch your hands.

Code
==========================================

.. literalinclude:: ../../../freenove_Kit/Sketches/08.1.Ultrasonic_Ant/08.1.Ultrasonic_Ant.ino
    :linenos: 
    :language: c
    :dedent:

Explanation of Code
===========================================

Include the header file of library function, which makes it easier to call the program.

.. code-block:: c 
    :linenos:

    #include "Ultrasonic.h"
    #include "myServo.h"

Ultrasonic_Setup() function is called to initialize ultrasonic module. Ant_Setup() function is called to initialize servo.

.. code-block:: c 
    :linenos:

    Ultrasonic_Setup();
    Ant_Setup();

Ultrasonic_Get_Data() is called to obtain distance information every 100 milliseconds and control the robot to make different actions based on the data received. When there is no obstacle 40cm in front of the ant robot, it crawls forward. When the ant robot detects an obstacle 20-40cm ahead, it crawls to the left and ahead to avoid the obstacle in advance. When the ant robot detects an obstacle 10-20cm ahead, which is a relatively close distance, therefore it will make a spot turn to left. When the obstacle is within 10cm, it will move backward to have enough space for the next movement.

.. code-block:: c 
    :linenos:

    Ultrasonic_Get_Data(100);
    if (Ultrasonic_Value >= 40)
        ant_run_forth(2, 5);      //Forward
    else if (Ultrasonic_Value >= 20 && Ultrasonic_Value < 40)
        ant_run_left(2, 5);       //Forward to the left
    else if (Ultrasonic_Value >= 10 && Ultrasonic_Value < 20)
        ant_run_situ_left(2, 5);  //Turn left in situ
    else
        ant_run_back(2, 5);       //Backwards