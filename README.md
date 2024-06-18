# tearson

## overview

**tearson** is a proof-of-concept project designed to bypass the security measures of the pearson lockdown browser vm. this tool injects hooks into the pearson executable as it opens, intercepting various function calls to prevent the detection of a virtual machine and other security checks.

## features

- **hooks `GetProcAddress`**: intercepts calls to this function to prevent vm & hook detection mechanisms.
- **hooks pearsons `report_post`**: blocks the function responsible for sending reports and detections completely.
- **hooks `HidCheckVM`**: bypasses the pearsons vm checks to prevent the detection of any virtual machine software.

## installation

1. clone the repository:
    ```sh
    git clone https://github.com/nulledc0de/tearson.git
    ```
2. build the project using visual studio 2022.

## usage

1. inject the compiled tearson dll into the pearson executable as it opens.
2. the hooks will automatically be created and active during the execution of the pearson software.

## disclaimer

this project is for educational and research purposes only. use of this tool to cheat in exams is not recommended. the author does not condone or support any illegal activities and is not responsible for any misuse of this project.

## credits

this project uses [minhook](https://github.com/TsudaKageyu/minhook), a lightweight x86/x64 api hooking library for windows.

minhook is licensed under the [BSD license](https://github.com/TsudaKageyu/minhook/blob/master/LICENSE.md).
