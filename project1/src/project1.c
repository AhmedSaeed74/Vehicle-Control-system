/*
 ========================================================================================
 Name        : Mini_project1.c
 Author      : Ahmed Saeed
 Version     : 1.0.0
 Description : Vehicle Control System Project
 Date        : 23/08/2022
 ========================================================================================
 */


/* ***************************** Includes Section Start ***************************** */
#include<stdio.h>
#include<stdlib.h>  //for exit() function which used to terminate the program
/* ***************************** Includes Section End   ***************************** */


/* ***************************** Macro Section Start ******************************** */
#define ENGINE_TEMP_CONTROLLER 0
/* choose 1 to compile and show all the results
   choose 0 to compile and show all code parts except engine temperature controller part*/
/* ***************************** Macro Section End   ******************************** */


/* ******************** Global User Defined Data Types Section Start **************** */
typedef struct{
	int speed;
	float room_temp;
	float engine_temp;
}car;
car sensor;  //create type structure "sensor" which contains three members speed, room temperature and engine temperature.

typedef enum {
	OFF,
	ON
}vehicle;
vehicle Engine_State,AC_State,Controller_State; //create enum variables Engine, AC and controller, each could be OFF or ON.
/* ******************** Global User Defined Data Types Section End ****************** */


/* ************************* Functions Declaration Section Start ******************** */
void   Set_Sensor_Initial_Values();
void   Main_Options_Menu();
void   set_Sensors_Menu();
int    Set_Vehicle_Speed(int*);
float  Set_Room_Temp(float*);
float  Set_Engine_Temp(float*);
void   Change_Sensor_Values_For_Speed_30KmPerHr();
void   Display_Vehicle_Current_State();
/* ************************** Functions Declaration Section End ********************* */



/* ****************************** Main Function Start ****************************** */
int main(void) {
	Main_Options_Menu();  // calling main options function to begin the program
	return 0;
}
/* ****************************** Main Function End ******************************** */



/* ************************ functions Definition Section Start ********************* */
void Set_Sensor_Initial_Values()  // this function initializes the structure members
{
	sensor.speed = 50;
	sensor.room_temp = 35;
	sensor.engine_temp = 90;
	AC_State = OFF;
	Controller_State = OFF;
}

void Main_Options_Menu()  // this function asks the user to enter a character then Make a decision based on this input
{
	char option; // create character variable
	printf("a. Turn on the vehicle engine\n");
	printf("b. Turn off the vehicle engine\n");
	printf("c. Quit the system\n\n");
	fflush(stdout);
	scanf(" %c",&option); //asks for character input (a,b,c) from user

	switch(option)
	{
	case 'a' :
		Engine_State = ON; // turn on the vehicle's engine
		printf("\nTurn on vehicle engine\n\n");
		Set_Sensor_Initial_Values(); // set the initial values for sensor's parameters
		set_Sensors_Menu();  // call sensors set menu function which will take action when the engine is on only
		break;

	case 'b' :
		printf("\nTurn off vehicle engine\n\n");
		Main_Options_Menu();  // back to the main options then wait the user to enter input again
		break;

	case 'c' :
		printf("Quit the system\n");
		exit(0);  // terminate the program, this is the only way to get out from the console
		break;

	default :
		// if the user entered any input except a,b or c this part would ask him to enter a valid input and return to main options
		printf("Wrong Input....Please try again\n\n");
		Main_Options_Menu();
		break;
	}
}

//this function asks the user to enter a character then Make a decision either set a sensor or back to main options
void set_Sensors_Menu()
{
	char option; // create character variable
	printf("a. Turn off the engine\n");
	printf("b. Set the traffic light color\n");
	printf("c. Set the room temperature (Temperature Sensor)\n");
#if ENGINE_TEMP_CONTROLLER == 1
	// this line is printed only if engine temp controller macro = 1
	printf("d. Set the engine temperature (Engine Temperature Sensor)\n\n");
#endif
	fflush(stdout);
	scanf(" %c",&option);  //asks for character input (a,b,c,d) from user

	switch(option)
	{
	case 'a' :
		printf("\nTurn off vehicle engine\n\n");
		Main_Options_Menu();  // back to main options menu then waits the user to enter an input (a,b,c)
		break;

	case 'b' :
		sensor.speed = Set_Vehicle_Speed(&sensor.speed);
		// call vehicle speed function to get the speed depending on traffic light state
		if (sensor.speed == 30)  // check if speed = 30 then another function would be called to take action just in this case
		{
			Change_Sensor_Values_For_Speed_30KmPerHr();
		}
		break;

	case 'c' :
		printf("Enter the room temperature : ");
		fflush(stdout);
		scanf("%f",&sensor.room_temp);  //asks the user to enter a value for room temperature
		sensor.room_temp = Set_Room_Temp(&sensor.room_temp);
		// call room temp function which set AC temperature and state depending on user's input
		break;

#if ENGINE_TEMP_CONTROLLER == 1    // this line is compiled only if engine temperature controller macro = 1
	case 'd' :
		printf("Enter the engine temperature : ");
		fflush(stdout);
		scanf("%f",&sensor.engine_temp);  //asks the user to enter a value for engine temperature
		sensor.engine_temp = Set_Engine_Temp(&sensor.engine_temp);
		// call engine temperature function which set engine temperature and state depending on user's input
		break;
#endif

	default :
		/* if the user entered any input except a,b,c or (d just in case engine temperature controller is on)
		   this part would ask him to enter a valid input and return to sensors set menu */
		printf("Wrong Input....Please try again\n\n");
		set_Sensors_Menu();
		break;
	}

	Display_Vehicle_Current_State();  // call display function to print sensor's parameter values and states
}

