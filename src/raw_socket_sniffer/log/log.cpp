/**
 * @file log.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-31
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "log.hh"

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */


/**
 * @brief it prints log messages either on screen or in a log file 
 * there are three degree of log messages 
 *   1. warning - this type of messages must be written yellow and the format below 
 *      [WARNING] bla bla bla 
 *   2. error - this type of messages must be written red and the format
 *      [ERROR] bla bla bla 
 *   3. chat - type type of messages must be written green and the format 
 *      [CHAT] - bla bla bla 
 * 
 * Business logic: one of these functions 
 *          
 *          print_warning
 *          print_error
 *          print_chat 
 *           
 *  is called by the upper layer with a given string messages. 
 *  these functions can get only string as parameter and it writes this 
 *  string in corresponding format. 
 *
 *   check for colored text : 
 *   https://www.geeksforgeeks.org/how-to-print-colored-text-in-c/ 
 * 
 * 
 * @param msg 
 */

static uint8_t s_g_print_to_file = 0;

/**
 * @brief this functions writes the log messages either on the screen or in a text file 
 * selection of the destination of scripts should be done dynamically 
 * 
 * @param msg  string message to be printed 
 * @param color  color of the message. It  comes from the caller function 
 */
static void print_log(std::string msg)
{
    if (s_g_print_to_file) // print message to a file 
    {
        std::ofstream inFile;
        inFile.open("log.txt");
        if (!inFile) 
            {
            std::cerr << "Unable to open file datafile.txt";
            exit(1);   // call system to stop
            }
        inFile << msg;
    }

    else  // print message to the screen 
    {
        std::cout << " " << msg <<std::endl;
    }
}

/**
 * @brief Set the print dest file object
 * 
 */
void set_print_dest_file ()
{
    s_g_print_to_file = 1;
}

/**
 * @brief Set the print dest screen object
 * 
 */
void set_print_dest_screen()
{
    s_g_print_to_file = 0;
}

/**
 * @brief Set the log msg object
 * 
 * @param msg 
 */
static void set_log_msg(std::string msg)
{
    std::string warnMessage = msg;
    print_log(warnMessage);

}

/**
 * @brief 
 * 
 * @param msg 
 */
void print_warning(std::string msg)
{
    std::cout << YELLOW << "[WARNING]" << RESET;
    set_log_msg(msg);
}

/**
 * @brief 
 * 
 * @param msg 
 */
void print_error(std::string msg)
{
    std::cout << RED << "[ERROR]" << RESET;
    set_log_msg(msg);

}

/**
 * @brief 
 * 
 * @param msg 
 */
void print_chat(std::string msg)
{
#ifdef LOG_LEVEL_CHAT
    std::cout << GREEN << "[CHAT]" << RESET;
    set_log_msg(msg);
#endif

}

/**
 * @brief 
 * 
 * @param msg 
 */
void print_data(std::string msg)
{
    std::cout << BOLDCYAN  << RESET;
    set_log_msg(msg);
}