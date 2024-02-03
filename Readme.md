
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



## Results

![11](https://github.com/Sharif-University-ESRLab/Fall2023-uefi-file-system-explorer/assets/59166955/eb63c8eb-8767-48dd-ade5-54ef9363c33e)
![10](https://github.com/Sharif-University-ESRLab/Fall2023-uefi-file-system-explorer/assets/59166955/30324939-6bb2-48e3-8773-b9a0251034a4)
![9](https://github.com/Sharif-University-ESRLab/Fall2023-uefi-file-system-explorer/assets/59166955/64c030e7-bd31-453c-a8ff-cac63dd644e3)
![8](https://github.com/Sharif-University-ESRLab/Fall2023-uefi-file-system-explorer/assets/59166955/3491f2dc-2e16-4cec-a3e4-7f471fad17c4)
![7](https://github.com/Sharif-University-ESRLab/Fall2023-uefi-file-system-explorer/assets/59166955/6f19bbfb-e7ce-40ca-aa9b-76c4f4ad7c32)
![6](https://github.com/Sharif-University-ESRLab/Fall2023-uefi-file-system-explorer/assets/59166955/9215f1af-5abf-467f-a91e-c0798c45ee4f)
![5](https://github.com/Sharif-University-ESRLab/Fall2023-uefi-file-system-explorer/assets/59166955/b0a6e1ba-e204-45a2-af9a-3ef3235c8db6)
![4](https://github.com/Sharif-University-ESRLab/Fall2023-uefi-file-system-explorer/assets/59166955/136c729b-addb-46f9-9041-726c6bf0ac1a)
![3](https://github.com/Sharif-University-ESRLab/Fall2023-uefi-file-system-explorer/assets/59166955/98d76eed-642b-4c6a-af41-a535f26b554b)
![2](https://github.com/Sharif-University-ESRLab/Fall2023-uefi-file-system-explorer/assets/59166955/6758ed4d-8223-43ca-b04b-d3259cc0f612)
![1](https://github.com/Sharif-University-ESRLab/Fall2023-uefi-file-system-explorer/assets/59166955/b561e63b-2d2a-4681-8dc0-7dd6d030a03b)
![19](https://github.com/Sharif-University-ESRLab/Fall2023-uefi-file-system-explorer/assets/59166955/edcffac6-bb30-46f0-8384-01913c1dcf2c)
![18](https://github.com/Sharif-University-ESRLab/Fall2023-uefi-file-system-explorer/assets/59166955/4bba9135-7bd9-482a-99c6-e6f03ffa2c60)
![17](https://github.com/Sharif-University-ESRLab/Fall2023-uefi-file-system-explorer/assets/59166955/77ba0178-b72e-42ba-bc60-61b4494ce378)
![16](https://github.com/Sharif-University-ESRLab/Fall2023-uefi-file-system-explorer/assets/59166955/44fd102f-04d8-4050-881e-4895a89a51f2)
![15](https://github.com/Sharif-University-ESRLab/Fall2023-uefi-file-system-explorer/assets/59166955/a7e82e1a-0880-41f9-b84d-48cc3d4ae664)
![14](https://github.com/Sharif-University-ESRLab/Fall2023-uefi-file-system-explorer/assets/59166955/027236fd-2bf9-402f-a597-97bdac747c77)
![13](https://github.com/Sharif-University-ESRLab/Fall2023-uefi-file-system-explorer/assets/59166955/d151776d-c2a4-4749-b892-997e976b60df)
![12](https://github.com/Sharif-University-ESRLab/Fall2023-uefi-file-system-explorer/assets/59166955/2c3c87f2-c58d-41fe-beed-bf54ef22a125)






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


