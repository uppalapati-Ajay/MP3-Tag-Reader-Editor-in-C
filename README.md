# 🎵 MP3 Tag Reader & Editor in C

A command-line **MP3 Tag Reader & Editor** developed using the C programming language to read, display, and modify ID3 metadata stored in MP3 audio files.

The project allows users to view song information such as title, artist, album, year, genre, and comments. It also provides options to edit selected metadata fields and save the updated information into the original MP3 file.

This project demonstrates practical applications of **C programming, binary file handling, structures, pointers, string manipulation, command-line arguments, and modular programming**.

## 📌 Table of Contents

- [About the Project](#-about-the-project)
- [Features](#-features)
- [Metadata Supported](#-metadata-supported)
- [Command-Line Options](#-command-line-options)
- [Project Structure](#-project-structure)
- [Technologies and Concepts](#-technologies-and-concepts)
- [How the Project Works](#-how-the-project-works)
- [Compilation and Execution](#-compilation-and-execution)
- [Sample Input and Output](#-sample-input-and-output)
- [Error Handling](#-error-handling)
- [Learning Outcomes](#-learning-outcomes)
- [Limitations](#-limitations)
- [Future Improvements](#-future-improvements)
- [Author](#-author)

## 🚀 About the Project

MP3 files can contain metadata that describes the audio, including the song title, artist, album, release year, genre, and comments.

This project reads the ID3 header and processes metadata frames to display the information stored inside an MP3 file. It also allows users to select a metadata field, provide new text, and update the corresponding frame.

The application uses command-line arguments to identify whether the user wants to view or edit metadata.

The program is divided into separate source files to keep the implementation organized and easier to maintain.

## ✨ Features

### 1. View MP3 Metadata

- Read the ID3 header from an MP3 file.
- Display the ID3 version reported by the header.
- Calculate and display the ID3 tag size.
- Read metadata frames and identify supported frame IDs.
- Display available song information in a formatted output.

### 2. Edit MP3 Metadata

The application supports editing the following fields:

- **Title:** Change the song title.
- **Artist:** Change the artist name.
- **Album:** Change the album name.
- **Year:** Update the year field.
- **Comment:** Replace the comment text.
- **Genre:** Update the genre text.

The program searches for the selected frame, replaces its content, updates the frame size and total tag size, and writes the resulting file through a temporary file.

### 3. Command-Line Interface

- View metadata using the `-v` option.
- Edit metadata using the `-e` option.
- Select a specific field using an edit option.
- Display usage instructions using `-h` or `--help`.
- Accept multiword replacement text through command-line arguments.

### 4. Binary File Handling

- Open MP3 files in binary mode.
- Read the ID3 header and frame headers.
- Process frame data using byte arrays.
- Copy unchanged frame data and audio content to a temporary file.
- Replace the original file with the updated temporary file after editing.

### 5. Modular Programming

The project separates the main program, metadata viewing logic, metadata editing logic, and function declarations into different source and header files.

## 🎼 Metadata Supported

The implementation recognizes these ID3 frame identifiers:

| Metadata | Frame ID | Operation |
|---|---|---|
| Title | `TIT2` | View and edit |
| Artist | `TPE1` | View and edit |
| Album | `TALB` | View and edit |
| Year | `TYER` | View and edit |
| Genre | `TCON` | View and edit |
| Comment | `COMM` | View and edit |

The program reads the ID3 version from the file header and displays it. The editing implementation uses the frame identifiers listed above.

## 🖥️ Command-Line Options

### View metadata

```bash
./a.out -v song.mp3
```

Displays the supported metadata fields found in the specified MP3 file.

### Edit the title

```bash
./a.out -e song.mp3 -t My New Song
```

### Edit the artist

```bash
./a.out -e song.mp3 -A Ajay
```

### Edit the album

```bash
./a.out -e song.mp3 -a My New Album
```

### Edit the year

```bash
./a.out -e song.mp3 -y 2026
```

### Edit the comment

```bash
./a.out -e song.mp3 -C My Favourite Song
```

### Edit the genre

```bash
./a.out -e song.mp3 -c Rock
```

### Display help

```bash
./a.out --help
```

The help output lists the supported viewing and editing commands.

**Note:** The commands above use `./a.out`, as in the project's current usage instructions. If you compile the program with a different output filename, use that filename instead.

## 📂 Project Structure

```text
MP3-Tag-Reader-Editor-in-C/
│
├── main.c
├── view.c
├── edit.c
├── mp3.h
├── README.md
└── .gitignore
```

### File descriptions

**`main.c`**
- Contains the main function.
- Processes command-line arguments.
- Selects viewing or editing operations.
- Combines multiword replacement text.
- Displays help and usage instructions.

**`view.c`**
- Opens the MP3 file in binary read mode.
- Reads and validates the ID3 header.
- Calculates the tag size.
- Processes metadata frames.
- Displays title, artist, album, year, genre, and comment.

**`edit.c`**
- Identifies the requested metadata frame.
- Reads the existing tag information.
- Replaces the selected frame's text.
- Updates the frame size and total tag size.
- Copies the updated content through a temporary file.

**`mp3.h`**
- Declares the `view_mp3_tags()` function.
- Declares the `edit_mp3_tag()` function.
- Provides shared function declarations for the source modules.

**`README.md`**
- Documents the project, supported commands, compilation, and usage.

**`.gitignore`**
- Excludes configured compiled files, temporary files, and local audio files from future Git tracking.

## ⚙️ Technologies and Concepts

| Concept | Application in the Project |
|---|---|
| C Programming | Main application logic |
| Functions | Separate viewing, editing, and helper operations |
| Pointers | Passing filenames and metadata buffers |
| Arrays | Storing headers, frames, and text data |
| Strings | Comparing frame IDs and processing replacement text |
| Command-Line Arguments | Selecting operations and metadata fields |
| Binary File Handling | Reading and writing MP3 file bytes |
| File Operations | Using `fopen()`, `fread()`, `fwrite()`, `fseek()`, and `fclose()` |
| String Library | Using functions such as `strcmp()`, `strncmp()`, `strcpy()`, and `strcat()` |
| Bitwise Operations | Extracting and updating tag-size values |
| Modular Programming | Separating source files and declarations |
| Temporary Files | Rebuilding the file during metadata editing |

## 🔍 How the Project Works

### Viewing metadata

1. The program receives the `-v` option and the MP3 filename.
2. It opens the file in binary read mode.
3. It reads the first ten bytes as the ID3 header.
4. It checks for the `ID3` signature.
5. It extracts the version and calculates the tag size.
6. It reads frame headers and their associated data.
7. It identifies supported frame IDs.
8. It displays the corresponding metadata values.
9. It closes the file.

### Editing metadata

1. The program receives the `-e` option, filename, field option, and replacement text.
2. It maps the field option to the corresponding frame ID.
3. It opens the original MP3 file and validates the ID3 signature.
4. It creates a temporary file.
5. It reads metadata frames and searches for the selected frame.
6. It creates replacement frame data and updates the frame size.
7. It copies the other frame data and remaining audio bytes.
8. It updates the total tag size in the header.
9. It closes the files and replaces the original file with the temporary file.

**Important:** Editing changes the specified MP3 file. Keep a backup of important audio files before testing the edit commands.

## 💻 Compilation and Execution

### Prerequisites

- GCC or another compatible C compiler.
- A terminal or command prompt.
- An MP3 file containing a readable ID3 tag for testing.

### Compile the project

Run the following command from the project directory:

```bash
gcc main.c view.c edit.c -o mp3tag
```

### Run on Linux

View metadata:

```bash
./mp3tag -v song.mp3
```

Edit the title:

```bash
./mp3tag -e song.mp3 -t My New Song
```

Display help:

```bash
./mp3tag --help
```

### Run on Windows

Compile using GCC:

```bash
gcc main.c view.c edit.c -o mp3tag.exe
```

View metadata:

```bash
mp3tag.exe -v song.mp3
```

Edit the artist:

```bash
mp3tag.exe -e song.mp3 -A Ajay
```

Replace `song.mp3` with the path to your own test file.

## 🧪 Sample Input and Output

### View metadata

**Command:**

```bash
./a.out -v song.mp3
```

**Illustrative output from the project's documentation:**

```text
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
```

The values shown above are sample documentation values. Actual output depends on the metadata in the MP3 file being read.

### Edit the title

**Command:**

```bash
./a.out -e song.mp3 -t My New Song
```

**Output:**

```text
Tag updated successfully
```

### Edit the artist

**Command:**

```bash
./a.out -e song.mp3 -A Ajay
```

**Output:**

```text
Tag updated successfully
```

## ⚠️ Error Handling

The current implementation includes messages for several error conditions:

| Condition | Message |
|---|---|
| Missing or invalid command-line arguments | `Invalid arguments` |
| Incorrect view command usage | `Usage: ./a.out -v song.mp3` |
| MP3 file cannot be opened | `File not found` |
| ID3 signature is missing | `ID3 tag not found` |
| Unsupported edit option | `Invalid edit option` |
| Temporary file cannot be created | `Cannot create temporary file` |
| Selected metadata frame is missing | `Tag not found` |
| Metadata update completes | `Tag updated successfully` |

These messages help users understand common problems while running the program.

## 📚 Learning Outcomes

Working on this project provided practical experience with:

- Understanding the structure of ID3 metadata.
- Reading binary data from files.
- Processing file headers and metadata frames.
- Using arrays and pointers to manage byte data.
- Converting byte sequences into integer values.
- Applying bitwise operations to extract and update tag sizes.
- Handling command-line arguments in C.
- Managing strings and multiword input.
- Organizing a program into multiple `.c` and `.h` files.
- Using temporary files to update file contents.
- Handling common file and command-line errors.

## ⚠️ Limitations

- The implementation recognizes a specific set of metadata frame identifiers.
- The year field uses the `TYER` frame identifier.
- Text processing is implemented using the encoding assumptions in the current source code.
- Frame data larger than the configured buffer is skipped or copied without editing, depending on the operation.
- The program checks the ID3 signature and some frame-size boundaries but does not implement complete validation of every possible MP3 metadata format.
- Editing requires the selected frame to exist in the file; the current implementation does not add a missing metadata frame.

## 🔮 Future Improvements

Possible enhancements include:

- Supporting additional ID3 frame identifiers and versions.
- Improving support for different text encodings.
- Adding missing metadata frames when requested.
- Improving validation of malformed or truncated MP3 files.
- Adding safer recovery if an edit fails during file replacement.
- Supporting additional metadata fields.
- Adding automated tests for viewing and editing operations.
- Improving command-line help and error messages.

## 👨‍💻 Author

**Ajay Uppalapati**

Electronics and Communication Engineering graduate passionate about C Programming, Embedded Systems, Linux, and software development.

### Connect With Me

- 💻 **GitHub:** [uppalapati-Ajay](https://github.com/uppalapati-Ajay)
- 💼 **LinkedIn:** www.linkedin.com/in/ajay-uppalapati-06865124b

---

⭐ If you find this project interesting, feel free to explore the source code and share your feedback!
