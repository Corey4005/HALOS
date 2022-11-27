
This repo was built on a windows machine using Visual Studio. Therefore, it uses a windows package managers to install the required libraries. 

# Required
1. vcpkg - package manager
2. netcdf-cxx4 - netcdf library from UCAR

# How to install vspkg
  - First pull the [vspkg github repo](https://github.com/microsoft/vcpkg) to a suitable file on your local machine
  - Then, add vcpkg application to your environment path variable 

# How to install netcdf-cxx4 
  The following will install the x64 version of the library: 
  
  ``` 
  $ vcpkg install netcdf-cxx4 --triplet x64-windows 
  
  ```
  The following will make your library available to the ```#include``` preprocessor statement in Visual Studio:
  
  ``` 
  $ vcpkg integrate install 
  
  ``` 
