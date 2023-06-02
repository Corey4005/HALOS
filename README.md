# Overview
HALIOS - "Hurricane Advanced Lightning Observation System" is a C++ program to collect [lightning data](https://github.com/Corey4005/HALIOS/blob/master/textfile/textfile.txt) from interpolated timestamp points over known hurricane pathways. Currently, [Python based programs](https://github.com/Corey4005/Count-Hurricane-Lightining-Flashes) that provide similar solutions take increased time (~8 hours per storm path) to collect all lightning information along a pathway. This program can collect the same amount of infomation in half the time because it is written in C++, which serperates run time from compile time and does not need an interpretor. This means that this tool could possibly help researchers interested in generating lighting climatologies over hurrricane events at increased scale and speed. This program is also built on the AWS cloud system which provides all GOES-16 GLM netCDF files that currently exist free of charge to tht user. This means that the user does not need the netCDF data locally to retrieve lightning data.

Currently this repo can be built on a windows machine using Visual Studio and the [MSVC legacy compiler](https://learn.microsoft.com/en-us/cpp/build/reference/compiling-a-c-cpp-program?view=msvc-170). 

# Required
1. [vcpkg](https://vcpkg.io/en/index.html) - C++ package manager for windows machines
2. [AWS C++ SDK](https://github.com/aws/aws-sdk-cpp/tree/main/aws-cpp-sdk-s3) [S3] - tool for data collection from cloud to local ```/netcdf``` directory
3. netcdf-cxx4 - netcdf library from UCAR to process netcdf files
4. HDF5 - hierarchical data format library, required for netcdf-cxx4 as dependency

# How to install vspkg
  - First pull the [vspkg github repo](https://github.com/microsoft/vcpkg) to a suitable file on your local machine
  - Then, add vcpkg application to your environment path variable 

# How to install netcdf-cxx4 
  The following will install the x64 version of the library: 
  
  ``` 
  $ vcpkg install netcdf-cxx4:x64-windows 
  
  ```
  The following command will make all libraries downloaded available to the ```#include``` preprocessor statement in Visual Studio:
  
  ``` 
  $ vcpkg integrate install 
  ``` 
  # How to install S3, transfer
  ```
  vcpkg install aws-cpp-sdk[s3, transfer]:x64-windows
  
  ```
  # How to install HDF5
  ```
  vcpkg install hdf5:x64-windows
  
  ```
  
  # Important configuration and credential settings for the AWS SDK 
  
  Before running the code, you will need to set up specific AWS environment variables, which are needed to initialize the api and call for the netcdf files containing lightning data. 
  1. Set up an AWS account and follow steps 1-11 [here](https://docs.aws.amazon.com/sdk-for-cpp/v1/developer-guide/credentials.html) to create a credentials file. 
  2. Similarly, you will need to set up an AWS config file with plain text that is best for your region. Documentation on config files are found [here](https://docs.aws.amazon.com/sdkref/latest/guide/file-format.html).
  3. Set up your `AWS_CONFIG_FILE` and `AWS_CREDENTIALS_FILE` path variables by using the windows commands at the bottom of [this](https://docs.aws.amazon.com/sdkref/latest/guide/file-location.html) page. 
  
  # Import configuration setting for HDF5
  1. You will get an HDF error when trying to read an NcFile unless you set the `HDF5_USE_FILE_LOCKING=FALSE`
