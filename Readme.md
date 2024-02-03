
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

bashCopy code

`sudo apt-get install -y nasm iasl uuid-dev python3 sudo apt-get install -y python3-distutils`

Cloning and Preparing EDK2 Repository
-------------------------------------

bashCopy code

`git clone https://github.com/tianocore/edk2 cd edk2 git submodule update --init`

Compiling EDK2 Build Tools
--------------------------

*   **Compile C Programs**: **EDK2** utilizes a combination of Python scripts and C programs located in the **BaseTools** directory.
    
    bashCopy code
    
    `make -C BaseTools`
    
    This command builds tools and libraries under **BaseTools/Source/C/bin** and **BaseTools/Source/C/libs**.
    
*   **Tool Wrappers and User Manuals**:
    
    *   **EDK2** offers comprehensive wrappers for the use of build tools on both **Linux** and **Windows** platforms. For detailed guidance, refer to the corresponding directories within the **EDK2** repository.
    *   User manuals for various build tools are located under `BaseTools/UserManuals`.

Building EDKII
--------------

*   **Initialize Environment**: Source the `edksetup.sh` script:
    
    bashCopy code
    
    `. edksetup.sh`
    
*   **Building EDKII**: Use the `build` command to compile EDKII packages.
    

Compiling OVMF (Open Virtual Machine Firmware)
----------------------------------------------

*   **Building OVMF**: Execute the following command to build OVMF:
    
    bashCopy code
    
    `build --platform=OvmfPkg/OvmfPkgX64.dsc --arch=X64 --buildtarget=RELEASE --tagname=GCC5`
    
    **Note:** GCC version 5 or higher is required.
    
*   **Locating Build Artifacts**: The build artifacts can be found in the directory structure: `Build/{Platform Name}/{TARGET}_{TOOL_CHAIN_TAG}/FV`.
    

Testing with QEMU
-----------------

*   **Install QEMU**: To install QEMU on your system, run the following command in the terminal:
    
    bashCopy code
    
    `sudo apt-get install qemu-system-x86_64`
    
*   **Running OVMF in QEMU**: To run OVMF with QEMU, use the following command:
    
    bashCopy code
    
    `qemu-system-x86_64 -drive if=pflash,format=raw,readonly,file=Build/OvmfX64/RELEASE_GCC5/FV/OVMF_CODE.fd -drive if=pflash,format=raw,file=Build/OvmfX64/RELEASE_GCC5/FV/OVMF_VARS.fd -nographic -net none`


## Implementation Details

In this section, you will explain how you completed your project. It is recommended to use pictures to demonstrate your system model and implementation.


Feel free to use sub-topics for your projects. If your project consists of multiple parts (e.g. server, client, and embedded device), create a separate topic for each one.

## How to Run

In this part, you should provide instructions on how to run your project. Also if your project requires any prerequisites, mention them. 

#### Examples:
#### Build Project
Your text comes here
```bash
  build --platform=OvmfPkg/OvmfPkgX64.dsc --arch=X64 --buildtarget=RELEASE --tagname=GCC5
```

#### Run server
Your text comes here
```bash
  pyhton server.py -p 8080
```

| Parameter | Type     | Description                |
| :-------- | :------- | :------------------------- |
| `-p` | `int` | **Required**. Server port |



## Results
In this section, you should present your results and provide an explanation for them.

Using image is required.

## Related Links
Some links related to your project come here.
 - [EDK II]([https://github.com/tianocore/edk2](https://github.com/tianocore/edk2))
 - [Protocols – Media Access]([https://randomnerdtutorials.com/esp32-pinout-reference-gpios/](https://uefi.org/specs/UEFI/2.10/13_Protocols_Media_Access.html))
 - [UEFI-Lessons]([https://docs.djangoproject.com/en/5.0/](https://github.com/Kostr/UEFI-Lessons))


## Authors
Authors and their github link come here.
- [@Mohammadreza AhmadiTeshnizi]([https://github.com/Sharif-University-ESRLab](https://github.com/teshnizi2))
- [@Ali Abbasi]([https://github.com/Sharif-University-ESRLab](https://github.com/a80-abbasi))
- [@Matin Shoja](https://github.com/Sharif-University-ESRLab)


