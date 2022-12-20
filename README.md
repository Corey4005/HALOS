
This repo was built on a windows machine using Visual Studio. Therefore, it uses a windows package managers to install the required libraries. 

# Required
1. vcpkg - package manager
2. AWS SDK S3, Transfer - s3 tool for data collection and transfer to local
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
  
  # Important configuration and credential settings for the AWS SDK 
  
  Before running the code, you will need to set up specific AWS environment variables, which are needed to initialize the api and call for the netcdf files containing lightning data. 
  1. Set up an AWS account and follow steps 1-11 [here](https://docs.aws.amazon.com/sdk-for-cpp/v1/developer-guide/credentials.html) to create a credentials file. 
  2. Similarly, you will need to set up an AWS config file with plain text that is best for your region. Documentation on config files are found [here](https://docs.aws.amazon.com/sdkref/latest/guide/file-format.html).
  3. Set up your `AWS_CONFIG_FILE` and `AWS_CREDENTIALS_FILE` path variables by using the windows commands at the bottom of [this](https://docs.aws.amazon.com/sdkref/latest/guide/file-location.html) page. 