// this function takes the address of the speed member as an argument and returns the speed value based on traffic light color
int Set_Vehicle_Speed(int* ptr_to_speed)
{
	char color;  // create character variable
	printf("Enter the traffic light color : ");
	fflush(stdout);
	scanf(" %c",&color);  //asks for character input (g,G,o,O,r,R) from user

	switch(color)
	{
	case 'g' :
	case 'G' :
		*ptr_to_speed = 100;
		break;

	case 'o' :
	case 'O' :
		*ptr_to_speed = 30;
		break;

	case 'r' :
	case 'R' :
		*ptr_to_speed = 0;
		break;

	default :   //  if the user entered invalid input he will be asked to try again then return to the beginning of the function
		printf("Wrong Input....Please try again\n\n");
		Set_Vehicle_Speed(ptr_to_speed);
		break;
	}
	return *ptr_to_speed;  // return the value of speed which passed by address
}

/* this function takes the address of the room temperature member as an argument
   and returns the new room temperature value based on the argument */
float Set_Room_Temp(float* ptr_to_room_temp)
{
	if (*ptr_to_room_temp < 10)
	{
		AC_State = ON;
		*ptr_to_room_temp = 20;
	}

	else if (*ptr_to_room_temp > 30)
	{
		AC_State = ON;
		*ptr_to_room_temp = 20;
	}

	else  // room temperature is neither less than 10 nor higher than 20
	{
		AC_State = OFF;
	}

	return *ptr_to_room_temp;  // return the value of room temperature which passed by address
}

/* this function takes the address of the engine temperature member as an argument and returns the new engine temperature
   value based on the argument, this function will be compiled only if engine room temperature macro = 1 */
float Set_Engine_Temp(float* ptr_to_engine_temp)
{
	if (*ptr_to_engine_temp < 100)
	{
		Controller_State = ON;
		*ptr_to_engine_temp = 125;
	}

	else if (*ptr_to_engine_temp > 150)
	{
		Controller_State = ON;
		*ptr_to_engine_temp = 125;
	}

	else  // engine temperature is neither less than 100 nor higher than 150
	{
		Controller_State = OFF;
	}

	return *ptr_to_engine_temp;  // return the value of engine temperature which passed by address
}

/* this function is compiled only if speed = 30, if this condition is valid
   it will change room and controller temperatures and may change their states */
void Change_Sensor_Values_For_Speed_30KmPerHr()
{
	AC_State = ON;
	sensor.room_temp = ((sensor.room_temp * (5.0/4)) + 1);  // new room temperature value

#if ENGINE_TEMP_CONTROLLER == 1   // this line is compiled only if engine temperature controller macro = 1
	Controller_State = ON;
	sensor.engine_temp = ((sensor.engine_temp * (5.0/4)) + 1);  // new engine temperature value
#endif
}

// this function displays the values and states of vehicles speed, room temperature and engine temperature
void Display_Vehicle_Current_State()
{
	if (Engine_State == ON)
	{
		printf("\n\nEngine is ON\n");
	}

	else
	{
		printf("\n\nEngine is OFF\n");
	}

	if (AC_State == ON)
	{
		printf("AC is ON\n");
	}

	else
	{
		printf("AC is OFF\n");
	}

	printf("Vehicle Speed: %d Km/Hr\n",sensor.speed);
	printf("Room Temperature: %.2f C\n",sensor.room_temp);

#if ENGINE_TEMP_CONTROLLER == 1 // this parts is printed only if engine temperature controller macro = 1
	if (Controller_State == ON)
	{
		printf("Engine Temp Controller is ON\n");
	}

	else
	{
		printf("Engine Temp Controller is OFF\n");
	}

	printf("Engine Temperature: %.2f C\n\n",sensor.engine_temp);
#endif
	printf("\n\n");
	set_Sensors_Menu();
	// back to sensor set menu then waiting the user to enter set another sensor or just turn of the vehicle's engine
}
/* ********************** functions Definition Section End ************* */
