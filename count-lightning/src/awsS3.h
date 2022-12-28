#ifndef AWSS3
#define AWSS3

// Include necessary headers for the AWS SDK and S3 client
#include <iostream>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/ListObjectsRequest.h>
#include <aws/s3/model/Object.h>


/**
* This is a header file containing the relevant AWS functions to find and download dynamically changing datetimes from S3. 
*/
const std::string bucket = "noaa-goes16";
const std::string product = "GLM-L2-LCFA";
const std::string filestart = "OR_GLM-L2-LCFA_G16_"; //represents file start path

// Declare function to find an object in a bucket
bool findObject(const Aws::String& bucketName, 
    const Aws::String& subfolder, 
    const Aws::String& date, 
    const Aws::Client::ClientConfiguration& client, 
    bool downloadObject);

// Declare function to download an object from a bucket
bool GetObject(const Aws::String& objectKey,
    const Aws::String& fromBucket, const Aws::String& date,
    const Aws::Client::ClientConfiguration& clientConfig);

#endif
