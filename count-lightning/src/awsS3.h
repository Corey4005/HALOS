#ifndef AWSS3
#define AWSS3

// Include necessary headers for the AWS SDK and S3 client
#include <iostream>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/ListObjectsRequest.h>
#include <aws/s3/model/Object.h>

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
