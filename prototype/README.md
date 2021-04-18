# Making a compressed selfexecutable ELF 

This is a program that can takes an ELF file then compress and append it to the end of a different ELF.

The though behind this is to make a easier way of sending readymade executables. 

# How does it work?

There are three different executables:
* Constructor
* Compressor
* Decompressor

<b> Constructor </b>
This part is more or less the glue to both of the other ones. It's the one that the user is supposed to call. 

It takes only two arguments, the first is the ELF to compress. The second is the name to give the new file. The argument -h can also be given. 

<b> Compressor </b>
This executable is called from the constructor. It takes two arguments. The first is the file to compress, and the second is the file to which the compressed file whould be appended.

The program ends by appending the amount of bytes written to the end. This is done to help the decompressor find where the ELF ends and the compressed elf start.

<b> Decompressor</b>

This is the file that the compressed file is supposed to be appended against. 

It works by opening itself, reading the value at the end, and then using this to know where the compressed ELF start. The compressed file is the decompressed and stored in /dev/shm (this is done because it's most likely a tmpfs). The newly created file is unlinked and then executed with fexecv.

All arguments and environment variables are passed along through the fexecv call. In theory making the compression seamless to the user. 

# When should it be used?

This can be used to store ELF files if the user doesn't mind slower execution. 

It can also be used to decrease size of binaries sent online.

# What is it not?

It's not a good way to send smaller executables due to the fact that the overhead is going to be more than the storage saved. 

It's not a good way to decrease transfer time if the source code could be sent and compiled on the reciver.

# Dependencies

* bzip2
* glibc
* make
