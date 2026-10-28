/*
Description:

This project is used to read and edit MP3 song information
using ID3 tags.
The program can display Title, Artist, Album, Year, Genre,
Comment and ID3 Version.
It can also edit the required tag information and save the
updated information into the MP3 file.

main() - Starting point of the program.
         It checks the command line arguments and calls the
         required view or edit function.

view_mp3_tags() - Used to display the MP3 tag information.
                  It reads the ID3 header and frames and
                  displays the stored details.

edit_mp3_tag() - Used to edit the selected MP3 tag.
                 It finds the required frame and replaces
                 the old information with new information.

get_size() - Converts 4 bytes into one integer value.
             It is used to find the size of an MP3 frame.

get_size_edit() - Converts 4 bytes into an integer while
                  editing the MP3 file.

put_size() - Converts an integer into 4 bytes.
             It is used to update the frame size.


put_tag_size() - Updates the total ID3 tag size in the
                 MP3 header.

copy_bytes() - Copies a given number of bytes from one
               file to another file.

print_text() - Displays normal text information such as
               Title, Artist, Album, Year and Genre.

print_comment() - Displays the comment stored in the COMM
                  frame.

mp3.h - Contains the function declarations used in the
        project.

Command Line Options:

-v  -> Used to view MP3 tag information.
-e  -> Used to edit MP3 tag information.
-t  -> Used to edit Title.
-A  -> Used to edit Artist.
-a  -> Used to edit Album.
-y  -> Used to edit Year.
-C  -> Used to edit Comment.
-c  -> Used to edit Genre.

Sample Input:

./a.out -v song.mp3


Sample Output:

================================
       MP3 TAG INFORMATION
================================

ID3 Version : ID3v2.3.0
ID3 Tag Size : 4567 bytes

--------------------------------

Title   : Believer
Artist  : Imagine Dragons
Album   : Evolve
Year    : 2017
Genre   : Rock
Comment : My Favourite Song

================================
Sample Edit Input:

./a.out -e song.mp3 -t My New Song

Output:

Tag updated successfully
Example:

./a.out -e song.mp3 -A Ajay

Output:

Tag updated successfully

*/


#include <stdio.h>
#include <string.h>
#include "mp3.h"

// main function starts the program
int main(int argc,char *argv[])
{
    char new_text[500] = "";
    int i;

    // check if user entered any argument
    if(argc < 2)
    {
        printf("Invalid arguments\n");
        printf("Use ./a.out --help for help\n");
        return 1;
    }

    // -h is used to show help
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--h") == 0 || strcmp(argv[1], "-help") == 0 ||
        strcmp(argv[1], "--help") == 0)
    {
        printf("\nMP3 TAG READER / EDITOR\n\n");

        printf("View:\n");
        printf("./a.out -v song.mp3\n\n");

        printf("Edit:\n");
        printf("./a.out -e song.mp3 -t New Title\n");
        printf("./a.out -e song.mp3 -A New Artist\n");
        printf("./a.out -e song.mp3 -a New Album\n");
        printf("./a.out -e song.mp3 -y 2026\n");
        printf("./a.out -e song.mp3 -C New Comment\n");
        printf("./a.out -e song.mp3 -c Rock\n");
    }


    // -v is used to view the tags
    else if(strcmp(argv[1], "-v") == 0)
    {
        // file name is required
        if(argc != 3)
        {
            printf("Usage: ./a.out -v song.mp3\n");
            return 1;
        }
        // call view function
        view_mp3_tags(argv[2]);
    }

    // -e is used to edit the tags
    else if(strcmp(argv[1], "-e") == 0)
    {
        // minimum arguments are required
        if(argc < 5)
        {
            printf("Usage: ./a.out -e song.mp3 -t New Title\n");
            return 1;
        }

        // join the words entered by the user
        // example: New My Song becomes one string
        for(i = 4;i < argc;i++)
        {
            if(i > 4)
            {
                strcat(new_text, " ");
            }
            strcat(new_text, argv[i]);
        }
        // call edit function
        edit_mp3_tag(argv[2], argv[3], new_text);
    }
    // invalid option
    else
    {
        printf("Invalid arguments\n");
        printf("Use ./a.out --help for help\n");
    }
    return 0;
}