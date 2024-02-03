*   **FileSystem.c (C Source Files):**
    *   `.c` files contain C source code, defining the logic and functionality of our UEFI application.
*   **FileSystem.inf (Platform Configuration Files):**
    *   `.inf` files configure our application's dependencies, libraries, and protocols during the build process.
*   **FileSystemDescription.dsc (Platform Description Files):**
    *   `.dsc` files describe the structure of our UEFI application, specifying modules, components, and dependencies.
*   **FileSystem.efi (EFI Executable Files):**
    *   `.efi` files are compiled UEFI executable binaries, generated from `.c` source files, which can be executed within QEMU.
