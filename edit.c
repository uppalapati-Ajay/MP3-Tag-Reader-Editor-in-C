#include <stdio.h>
#include <string.h>
#include "mp3.h"

// this function converts 4 bytes into one integer
// used to get the size of a frame
int get_size_edit(unsigned char size[])
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

// this function stores an integer
// into 4 separate bytes
void put_size(unsigned char size[],int value)
{
    size[0] = (value >> 24) & 255;
    size[1] = (value >> 16) & 255;
    size[2] = (value >> 8) & 255;
    size[3] = value & 255;
}

// this function stores the ID3 tag size
// into the header
void put_tag_size(unsigned char header[],int value)
{
    header[6] =(value >> 21) & 127;
    header[7] =(value >> 14) & 127;
    header[8] =(value >> 7) & 127;
    header[9] = value & 127;
}

// this function copies bytes
// from one file to another file
void copy_bytes(FILE *source,FILE *temp,int size)
{
    char ch;
    int i;
    // copy one byte at a time
    for(i = 0;i < size;i++)
    {
        fread(&ch,1,1,source);
        fwrite(&ch,1,1,temp);
    }
}
// this function edits the selected MP3 tag
void edit_mp3_tag(char *file_name,char *option,char *new_text)
{
    FILE *source;
    FILE *temp;
    unsigned char header[10];
    unsigned char frame[10];
    unsigned char data[10000];
    unsigned char new_data[10000];
    char frame_id[5] = "";
    char temp_name[100];
    int tag_size;
    int old_tag_size;
    int read_size = 0;
    int frame_size;
    int new_size;
    int found = 0;
    // check which option the user selected
    if(strcmp(option,"-t")== 0)
    {
        strcpy(frame_id,"TIT2");
    }
    else if(strcmp(option,"-A") == 0)
    {
        strcpy(frame_id, "TPE1");
    }
    else if(strcmp(option, "-a") == 0)
    {
        strcpy(frame_id, "TALB");
    }
    else if(strcmp(option, "-y") == 0)
    {
        strcpy(frame_id, "TYER");
    }
    else if(strcmp(option, "-C") == 0)
    {
        strcpy(frame_id, "COMM");
    }
    else if(strcmp(option, "-c") == 0)
    {
        strcpy(frame_id, "TCON");
    }
    else
    {
        printf("Invalid edit option\n");
        return;
    }
    // open original MP3 file
    source = fopen(file_name, "rb");
    if (source == NULL)
    {
        printf("File not found\n");
        return;
    }
    // read the ID3 header
    fread(header, 1, 10, source);
    // check ID3
    if(header[0] != 'I' || header[1] != 'D' || header[2] != '3')
    {
        printf("ID3 tag not found\n");
        fclose(source);
        return;
    }
    // calculate ID3 tag size
    int a = (header[6] & 127) << 21;
    int b = (header[7] & 127) << 14;
    int c = (header[8] & 127) << 7;
    int d = (header[9] & 127);
    // add all values
    tag_size = a + b + c + d;
    old_tag_size = tag_size;
    // create temporary file
    strcpy(temp_name, "temp.mp3");
    temp = fopen(temp_name, "wb");

    if(temp == NULL)
    {
        printf("Cannot create temporary file\n");
        fclose(source);
        return;
    }

    // copy the ID3 header
    fwrite(header, 1, 10, temp);

    // read frames one by one
    while(read_size + 10 <= old_tag_size)
    {
        // read frame header
        fread(frame, 1, 10, source);
        read_size = read_size + 10;

        // no more frames
        if(frame[0] == 0)
        {
            fwrite(frame, 1, 10, temp);
            copy_bytes(source,temp,old_tag_size - read_size);
            read_size = old_tag_size;
            break;
        }
        // get current frame size
        frame_size = get_size_edit(&frame[4]);
        // check frame size
        if (frame_size <= 0 ||
            frame_size > old_tag_size - read_size)
        {
            break;
        }

        // if frame is bigger than our array
        // copy it without editing
        if(frame_size > 10000)
        {
            fwrite(frame,1,10,temp);
            copy_bytes(source,temp,frame_size);
            read_size = read_size + frame_size;
            continue;
        }

        // read frame data
        fread(data, 1, frame_size, source);
        read_size = read_size + frame_size;

        // check whether this is the frame
        // that the user wants to edit
        if(found == 0 && strncmp((char *)frame,frame_id,4) == 0)
        {
            // comment has a different format
            if(strcmp(frame_id, "COMM") == 0)
            {
                // one byte for encoding
                // three bytes for language
                // one byte separator
                // remaining bytes are comment
                new_size = strlen(new_text) + 5;
                // encoding

                new_data[0] = 0;
                // language = English

                new_data[1] = 'e';
                new_data[2] = 'n';
                new_data[3] = 'g';
                // separator
                new_data[4] = 0;

                // copy new comment
                strcpy((char *)&new_data[5],
                       new_text);
            }

            // normal text tag
            else
            {
                // one byte for encoding
                // remaining bytes are text
                new_size = strlen(new_text) + 1;

                // encoding
                new_data[0] = 0;
                // copy new text
                strcpy((char *)&new_data[1],
                       new_text);
            }
            // update frame size
            put_size(&frame[4],
                     new_size);

            // write updated frame
            fwrite(frame, 1, 10, temp);
            fwrite(new_data,1,new_size,temp);

            // update total tag size
            tag_size = tag_size - frame_size +new_size;
            found = 1;
        }
        else
        {
            // this is not the required frame
            // so copy it without changing
            fwrite(frame, 1, 10, temp);
            fwrite(data,1,frame_size,temp);
        }
    }
    // copy the remaining MP3 audio
    while (1)
    {
        char ch;
        // read one byte
        if(fread(&ch,1,1,source) != 1)
        {
            break;
        }
        // write one byte
        fwrite(&ch, 1, 1, temp);
    }

    // if tag was not found
    if(found == 0)
    {
        printf("Tag not found\n");
        fclose(source);
        fclose(temp);
        remove(temp_name);
        return;
    }

    // update ID3 tag size
    put_tag_size(header,tag_size);

    // go back to beginning of temp file
    fseek(temp,0,SEEK_SET);

    // write updated header
    fwrite(header,1,10,temp);// close files
    fclose(source);
    fclose(temp);

    // delete old MP3
    remove(file_name);

    // rename temporary file
    // with the original file name
    rename(temp_name,file_name);
    printf("Tag updated successfully\n");
}