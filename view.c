#include <stdio.h>
#include <string.h>
#include "mp3.h"

// this function converts 4 bytes into one integer
// used to get the size of a frame
int get_size(unsigned char size[])
{
    int value;
    // first byte value
    int a = size[0] * 16777216;
    // second byte value
    int b = size[1] * 65536;
    // third byte value
    int c = size[2] * 256;
    // fourth byte value
    int d = size[3];
    // add all values
    value = a + b + c + d;
    return value;
}

// this function prints normal text
// example: title, artist, album, year and genre
void print_text(char name[],unsigned char data[],int size)
{
    int i;
    printf("%s : ", name);
    // first byte contains encoding
    // so start from byte 1
    for(i = 1;i < size;i++)
    {
        // zero means text has ended
        if(data[i] == 0)
        {
            break;
        }
        printf("%c", data[i]);
    }
    printf("\n");
}

// this function prints comment
void print_comment(unsigned char data[],int size)
{
    int i;
    printf("Comment : ");
    // first 4 bytes contain language information
    i = 4;
    // skip the description
    while(i < size && data[i] != 0)
    {
        i++;
    }
    i++;
    // print the actual comment
    while(i < size && data[i] != 0)
    {
        printf("%c", data[i]);
        i++;
    }
    printf("\n");
}

// this function reads the MP3 file
// and displays the tag information
void view_mp3_tags(char *file_name)
{
    FILE *fp;
    unsigned char header[10];
    unsigned char frame[10];
    unsigned char data[10000];
    int tag_size;
    int read_size = 0;
    int frame_size;
    // open MP3 file
    fp = fopen(file_name, "rb");
    if(fp == NULL)
    {
        printf("File not found\n");
        return;
    }

    // read first 10 bytes
    // these bytes contain the ID3 header
    fread(header, 1, 10, fp);
    // check ID3
    if (header[0] != 'I' || header[1] != 'D' || header[2] != '3')
    {
        printf("ID3 tag not found\n");
        fclose(fp);
        return;
    }

    printf("\n================================\n");
    printf("       MP3 TAG INFORMATION\n");
    printf("================================\n");

    // display ID3 version
    printf("ID3 Version : ID3v2.%d.%d\n", header[3], header[4]);

    // calculate ID3 tag size
    int a = (header[6] & 127) << 21;
    int b = (header[7] & 127) << 14;
    int c = (header[8] & 127) << 7;
    int d = (header[9] & 127);
    // add all four values
    tag_size = a + b + c + d;
    printf("ID3 Tag Size : %d bytes\n", tag_size);

    printf("--------------------------------\n");

    // read frames one by one
    while(read_size + 10 <= tag_size)
    {
        // read 10 byte frame header
        fread(frame, 1, 10, fp);
        read_size = read_size + 10;
        // if first byte is zero
        // there are no more frames
        if(frame[0] == 0)
        {
            break;
        }
        // get frame size
        frame_size = get_size(&frame[4]);
        // check frame size
        if(frame_size <= 0 || frame_size > tag_size - read_size)
        {
            break;
        }

        // our array can store only 10000 bytes
        if(frame_size > 10000)
        {
            fseek(fp, frame_size, SEEK_CUR);
            read_size = read_size + frame_size;
            continue;
        }

        // read frame data
        fread(data, 1, frame_size, fp);
        read_size = read_size + frame_size;

        // TIT2 means title
        if(strncmp((char *)frame, "TIT2", 4) == 0)
        {
            print_text("Title", data, frame_size);
        }

        // TPE1 means artist
        else if(strncmp((char *)frame, "TPE1", 4) == 0)
        {
            print_text("Artist", data, frame_size);
        }

        // TALB means album
        else if(strncmp((char *)frame, "TALB", 4) == 0)
        {
            print_text("Album", data, frame_size);
        }

        // TYER means year
        else if(strncmp((char *)frame, "TYER", 4) == 0)
        {
            print_text("Year", data, frame_size);
        }

        // TCON means genre
        else if(strncmp((char *)frame, "TCON", 4) == 0)
        {
            print_text("Genre", data, frame_size);
        }

        // COMM means comment
        else if(strncmp((char *)frame, "COMM", 4) == 0)
        {
            print_comment(data, frame_size);
        }
    }
    printf("================================\n");
    // close the file
    fclose(fp);
}