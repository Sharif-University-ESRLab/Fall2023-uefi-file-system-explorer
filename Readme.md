
![Logo](https://github.com/Sharif-University-ESRLab/Fall2023-uefi-file-system-explorer/assets/59166955/ccd1e642-9594-4861-929e-8e6194769d04)

# UEFI File System Explorer

In this project, we were responsible for developing a UEFI program functioning as a file system explorer. Our primary goal was to design a user interface that allows for easy navigation and interaction with files and directories in the UEFI environment. This project involved a detailed study of UEFI specifications and understanding the principles of developing related applications. Utilizing the protocols available in the UEFI file system, we integrated files and directories. Additionally, developing the user interface, adding advanced features like file searching, filtering, and sorting, and developing error management mechanisms to handle potential exceptions and errors were part of the challenges of this project. Finally, we conducted extensive testing and validation of the program in various scenarios.


Prerequisites
=============

Before starting, ensure your Linux distribution has the following packages installed:

*   **NASM (Netwide Assembler)**: An assembler and disassembler for the Intel x86 architecture.
*   **IASL (Intel ACPI Compiler/Decompiler)**: Used for Advanced Configuration and Power Interface (ACPI).
*   **UUID-Dev (Universally Unique ID Library)**: Essential for generating unique identifiers in UEFI.
*   **Python 3**: Necessary for running build infrastructure scripts.

Installing Packages on Ubuntu
-----------------------------

Run the following commands in your terminal:


`sudo apt-get install -y nasm iasl uuid-dev python3 sudo apt-get install -y python3-distutils`

Cloning and Preparing EDK2 Repository
-------------------------------------


`git clone https://github.com/tianocore/edk2 cd edk2 git submodule update --init`

Compiling EDK2 Build Tools
--------------------------

*   **Compile C Programs**: **EDK2** utilizes a combination of Python scripts and C programs located in the **BaseTools** directory.
    
    
    `make -C BaseTools`
    
    This command builds tools and libraries under **BaseTools/Source/C/bin** and **BaseTools/Source/C/libs**.
    
*   **Tool Wrappers and User Manuals**:
    
    *   **EDK2** offers comprehensive wrappers for the use of build tools on both **Linux** and **Windows** platforms. For detailed guidance, refer to the corresponding directories within the **EDK2** repository.
    *   User manuals for various build tools are located under `BaseTools/UserManuals`.

Building EDKII
--------------

*   **Initialize Environment**: Source the `edksetup.sh` script:
    
     
    `. edksetup.sh`
    
*   **Building EDKII**: Use the `build` command to compile EDKII packages.
    

Compiling OVMF (Open Virtual Machine Firmware)
----------------------------------------------

*   **Building OVMF**: Execute the following command to build OVMF:
    
     
    `build --platform=OvmfPkg/OvmfPkgX64.dsc --arch=X64 --buildtarget=RELEASE --tagname=GCC5`
    
    **Note:** GCC version 5 or higher is required.
    
*   **Locating Build Artifacts**: The build artifacts can be found in the directory structure: `Build/{Platform Name}/{TARGET}_{TOOL_CHAIN_TAG}/FV`.
    

*****************************
Implementation Details:
-----------------------

### 1\. Command Line Interface:

*   Users interact with the program through a command-line interface, issuing commands for file system operations.

### 2\. Implemented Commands:

*   `ls`: List files and directories in the current directory.
*   `ls -n`: List files and directories sorted by name.
*   `rm`: Remove files or directories.
*   `mkdir`: Create a new directory.
*   `cd`: Change the current directory.
*   `nano`: Text editor for file editing or creating a new file.
*   `info`: Display information about a file or directory.
*   `cat`: Display the contents of a file.
*   `copy`: Copy files or directories.
*   `cut`: Cut (move) files or directories.
*   `paste`: Paste copied or cut files or directories.
*   `search`: Search for files or directories by name.
*   `quit`: Exit the program.

### 3\. Development Environment:

*   The application is developed using the EDK II (EFI Development Kit II) framework, which provides a development environment for UEFI applications.

### 4\. File System Interaction:

*   File system interactions are performed using the EFI\_FILE\_PROTOCOL, a standard protocol for UEFI file system operations.

### 5\. Execution Environment:

*   QEMU (Quick EMUlator) is utilized as the UEFI environment for running and testing the application.

For in-depth information on the implementation details of each feature, please refer to our thorough documentation available in the "Documents" directory. The documentation provides comprehensive insights into the design choices, coding practices, and specific functionalities of each command implemented in this UEFI application.
*****************************
## How to Run
-----------------

*   **Install QEMU**: To install QEMU on your system, run the following command in the terminal:
     
    `sudo apt-get install qemu-system-x86_64`
    
*   **Running OVMF in QEMU**: To run OVMF with QEMU, use the following command:
     
    `qemu-system-x86_64 -drive if=pflash,format=raw,readonly,file=Build/OvmfX64/RELEASE_GCC5/FV/OVMF_CODE.fd -drive if=pflash,format=raw,file=Build/OvmfX64/RELEASE_GCC5/FV/OVMF_VARS.fd -nographic -net none`



## Example Results

<p align="center">
  <img src="https://github.com/Sharif-University-ESRLab/Fall2023-uefi-file-system-explorer/assets/59166955/c25d643f-ddda-4782-8759-43eda7c5d94c" alt="Example Result 1" />
  <br>
  <em>Figure 1: mkdir, ls, help</em>
</p>

<p align="center">
  <img src="https://github.com/Sharif-University-ESRLab/Fall2023-uefi-file-system-explorer/assets/59166955/763b51d7-548f-40ee-aca9-6544e04d592d" alt="Example Result 2" />
  <br>
  <em>Figure 2: nano, cat</em>
</p>

<p align="center">
  <img src="https://github.com/Sharif-University-ESRLab/Fall2023-uefi-file-system-explorer/assets/59166955/80669c71-0f12-4341-938c-99fb1307d908" alt="Example Result 3" />
  <br>
  <em>Figure 3: copy, paste</em>
</p>


## Related Links
Some links related to your project come here.
 - [EDK II]([https://github.com/tianocore/edk2](https://github.com/tianocore/edk2))
 - [Protocols – Media Access]([https://randomnerdtutorials.com/esp32-pinout-reference-gpios/](https://uefi.org/specs/UEFI/2.10/13_Protocols_Media_Access.html))
 - [UEFI-Lessons]([https://docs.djangoproject.com/en/5.0/](https://github.com/Kostr/UEFI-Lessons))


## Authors
Authors and their github link come here.
- [Mohammadreza AhmadiTeshnizi]([https://github.com/Sharif-University-ESRLab](https://github.com/teshnizi2))
- [Ali Abbasi]([https://github.com/Sharif-University-ESRLab](https://github.com/a80-abbasi))
- [Matin Shoja]([https://github.com/Sharif-University-ESRLab](https://github.com/MartinBrave)https://github.com/MartinBrave)


