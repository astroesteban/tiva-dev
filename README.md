# TM4C CMake Dev Environment

A fully self-contained development environment for the Texas Instruments
TM4C Launchpad.

## Getting Started

### Dependencies

- Docker
- Visual Studio Code
- [Remote Extension Pack](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.vscode-remote-extensionpack)
- OpenOCD (if debugging on macOS)
- [LM4Flash](https://github.com/utzig/lm4tools) (if debugging on macOS)

### Installing

You can simply clone the repo and reopen in the development container in Visual
Studio Code.

## Help

### Debugging On macOS

On macOS you unfortunately cannot access USB devices from inside of Docker. You
can still build the application in the Docker container but to debug on the
TM4C you'll need to install OpenOCD and LM4Flash on macOS. The easiest way to
do this is via HomeBrew. You can do so as follows.

1. Install OpenOCD
```sh
brew install openocd
```

2. Install LM4Tools
```sh
brew install lm4flash
```

3. Install GDB
```sh
brew install gdb
```

What I like to do then is keep two VS Code windows open. One is reopened in the
Docker container and another one is open on the macOS host. When I'm ready to
debug on macOS I run the `flash.sh` script and then launch the debugger in VS
Code on the host window. 

Another issue I had to resolve was that GDB complained that there was no
file or directory for the executable's source file. A quick workaround for it
was to enter `directory /path/to/your/source/file` once GDB starts. If you can
find a fix for this please let me know! I used [this blog post](https://alex.dzyoba.com/blog/gdb-source-path/)
to get some ideas of how to fix it.

### LibUSB Error

An issue I encountered on Ubuntu 20.04 was that I needed to run `lm4flash` and `openocd` as sudo. 
This is a problem when using VS Code extensions because you'd either have to hardcode your password
into the JSON file or instead run `lm4flash` and `openocd` via the terminal (which I did not want to).

If you try to run `lm4flash MicroInvaders.bin` from `{workspace}/build/src` and get the following error:

```sh
Unable to open USB device: LIBUSB_ERROR_ACCESS
Unable to find any ICDI devices
```

Then this issue is for you. It just means your user account does not have the permissions to open
the usb device. In this case the microcontroller we are trying to flash.

So to fix this we need to:

1. Create a new rules file as so:

```sh
sudo touch /etc/udev/rules.d/tm4c.rules
```

2. In the new `tm4c.rules` file paste

```bash
sudo vim /etc/udev/rules.d/tm4c.rules
```

```bash
SUBSYSTEM=="usb", ATTRS{idVendor}=="1234", MODE="0666"
SUBSYSTEM=="usb_device", ATTRS{idVendor}=="1234", MODE="0666"
```
where you replace `idVendor` with the TM4C's vendor ID.

> NOTE: If you don't know how to get the vendor ID for the Launchpad, simply run

```bash
echo 'ATTRS{idVendor}=="1cbe", ATTRS{idProduct}=="00fd", GROUP="users", MODE="0660"' | sudo tee /etc/udev/rules.d/99-stellaris-launchpad.rules
```

3. Now, once you have your new rules file setup, you need to reload the rules with

```sh
sudo udevadm control --reload-rules
```

4. Last but not least, unplug your Launchpad and plug it back in. You should now
be able to run `lm4flash MicroInvaders.bin`
