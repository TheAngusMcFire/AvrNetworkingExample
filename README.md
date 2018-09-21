# AvrNetworkingExample

This example should mainly show how to develop code with maximum reusability.

The Key is to structure the code into different layers and define fixed interfaces  
which can be reused with different microcontrollers and different architectures.

### Folder structure:

* hardware_abstraction_layer  
this folder contains the hal implementations for the different microcontroller types

* interfaces
this folder contains the header files with the function prototype interfaces, no target specific code will be in there

* library
the implementation of the platform independent code
